#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ghgrass.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> GH_Grass::models;

GH_Grass::GH_Grass()
{
	
}

GH_Grass::GH_Grass(float x, float y, float z, float rotY, float scale)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	this->scale = scale;
	visible = true;
	updateTransformationMatrix();
}

void GH_Grass::step()
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

std::list<TexturedModel*>* GH_Grass::getModels()
{
	return &GH_Grass::models;
}

void GH_Grass::loadStaticModels()
{
	if (GH_Grass::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading GH_Grass static models...\n");
	#endif

	loadObjModel(&GH_Grass::models, "res/Models/GreenHillZone/Objects/", "GreenHillGrass.obj");
}

void GH_Grass::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting GH_Grass static models...\n");
	#endif

	Entity::deleteModels(&GH_Grass::models);
}
