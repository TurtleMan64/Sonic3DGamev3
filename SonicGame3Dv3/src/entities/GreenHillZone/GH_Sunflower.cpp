#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ghsunflower.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../animation/body.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> GH_Sunflower::modelsBase;
std::list<TexturedModel*> GH_Sunflower::modelsTop;
std::list<TexturedModel*> GH_Sunflower::modelsTop2;

GH_Sunflower::GH_Sunflower()
{
	
}

GH_Sunflower::GH_Sunflower(float x, float y, float z, float rotY, float scale)
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

	petals = new Body(&GH_Sunflower::modelsTop);
	petals->setVisible(true);
	INCR_NEW
	Main_addEntity(petals);
	petals->setPosition(&position);
	petals->increasePosition(0, 25.0f, 0);
	petals->setRotY(rotY);
	petals->updateTransformationMatrix();
}

void GH_Sunflower::step()
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

			if ((Global::gameClock/20) % 2 == 0)
			{
				petals->setModels(&GH_Sunflower::modelsTop);
				petals->updateTransformationMatrix();
			}
			else
			{
				petals->setModels(&GH_Sunflower::modelsTop2);
				petals->updateTransformationMatrix();
			}
		}
	}
}

std::list<TexturedModel*>* GH_Sunflower::getModels()
{
	return &GH_Sunflower::modelsBase;
}

void GH_Sunflower::loadStaticModels()
{
	if (GH_Sunflower::modelsBase.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading GH_Sunflower static models...\n");
	#endif

	loadObjModel(&GH_Sunflower::modelsBase, "res/Models/GreenHillZone/Objects/", "GreenHillSunflowerBase.obj");
	loadObjModel(&GH_Sunflower::modelsTop,  "res/Models/GreenHillZone/Objects/", "GreenHillSunflowerTop.obj");
	loadObjModel(&GH_Sunflower::modelsTop2, "res/Models/GreenHillZone/Objects/", "GreenHillSunflowerTop2.obj");
}

void GH_Sunflower::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting GH_Sunflower static models...\n");
	#endif

	Entity::deleteModels(&GH_Sunflower::modelsBase);
	Entity::deleteModels(&GH_Sunflower::modelsTop);
	Entity::deleteModels(&GH_Sunflower::modelsTop2);
}
