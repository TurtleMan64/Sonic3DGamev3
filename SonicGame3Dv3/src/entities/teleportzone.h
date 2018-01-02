#ifndef TELEPORTZONE_H
#define TELEPORTZONE_H

#include <list>
#include "entities.h"


class TeleportZone : public Entity
{
private:
	float camYawTarget;
	float camPitchTarget;

	Vector3f teleportLocation;

public:
	TeleportZone();
	TeleportZone(float x, float y, float z, 
				 float xTarget, float yTarget, float zTarget, 
				 float newYaw, float newPitch, float size);

	void step();
};
#endif