#include <glad/glad.h>

#include "../entities.h"
#include "bmanager.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../audio/audioplayer.h"
#include "../controllableplayer.h"
#include "bplatform.h"
#include "bmeteor.h"
#include "bearth.h"
#include "bmetalsonic.h"
#include "../ring.h"

#include <list>
#include <iostream>

B_Manager::B_Manager()
{
	visible = false;
	platformCount = 0;
	timer = 0;

	B_Platform::loadStaticModels();
	B_Meteor::loadStaticModels();
	B_Earth::loadStaticModels();
	B_MetalSonic::loadStaticModels();

	theEarth = new B_Earth; INCR_NEW
	Main_addEntity(theEarth);

	theBoss = new B_MetalSonic; INCR_NEW
	Main_addEntity(theBoss);
}

void B_Manager::step()
{
	timer++;

	bool lookAtBoss = false;

	if (timer < 570)
	{
		Global::gamePlayer->setCanMoveTimer(2);
		Global::gamePlayer->setGroundSpeed(5.0f, 0.0f);

		lookAtBoss = true;
	}

	Vector3f* playPos = Global::gamePlayer->getPosition();
	while (playPos->x+4000 > platformCount*300.0f)
	{
		float baseX = platformCount*300.0f;

		B_Platform* p = new B_Platform(baseX, 2000.0f, 0.0f); INCR_NEW
		Main_addEntity(p);
		platformCount++;

		if (platformCount % 16 == 0)
		{
			Main_addEntity(new Ring(baseX-48, 2010, 20));
			Main_addEntity(new Ring(baseX-24, 2010, 20));
			Main_addEntity(new Ring(baseX,    2010, 20));
			Main_addEntity(new Ring(baseX+24, 2010, 20));
			Main_addEntity(new Ring(baseX+48, 2010, 20));
		}
		else if (platformCount % 16 == 8)
		{
			Main_addEntity(new Ring(baseX-48, 2010, -20));
			Main_addEntity(new Ring(baseX-24, 2010, -20));
			Main_addEntity(new Ring(baseX,    2010, -20));
			Main_addEntity(new Ring(baseX+24, 2010, -20));
			Main_addEntity(new Ring(baseX+48, 2010, -20));
		}
	}

	if (timer % 60 == 0 && Global::finishStageTimer == -1)
	{
		Vector3f pos(2*(Maths::random()-0.5f), Maths::random(), 2*(Maths::random()-0.5f));

		if (abs(pos.x) < 0.2f) { pos.x = 0.2f; }
		if (abs(pos.y) < 0.2f) { pos.y = 0.2f; }
		if (abs(pos.z) < 0.2f) { pos.z = 0.2f; }

		Vector3f vel(&pos);

		pos.scale(5000);
		pos.x += playPos->x+2500;
		pos.y += playPos->y+125;
		pos.z += playPos->z;

		vel.scale(-10);

		B_Meteor* p = new B_Meteor(pos.x, pos.y, pos.z, vel.x, vel.y, vel.z); INCR_NEW
		Main_addEntity(p);
	}

	if (theBoss->getX()-50 > playPos->x)
	{
		if (Global::isAutoCam)
		{
			lookAtBoss = true;
		}
	}

	if (Global::finishStageTimer > -1)
	{
		lookAtBoss = false;
	}

	if (lookAtBoss)
	{
		float xDiffCam = Global::gamePlayer->getX() - theBoss->getX();
		float zDiffCam = Global::gamePlayer->getZ() - theBoss->getZ();
		float yDiffCam = Global::gamePlayer->getY() - theBoss->getY() + 60;
		float hDistCam = sqrtf(xDiffCam*xDiffCam + zDiffCam*zDiffCam);
		float toTargetYaw   = -toDegrees(atan2f(-zDiffCam, xDiffCam))-90;
		float toTargetPitch =  toDegrees(atan2f(yDiffCam, hDistCam));
		float diffYaw   = 0.25f*compareTwoAngles(toTargetYaw,   Global::gameCamera->getYaw());
		float diffPitch = 0.25f*compareTwoAngles(toTargetPitch, Global::gameCamera->getPitch());

		Global::gamePlayer->setCameraTargetYaw(Global::gameCamera->getYaw() + diffYaw);
		Global::gamePlayer->setCameraTargetPitch(Global::gameCamera->getPitch() + diffPitch);
	}

	theEarth->setPosition(playPos->x, -2000, playPos->z);
	theEarth->updateTransformationMatrix();
}

std::list<TexturedModel*>* B_Manager::getModels()
{
	return nullptr;
}
