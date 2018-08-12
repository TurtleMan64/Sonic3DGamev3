#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecshark.h"
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

std::list<TexturedModel*> EC_Shark::models;

EC_Shark::EC_Shark()
{
	
}

EC_Shark::EC_Shark(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	initX = x;
	initY = y;
	initZ = z;
	xVel = 0;
	yVel = 0;
	zVel = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = false;
	seeTimer = 0;
	inWaterPrevious = true;
	updateTransformationMatrix();
}

void EC_Shark::step()
{
	if (seeTimer == 0)
	{
		if (abs(getX() - Global::gamePlayer->getX()) > 100)
		{
			setVisible(false);
			seeTimer = 0;
		}
		else
		{
			if (abs(getZ() - Global::gamePlayer->getZ()) > 250)
			{
				setVisible(false);
				seeTimer = 0;
			}
			else
			{
				setVisible(true);
				if (seeTimer == 0)
				{
					seeTimer = 1;
					setPosition(initX, initY, initZ);
					xVel = 0;
					yVel = 1;
					zVel = 0;
				}
			}
		}
	}

	if (seeTimer > 0)
	{
		seeTimer++;

		float xDiff = Global::gamePlayer->getX() - getX();
		float yDiff = 0 - getY(); //Global::gamePlayer->getY() - getY();
		float zDiff = Global::gamePlayer->getZ() - getZ();

		float diffAng = atan2f(-zDiff, xDiff);

		float hSpd = sqrtf(xDiff*xDiff + zDiff*zDiff);

		float factor = hSpd / 20;

		if (factor < 5.25f)
		{
			xVel = 5.25f * cos(diffAng);
			zVel = -5.25f * sin(diffAng);
		}
		else
		{
			xVel = factor * cos(diffAng);
			zVel = -factor * sin(diffAng);
		}
		
		if (yDiff > 0)
		{
			yVel += 0.5f;

			if (inWaterPrevious == false)
			{
				AudioPlayer::play(5, getPosition());
				Vector3f pos(getX(), 25, getZ());
				Vector3f vel(0, 0, 0);
				new Particle(ParticleResources::textureSplash, &pos, &vel, 0, 40, 0, 40, 0, false);
			}

			inWaterPrevious = true;
		}
		else
		{
			yVel -= 0.5f;

			if (inWaterPrevious == true)
			{
				AudioPlayer::play(5, getPosition());
				Vector3f pos(getX(), 25, getZ());
				Vector3f vel(0, 0, 0);
				new Particle(ParticleResources::textureSplash, &pos, &vel, 0, 40, 0, 40, 0, false);
			}

			inWaterPrevious = false;
		}

		if (yVel > 10)
		{
			yVel = 10;
		}
		if (yVel < -10)
		{
			yVel = -10;
		}

		float spd = sqrtf(xVel*xVel + zVel*zVel);
		float newRotZ = atan2f(yVel, spd);

		setRotY(toDegrees(diffAng));//+5*cosf(seeTimer/10.0f));
		setRotZ(toDegrees(newRotZ));

		increasePosition(xVel, yVel, zVel);
		updateTransformationMatrix();

		if (getX() > 5500)
		{
			setVisible(false);
			seeTimer = 0;
			setPosition(initX, initY, initZ);
		}

		xDiff = Global::gamePlayer->getX() - getX();
		yDiff = Global::gamePlayer->getY() - getY();
		zDiff = Global::gamePlayer->getZ() - getZ();

		float dist = sqrtf(xDiff*xDiff + yDiff*yDiff + zDiff*zDiff);

		if (dist < 60)
		{
			Global::gamePlayer->takeDamage(getPosition());
		}
	}
}

std::list<TexturedModel*>* EC_Shark::getModels()
{
	return &EC_Shark::models;
}

void EC_Shark::loadStaticModels()
{
	if (EC_Shark::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_Shark static models...\n");
	#endif

	loadObjModel(&EC_Shark::models, "res/Models/EmeraldCoast/", "Shark.obj");
}

void EC_Shark::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_Shark static models...\n");
	#endif
	
	Entity::deleteModels(&EC_Shark::models);
}
