#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "teleportzone.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/camera.h"
#include "../entities/playersonic.h"
#include "../collision/collisionchecker.h"
#include "../collision/triangle3d.h"
#include "../toolbox/maths.h"
#include "../audio/audioplayer.h"

#include <AL/al.h>
#include <list>
#include <iostream>
#include <algorithm>


TeleportZone::TeleportZone()
{

}

TeleportZone::TeleportZone(float x, float y, float z,
						   float xTarget, float yTarget, float zTarget,
						   float newYaw, float newPitch, float size, 
						   int newBGMIntro, int newBGMLoop)
{
	position.x = x;
	position.y = y;
	position.z = z;
	scale = size;
	visible = false;
	bgmIntroToPlay = newBGMIntro;
	bgmLoopToPlay = newBGMLoop;
	teleportLocation.set(xTarget, yTarget, zTarget);
	camYawTarget = newYaw;
	camPitchTarget = newPitch;
}

void TeleportZone::step()
{
	float rad = scale / 2;

	if (Global::gamePlayer->getX() > getX() - rad && Global::gamePlayer->getX() < getX() + rad &&
		Global::gamePlayer->getZ() > getZ() - rad && Global::gamePlayer->getZ() < getZ() + rad &&
		Global::gamePlayer->getY() > getY()       && Global::gamePlayer->getY() < getY() + scale)
	{
		Global::gamePlayer->setPosition(&teleportLocation);
		Global::gamePlayer->setCameraAngles(camYawTarget, camPitchTarget);
		Global::gamePlayer->stopMoving();

		if (bgmIntroToPlay != -1 && bgmLoopToPlay != -1)
		{
			AudioPlayer::playBGMWithIntro(bgmIntroToPlay, bgmLoopToPlay);
		}
		else if (bgmIntroToPlay == -1 && bgmLoopToPlay != -1)
		{
			AudioPlayer::playBGM(bgmLoopToPlay);
		}
	}
}
