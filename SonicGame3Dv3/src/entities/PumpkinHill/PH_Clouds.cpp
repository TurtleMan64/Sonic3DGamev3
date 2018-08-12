#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "phclouds.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/controllableplayer.h"
#include "../../toolbox/maths.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> PH_Clouds::models;



PH_Clouds::PH_Clouds(float y, float spinSpeed)
{
	position.x = 0;
	position.y = y;
	position.z = 0;
	scale = 60.0f; //60.0f
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	this->spinSpeed = spinSpeed;
	updateTransformationMatrix();
}


void PH_Clouds::step()
{
	position.x = Global::gamePlayer->getX();
	position.z = Global::gamePlayer->getZ();
	rotY += spinSpeed;
	updateTransformationMatrix();

	if (Global::gamePlayer->getY() < getY()+40)
	{
		float playerYVel = Global::gamePlayer->getyVel();
		if (playerYVel < -1.0f)
		{
			Global::gamePlayer->setyVel(playerYVel*0.85f);
		}
		else
		{
			if (playerYVel < 6.0f)
			{
				Global::gamePlayer->setyVel(playerYVel+0.5f);
			}
		}
	}
}

std::list<TexturedModel*>* PH_Clouds::getModels()
{
	return &PH_Clouds::models;
}

void PH_Clouds::loadStaticModels()
{
	if (PH_Clouds::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading PH_Clouds static models...\n");
	#endif

	loadObjModel(&PH_Clouds::models, "res/Models/PumpkinHill/Objects/", "Clouds.obj");
}

void PH_Clouds::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting PH_Clouds static models...\n");
	#endif

	Entity::deleteModels(&PH_Clouds::models);
}
