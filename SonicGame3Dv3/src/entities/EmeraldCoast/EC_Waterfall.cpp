#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecwaterfall.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EC_Waterfall::models;

EC_Waterfall::EC_Waterfall()
{
	
}

EC_Waterfall::EC_Waterfall(float x, float y, float z, float rotY, float scale)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = 0;
	this->scale = scale;
	this->visible = true;
	updateTransformationMatrix();
}

void EC_Waterfall::step()
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
		}
	}
}

std::list<TexturedModel*>* EC_Waterfall::getModels()
{
	return &EC_Waterfall::models;
}

void EC_Waterfall::loadStaticModels()
{
	if (EC_Waterfall::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_Waterfall static models...\n");
	#endif

	loadObjModel(&EC_Waterfall::models, "res/Models/EmeraldCoast/", "WaterfallDouble.obj");
}

void EC_Waterfall::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_Waterfall static models...\n");
	#endif

	Entity::deleteModels(&EC_Waterfall::models);
}


std::string EC_Waterfall::getName()
{
	return "EC_Waterfall";
}