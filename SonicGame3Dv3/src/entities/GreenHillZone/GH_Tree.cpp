#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ghtree.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> GH_Tree::models;

GH_Tree::GH_Tree()
{
	
}

GH_Tree::GH_Tree(float x, float y, float z, float rotY, float scale)
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

void GH_Tree::step()
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

std::list<TexturedModel*>* GH_Tree::getModels()
{
	return &GH_Tree::models;
}

void GH_Tree::loadStaticModels()
{
	if (GH_Tree::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading GH_Tree static models...\n");
	#endif

	loadObjModel(&GH_Tree::models, "res/Models/GreenHillZone/Objects/", "GreenHillTree.obj");
}

void GH_Tree::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting GH_Tree static models...\n");
	#endif

	Entity::deleteModels(&GH_Tree::models);
}
