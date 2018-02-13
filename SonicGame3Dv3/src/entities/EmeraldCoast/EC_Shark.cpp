#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecshark.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

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
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	initX = x;
	initY = y;
	initZ = z;
	xVel = 0;
	yVel = 0;
	zVel = 0;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = false;
	seeTimer = 0;
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
		}
		else
		{
			yVel -= 0.5f;
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

		if (getX() > 5666)
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

	std::fprintf(stdout, "Loading EC_Shark static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "Shark.obj");
	for (auto newModel : (*newModels))
	{
		EC_Shark::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void EC_Shark::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_Shark static models...\n");
	for (auto model : EC_Shark::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_Shark::models.clear();
}
