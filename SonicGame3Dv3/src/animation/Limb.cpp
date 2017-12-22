#include <cmath>

#include "body.h"
#include "keyframe.h"
#include "../toolbox/maths.h"
#include "limb.h"



Limb::Limb(std::list<TexturedModel*>* models, float pivotX, float pivotY, float pivotZ, Body* body, Limb* limb)
{
	myModels = models;
	this->pivotX = pivotX;
	this->pivotY = pivotY;
	this->pivotZ = pivotZ;
	this->body = body;
	this->limb = limb;
	setVisible(true);
}

void Limb::step()
{

}

void Limb::update(float time)
{
	time = (float)fmax(time, 0);
	bool inRange = false;
	Keyframe* key1 = nullptr;
	Keyframe* key2 = nullptr;


	float angleX, angleY, angleZ;
	if (body != nullptr)
	{
		angleX = (float)toRadians(body->getRotX());
		angleY = (float)toRadians(body->getRotY());
		angleZ = (float)toRadians(body->getRotZ());
	}
	else
	{
		angleX = (float)toRadians(limb->getRotX());
		angleY = (float)toRadians(limb->getRotY());
		angleZ = (float)toRadians(limb->getRotZ());
	}


	float newX = pivotX, newY = pivotY, newZ = pivotZ;

	//float newX = (float)(pivotZ*Math.sin(angleY) + pivotX*Math.cos(angleY));
	//float newZ = (float)(pivotZ*Math.cos(angleY) - pivotX*Math.sin(angleY));
	//System.out.println("before:  x = "+newX+"     y = "+newY+"     angleZ = "+Math.toDegrees(angleZ));


	//rotation around x axis
	//newY = (float) (pivotY * Math.cos(angleX) - pivotZ * Math.sin(angleX));
	//newZ = (float) (pivotY * Math.sin(angleX) + pivotZ * Math.cos(angleX));

	float newPivotX = newX;
	float newPivotY = newY;
	float newPivotZ = newZ;

	//rotation around z axis
	newX = (float)(newPivotX * cos(angleZ) - newPivotY * sin(angleZ));
	newY = (float)(newPivotX * sin(angleZ) + newPivotY * cos(angleZ));
	//newY = (float)(pivotY*Math.cos(angleZ) - pivotX*Math.sin(angleZ));

	//System.out.println("after:  x = "+newX+"     y = "+newY+"     angleZ = "+Math.toDegrees(angleZ));
	//System.out.println("radius = "+(float)Math.sqrt(Math.pow(newX, 2)+Math.pow(newY, 2)));
	//System.out.println();

	newPivotX = newX;
	newPivotY = newY;
	newPivotZ = newZ;

	//rotation around y axis
	newX = (float)(newPivotX * cos(angleY) + newPivotZ * sin(angleY));
	newZ = (float)(newPivotZ * cos(angleY) - newPivotX * sin(angleY));

	/*
	Matrix4f rotationMat = Maths.createTransformationMatrix(new Vector3f(0,0,0), 0, angleY, angleZ, 0);
	Vector4f position = new Vector4f(newX, newY, newZ, 1);

	position = Maths.multiplyByMat(position, rotationMat);
	newX = position.x;
	newY = position.y;
	newZ = position.z;
	*/
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
		float t = (time - key1->time) / (key2->time - key1->time);

		//sinusoidal interpolation
		t = 1 - ((float)(cos(M_PI*t) + 1)*0.5f);

		float ratio = t;

		newXRot = key1->xRot + ratio*(key2->xRot - key1->xRot);
		newYRot = key1->yRot + ratio*(key2->yRot - key1->yRot);
		newZRot = key1->zRot + ratio*(key2->zRot - key1->zRot);
		newScale = key1->scale + ratio*(key2->scale - key1->scale);
	}
	else
	{
		newXRot = key2->xRot;
		newYRot = key2->yRot;
		newZRot = key2->zRot;
		newScale = key2->scale;
	}

	if (body != nullptr)
	{
		position.x = (body->getX() + newX);
		position.y = (body->getY() + newY);
		position.z = (body->getZ() + newZ);
		setRotX(body->getRotX() + newXRot);
		setRotY(body->getRotY() + newYRot);
		setRotZ(body->getRotZ() + newZRot);//pitch
		//super.setScale(newScale);
	}
	else
	{
		position.x = (limb->getX() + newX);
		position.y = (limb->getY() + newY);
		position.z = (limb->getZ() + newZ);
		setRotX(limb->getRotX() + newXRot);
		setRotY(limb->getRotY() + newYRot);
		setRotZ(limb->getRotZ() + newZRot);//pitch
		//super.setScale(newScale);
	}
}

std::list<TexturedModel*>* Limb::getModels()
{
	return myModels;
}