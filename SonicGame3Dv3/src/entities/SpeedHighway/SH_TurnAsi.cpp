#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "shturnasi.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
#include "../../toolbox/maths.h"
#include "../../animation/body.h"
#include "../../entities/camera.h"
#include "../../audio/audioplayer.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> SH_TurnAsi::modelsFork;
std::list<TexturedModel*> SH_TurnAsi::modelsBucket;

SH_TurnAsi::SH_TurnAsi()
{

}

SH_TurnAsi::SH_TurnAsi(float x, float y, float z, float yRot)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	rotY = yRot;
	rotZ = -90;
	scale = 1;
	visible = true;
	storedSonicSpeed = 0;
	updateTransformationMatrix();

	bucket = new Body(&SH_TurnAsi::modelsBucket);
	bucket->setVisible(true);
	INCR_NEW
	Main_addEntity(bucket);
	bucket->setPosition(&position);
	bucket->setRotY(yRot + 180.0f);
	bucket->setRotZ(0);
}

void SH_TurnAsi::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
		bucket->setVisible(false);
		rotZ = -90.0f;
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
			bucket->setVisible(false);
			rotZ = -90.0f;
		}
		else
		{
			setVisible(true);
			bucket->setVisible(true);

			if (rotZ == -90.0f)
			{
				//check collision for sonic in bucket

				float yAng = toRadians(rotY+90);
				float xDisp =  20*cosf(yAng);
				float zDisp = -20*sinf(yAng);

				float xDiff = Global::gamePlayer->getX() - (getX() + xDisp);
				float yDiff = Global::gamePlayer->getY() + (Global::gamePlayer->getHitboxVertical() * 0.5f) - (getY() - 105.0f);
				float zDiff = Global::gamePlayer->getZ() - (getZ() + zDisp);

				float diffRadSquared = Global::gamePlayer->getHitboxHorizontal() + 30.0f;
				diffRadSquared = diffRadSquared*diffRadSquared;

				if (xDiff*xDiff + yDiff*yDiff + zDiff*zDiff < diffRadSquared)
				{
					storedSonicSpeed = fmaxf(Global::gamePlayer->getSpeed(), 5.5f);
					rotZ += 1.0f;
				}
				else
				{
					yAng = toRadians(rotY - 90);
					xDisp =  20 * cosf(yAng);
					zDisp = -20 * sinf(yAng);

					xDiff = Global::gamePlayer->getX() - (getX() + xDisp);
					yDiff = Global::gamePlayer->getY() + (Global::gamePlayer->getHitboxVertical() * 0.5f) - (getY() - 105.0f);
					zDiff = Global::gamePlayer->getZ() - (getZ() + zDisp);

					diffRadSquared = Global::gamePlayer->getHitboxHorizontal() + 30.0f;
					diffRadSquared = diffRadSquared*diffRadSquared;

					if (xDiff*xDiff + yDiff*yDiff + zDiff*zDiff < diffRadSquared)
					{
						storedSonicSpeed = Global::gamePlayer->getSpeed();
						rotZ += 1.0f;
					}
				}

				Vector3f bPos(getX(), getY() - 105.0f, getZ());
				bucket->setPosition(&bPos);
			}
			else
			{
				if (rotZ < 90.0f)
				{
					float prevRotZ = rotZ;
					rotZ += storedSonicSpeed*0.4f;

					if (prevRotZ < 0.0f && rotZ >= 0.0f)
					{
						Global::gamePlayer->setCameraTargetYaw(-rotY + 270);
						Global::gamePlayer->setCameraTargetPitch(30);
					}

					float zAng = toRadians(rotZ);
					float yAng = toRadians(rotY);

					Vector3f bucketPos = spherePositionFromAngles(-yAng, zAng, 105.0f) + getPosition();

					bucket->setPosition(&bucketPos);
					Global::gamePlayer->setPosition(&bucketPos);
					Global::gamePlayer->setxVelAir(0);
					Global::gamePlayer->setzVelAir(0);
					Global::gamePlayer->setyVel(0);

					if (rotZ >= 90.0f)
					{
						rotZ = 90.0f;
						//Set players air speed
						float newXSpd =  storedSonicSpeed*cosf((float)(yAng+M_PI));
						float newZSpd = -storedSonicSpeed*sinf((float)(yAng+M_PI));
						Global::gamePlayer->setxVelAir(newXSpd);
						Global::gamePlayer->setzVelAir(newZSpd);

						bucketPos.set(getX(), getY() + 105.0f, getZ());
						bucket->setPosition(&bucketPos);
					}
				}
			}

			updateTransformationMatrix();
			bucket->updateTransformationMatrix();
		}
	}
}

std::list<TexturedModel*>* SH_TurnAsi::getModels()
{
	return &SH_TurnAsi::modelsFork;
}

void SH_TurnAsi::loadStaticModels()
{
	if (SH_TurnAsi::modelsFork.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading SH_TurnAsi static models...\n");
	#endif

	loadObjModel(&SH_TurnAsi::modelsFork, "res/Models/SpeedHighway/", "Fork.obj");
	loadObjModel(&SH_TurnAsi::modelsBucket, "res/Models/SpeedHighway/", "Bucket.obj");
}

void SH_TurnAsi::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting SH_TurnAsi static models...\n");
	#endif

	Entity::deleteModels(&SH_TurnAsi::modelsFork);
	Entity::deleteModels(&SH_TurnAsi::modelsBucket);
}
