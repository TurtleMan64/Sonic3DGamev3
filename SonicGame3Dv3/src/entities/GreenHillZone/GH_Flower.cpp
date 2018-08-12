#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ghflower.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../animation/body.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> GH_Flower::modelsBase;
std::list<TexturedModel*> GH_Flower::modelsTop;

GH_Flower::GH_Flower()
{
	
}

GH_Flower::GH_Flower(float x, float y, float z, float rotY, float scale)
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

	petals = new Body(&GH_Flower::modelsTop);
	petals->setVisible(true);
	INCR_NEW
	Main_addEntity(petals);
	petals->setPosition(&position);
	petals->setRotY(rotY);
	petals->updateTransformationMatrix();
}

void GH_Flower::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
		petals->setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
			petals->setVisible(false);
		}
		else
		{
			setVisible(true);
			petals->setVisible(true);

			int val = Global::gameClock % 340;

			if (val == 0)
			{
				petals->setY(getY());
				petals->updateTransformationMatrix();
			}
			else if (val == 120 || val == 300)
			{
				petals->setY(getY()+1.5f);
				petals->updateTransformationMatrix();
			}
			else if (val == 160)
			{
				petals->setY(getY()+3.0f);
				petals->updateTransformationMatrix();
			}
		}
	}
}

std::list<TexturedModel*>* GH_Flower::getModels()
{
	return &GH_Flower::modelsBase;
}

void GH_Flower::loadStaticModels()
{
	if (GH_Flower::modelsBase.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading GH_Flower static models...\n");
	#endif

	loadObjModel(&GH_Flower::modelsBase, "res/Models/GreenHillZone/Objects/", "GreenHillPFlowerBase.obj");
	loadObjModel(&GH_Flower::modelsTop,  "res/Models/GreenHillZone/Objects/", "GreenHillPFlowerTop.obj");
}

void GH_Flower::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting GH_Flower static models...\n");
	#endif

	Entity::deleteModels(&GH_Flower::modelsBase);
	Entity::deleteModels(&GH_Flower::modelsTop);
}
