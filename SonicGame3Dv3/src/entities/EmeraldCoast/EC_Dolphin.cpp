#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecdolphin.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../audio/audioplayer.h"
#include "../../particles/particle.h"
#include "../../particles/particleresources.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> EC_Dolphin::models;

EC_Dolphin::EC_Dolphin()
{
	
}

EC_Dolphin::EC_Dolphin(
	float x, float y, float z, 
    float rotY,
    float triggerX, float triggerY, float triggerZ,
	float triggerRadius)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	hSpd = 0;
	yVel = 0;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = false;
	inWaterPrevious = true;
	triggerTimer = -1;
	this->triggerX = triggerX;
	this->triggerY = triggerY;
	this->triggerZ = triggerZ;
	this->triggerRadius = triggerRadius;
	updateTransformationMatrix();
}

void EC_Dolphin::step()
{
	if (triggerTimer == -1)
	{
		setVisible(false);

		float xDiff = Global::gamePlayer->getX() - triggerX;
		float yDiff = Global::gamePlayer->getY() - triggerY;
		float zDiff = Global::gamePlayer->getZ() - triggerZ;

		float dist = sqrtf(xDiff*xDiff + yDiff*yDiff + zDiff*zDiff);

		if (dist < triggerRadius)
		{
			triggerTimer = 0;
			setVisible(true);
			hSpd = 5;
		}
	}
	else
	{
		triggerTimer++;

		float xDiff = hSpd*cosf(toRadians(getRotY()));
		float yDiff = getY();
		float zDiff = hSpd*(-sinf(toRadians(getRotY())));
		
		if (yDiff > 0)
		{
			yVel -= 0.2f;
			hSpd = fmaxf(hSpd - 0.01f, 3);

			if (inWaterPrevious)
			{
				AudioPlayer::play(5, getPosition());
				Vector3f pos(getX(), 5, getZ());
				Vector3f vel(0, 0, 0);
				new Particle(ParticleResources::textureSplash, &pos, &vel, 0, 30, 0, 10, 0, false);
			}

			inWaterPrevious = false;
		}
		else
		{
			if (triggerTimer < 90)
			{
				yVel += 0.75f;
				hSpd = fminf(hSpd + 0.05f, 5);
			}

			if (!inWaterPrevious)
			{
				AudioPlayer::play(5, getPosition());
				Vector3f pos(getX(), 5, getZ());
				Vector3f vel(0, 0, 0);
				new Particle(ParticleResources::textureSplash, &pos, &vel, 0, 30, 0, 10, 0, false);
			}

			inWaterPrevious = true;
		}

		if (yDiff < -150)
		{
			Main_deleteEntity(this);
		}

		if (yVel > 10)
		{
			yVel = 10;
		}
		if (yVel < -10)
		{
			yVel = -10;
		}

		float newRotZ = atan2f(yVel, hSpd);

		setRotZ(toDegrees(newRotZ));

		increasePosition(xDiff, yVel, zDiff);
		updateTransformationMatrix();
	}
}

std::list<TexturedModel*>* EC_Dolphin::getModels()
{
	return &EC_Dolphin::models;
}

void EC_Dolphin::loadStaticModels()
{
	if (EC_Dolphin::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_Dolphin static models...\n");
	#endif

	loadObjModel(&EC_Dolphin::models, "res/Models/EmeraldCoast/", "Dolphin.obj");
}

void EC_Dolphin::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_Dolphin static models...\n");
	#endif

	Entity::deleteModels(&EC_Dolphin::models);
}
