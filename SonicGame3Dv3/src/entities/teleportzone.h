#ifndef TELEPORTZONE_H
#define TELEPORTZONE_H

#include <list>
#include "entities.h"
#include <AL/al.h>


class TeleportZone : public Entity
{
private:
	float camYawTarget;
	float camPitchTarget;

	Vector3f teleportLocation;

	int bgmIntroToPlay;
	int bgmLoopToPlay;

public:
	TeleportZone();
	TeleportZone(float x, float y, float z, 
				 float xTarget, float yTarget, float zTarget, 
				 float newYaw, float newPitch, float size, 
			     int newBGMIntro, int newBGMLoop);

	void step();
};
#endif