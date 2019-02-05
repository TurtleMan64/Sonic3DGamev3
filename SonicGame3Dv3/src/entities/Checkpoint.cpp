#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "checkpoint.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/controllableplayer.h"
#include "../toolbox/maths.h"
#include "../animation/body.h"
#include "../entities/camera.h"
#include "../audio/audioplayer.h"
#include "../particles/particleresources.h"
#include "../particles/particle.h"
#include "../guis/guimanager.h"
#include "../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> Checkpoint::modelsBase;
std::list<TexturedModel*> Checkpoint::modelsBall;

float Checkpoint::colHorizontal = 9;
float Checkpoint::colVertical   = 9;
ALuint Checkpoint::savedBGMIntro = AL_NONE;
ALuint Checkpoint::savedBGMLoop  = AL_NONE;

Checkpoint::Checkpoint()
{

}

Checkpoint::Checkpoint(float x, float y, float z, float rotY)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	scale = 1;
	visible = true;
	isHit = false;
	updateTransformationMatrix();

	if (Global::spawnAtCheckpoint)
	{
		float xDiff = Global::checkpointX - x;
		float yDiff = Global::checkpointY - y;
		float zDiff = Global::checkpointZ - z;

		if (sqrtf(xDiff*xDiff + yDiff*yDiff + zDiff*zDiff) < 50)
		{
			isHit = true;
			if (Checkpoint::savedBGMIntro != AL_NONE)
			{
				AudioPlayer::playBGMWithIntro(Checkpoint::savedBGMIntro, Checkpoint::savedBGMLoop);
			}
			else
			{
				AudioPlayer::playBGM(Checkpoint::savedBGMLoop);
			}
		}
	}

	float rot = toRadians(rotY);

	Vector3f off(0, 8.6f, -15.12f);
	float newX =   off.x*cosf(rot) - off.z*sinf(rot);
	float newZ = -(off.z*cosf(rot) + off.x*sinf(rot));
	Vector3f ball1Pos(newX, off.y, newZ);
	ball1Pos = ball1Pos + position;

	off.set(0, 8.6f, 15.12f);
	newX =   off.x*cosf(rot) - off.z*sinf(rot);
	newZ = -(off.z*cosf(rot) + off.x*sinf(rot));
	Vector3f ball2Pos(newX, off.y, newZ);
	ball2Pos = ball2Pos + position;

	ball1 = new Body(&Checkpoint::modelsBall); INCR_NEW
	Main_addEntity(ball1);
	ball1->setVisible(true);
	ball1->setPosition(&ball1Pos);
	ball1->setRotY(rotY+90);
	ball1->updateTransformationMatrix();

	ball2 = new Body(&Checkpoint::modelsBall); INCR_NEW
	Main_addEntity(ball2);
	ball2->setVisible(true);
	ball2->setPosition(&ball2Pos);
	ball2->setRotY(rotY-90);
	ball2->updateTransformationMatrix();

	if (isHit)
	{
		ball1->setRotZ(90);
		ball2->setRotZ(90);
		ball1->updateTransformationMatrix();
		ball2->updateTransformationMatrix();
	}
}

void Checkpoint::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
		ball1->setVisible(false);
		ball2->setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
			ball1->setVisible(false);
			ball2->setVisible(false);
		}
		else
		{
			setVisible(true);
			ball1->setVisible(true);
			ball2->setVisible(true);

			if (Global::gamePlayer->getX() > getX() - colHorizontal - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getX() < getX() + colHorizontal + Global::gamePlayer->getHitboxHorizontal() &&
				Global::gamePlayer->getZ() > getZ() - colHorizontal - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getZ() < getZ() + colHorizontal + Global::gamePlayer->getHitboxHorizontal() &&
				Global::gamePlayer->getY() + Global::gamePlayer->getHitboxVertical() >= getY() - colVertical && Global::gamePlayer->getY() - Global::gamePlayer->getHitboxVertical() <= getY() + colVertical)
			{
				if (!isHit)
				{
					AudioPlayer::play(45, getPosition());

					Checkpoint::savedBGMIntro = AudioPlayer::bgmIntro;
					Checkpoint::savedBGMLoop  = AudioPlayer::bgmLoop;

					isHit = true;
					Global::spawnAtCheckpoint  = true;
					Global::checkpointX        = Global::gamePlayer->getX();
					Global::checkpointY        = Global::gamePlayer->getY();
					Global::checkpointZ        = Global::gamePlayer->getZ();
					Global::checkpointRotY     = Global::gamePlayer->getRotY();
					Global::checkpointCamYaw   = Global::gameCamera->getYaw();
					Global::checkpointCamPitch = Global::gameCamera->getPitch();
					Global::checkpointTimeCen  = GuiManager::getCentiseconds();
					Global::checkpointTimeSec  = GuiManager::getSeconds();
					Global::checkpointTimeMin  = GuiManager::getMinutes();

					if (!CollisionChecker::checkCollision(
						Global::checkpointX, Global::checkpointY,    Global::checkpointZ,
						Global::checkpointX, Global::checkpointY-30, Global::checkpointZ))
					{
						Global::checkpointX = getX();
						Global::checkpointY = getY()+5;
						Global::checkpointZ = getZ();
					}

					ball1->setRotZ(90);
					ball2->setRotZ(90);
					ball1->updateTransformationMatrix();
					ball2->updateTransformationMatrix();
				}
			}
		}
	}
}

std::list<TexturedModel*>* Checkpoint::getModels()
{
	return &Checkpoint::modelsBase;
}

void Checkpoint::loadStaticModels()
{
	if (Checkpoint::modelsBase.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading Checkpoint static models...\n");
	#endif

	loadObjModel(&Checkpoint::modelsBase, "res/Models/Checkpoint/", "Base.obj");
	loadObjModel(&Checkpoint::modelsBall, "res/Models/Checkpoint/", "Ball.obj");
}

void Checkpoint::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting Checkpoint static models...\n");
	#endif

	Entity::deleteModels(&Checkpoint::modelsBase);
	Entity::deleteModels(&Checkpoint::modelsBall);
}