#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecseagull.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../audio/audioplayer.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> EC_Seagull::models;

EC_Seagull::EC_Seagull()
{
	
}

EC_Seagull::EC_Seagull(
	float x, float y, float z, 
	float startAngle,
	float flySpeed,
	float flyRadiusBase,
	float flyRadiusAmplitude,
	float flyRadiusChange,
	float flyHeightAmplitude,
	float flyHeightDelta)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = false;
	centerX = x;
	centerY = y;
	centerZ = z;

	flyAngle = startAngle;
	flyAngleDelta = flySpeed;

	this->flyRadiusBase = flyRadiusBase;
	this->flyRadiusAmplitude = flyRadiusAmplitude;
	flyRadiusDelta = flyRadiusChange;
	flyRadiusProgression = 0;

	flyHeightBase = y;
	this->flyHeightAmplitude = flyHeightAmplitude;
	this->flyHeightDelta = flyHeightDelta;
	flyHeightProgression = 0;

	soundTimer = (int)(300*Maths::random());

	updateTransformationMatrix();
}

void EC_Seagull::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
		}
		else
		{
			setVisible(true);

			soundTimer--;
			if (soundTimer < 0)
			{
				soundTimer = 300;
			}

			prevX = getX();
			prevY = getY();
			prevZ = getZ();

			flyAngle += flyAngleDelta;
			flyRadiusProgression += flyRadiusDelta;
			flyHeightProgression += flyHeightDelta;

			float flyRadius = flyRadiusAmplitude * sinf(toRadians(flyRadiusProgression)) + flyRadiusBase;

			position.x = centerX + flyRadius * cosf(toRadians(flyAngle));
			position.z = centerZ - flyRadius * sinf(toRadians(flyAngle));

			position.y = flyHeightAmplitude * sinf(toRadians(flyHeightProgression)) + flyHeightBase;

			float xDiff = position.x - prevX;
			float yDiff = position.y - prevY;
			float zDiff = position.z - prevZ;

			rotY = toDegrees(atan2f(-zDiff, xDiff));
			rotZ = toDegrees(atan2f(yDiff, sqrtf(xDiff*xDiff+zDiff*zDiff)));

			updateTransformationMatrix();

			float dx = getX() - Global::gameCamera->getPosition()->x;
			float dy = getY() - Global::gameCamera->getPosition()->y;
			float dz = getZ() - Global::gameCamera->getPosition()->z;

			if (dx*dx + dy*dy + dz*dz < 300 * 300 &&
				soundTimer == 0)
			{
				AudioPlayer::play(20, getPosition());
			}
		}
	}
}

std::list<TexturedModel*>* EC_Seagull::getModels()
{
	return &EC_Seagull::models;
}

void EC_Seagull::loadStaticModels()
{
	if (EC_Seagull::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_Seagull static models...\n");
	#endif

	loadObjModel(&EC_Seagull::models, "res/Models/EmeraldCoast/", "Seagull.obj");
}

void EC_Seagull::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_Seagull static models...\n");
	#endif

	Entity::deleteModels(&EC_Seagull::models);
}
