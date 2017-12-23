#include <cmath>

#include "body.h"
#include "keyframe.h"
#include "../toolbox/maths.h"



Body::Body(std::list<TexturedModel*>* models)
{
	myModels = models;
	baseX = 0;
	baseY = 0;
	baseZ = 0;
	baseRotY = 0;
	baseRotZ = 0;
	baseRotX = 0;
	animationIndex = 0;
	time = 0;
	prevTime = 0;
	deltaTime = 0;
	setVisible(true);
}

void Body::step()
{

}

void Body::update(float time)
{
	prevTime = this->time;
	this->time = (float)(std::fmax(time, 0));
	time = this->time;
	deltaTime = this->time - prevTime;
	bool inRange = false;
	Keyframe* key1 = nullptr;
	Keyframe* key2 = nullptr;
	float newX = 0;
	float newY = 0;
	float newZ = 0;
	float newXRot = 0;
	float newYRot = 0;
	float newZRot = 0;
	float newScale = 0;

	for (unsigned int i = 0; i < (*animations)[animationIndex].keyframes.size() - 1; i++)
	{
		key1 = &(*animations)[animationIndex].keyframes[i];
		key2 = &(*animations)[animationIndex].keyframes[i + 1];

		if (time >= key1->time && time <= key2->time)
		{
			inRange = true;
			break;
		}
	}

	if (inRange)
	{
		//linear interpolation
		//view key1 as the "base"
		//and add a certain ratio of the difference between
		//key2 and key1 to key1 for the interpolated value
		//float ratio = (time-key1.time)/(key2.time-key1.time);
		float t = (time - key1->time) / (key2->time - key1->time);

		//sinusoidal interpolation
		t = 1 - ((float)(cos(M_PI*t) + 1)*0.5f);

		float ratio = t;

		newX = key1->x + ratio*(key2->x - key1->x);
		newY = key1->y + ratio*(key2->y - key1->y);
		newZ = key1->z + ratio*(key2->z - key1->z);
		newXRot = key1->xRot + ratio*(key2->xRot - key1->xRot);
		newYRot = key1->yRot + ratio*(key2->yRot - key1->yRot);
		newZRot = key1->zRot + ratio*(key2->zRot - key1->zRot);
		newScale = key1->scale + ratio*(key2->scale - key1->scale);
	}
	else
	{
		newX = key2->x;
		newY = key2->y;
		newZ = key2->z;
		newXRot = key2->xRot;
		newYRot = key2->yRot;
		newZRot = key2->zRot;
		newScale = key2->scale;
	}
	float newXOffset = newX;
	float newZOffset = newZ;
	float angleY = (float)toRadians(baseRotY + newYRot);

	newX = (float)(newXOffset * cos(angleY) + newZOffset * sin(angleY));
	newZ = (float)(newZOffset * cos(angleY) - newXOffset * sin(angleY));

	position.x = (baseX + newX);
	position.y = (baseY + newY);
	position.z = (baseZ + newZ);
	setRotX(newXRot);
	setRotY(baseRotY + newYRot);
	setRotZ(baseRotZ + newZRot);
	//setScale(newScale);
}

void Body::setBaseOrientation(Vector3f* basePosition, float rotY, float rotZ)
{
	baseX = basePosition->x;
	baseY = basePosition->y;
	baseZ = basePosition->z;
	baseRotY = rotY;
	baseRotZ = rotZ;
}

void Body::setBaseRotZ(float rotZ)
{
	baseRotZ = rotZ;
}

std::list<TexturedModel*>* Body::getModels()
{
	return myModels;
}