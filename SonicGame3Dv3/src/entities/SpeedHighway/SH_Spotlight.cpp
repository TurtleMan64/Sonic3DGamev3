#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "shspotlight.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../animation/body.h"
#include "../camera.h"
#include "../../toolbox/maths.h"

#include <list>
#include <cmath>

std::list<TexturedModel*> SH_Spotlight::models;
std::list<TexturedModel*> SH_Spotlight::modelsLight;

SH_Spotlight::SH_Spotlight(float x, float y, float z,
	float xRot, float yRot, float zRot)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = xRot;
	rotY = yRot;
	rotZ = zRot;
	initRotZ = zRot;
	scale = 1;
	visible = true;
	timer = rand();
	updateTransformationMatrixSADX();

	light = new Body(&SH_Spotlight::modelsLight);
	light->setVisible(true);
	INCR_NEW
	Main_addTransparentEntity(light);
	light->setPosition(&position);
	light->setRotX(xRot);
	light->setRotY(yRot);
	light->setRotZ(zRot);
	light->setScale(1);
	light->updateTransformationMatrixSADX();
}

void SH_Spotlight::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST_HIGH)
	{
		setVisible(false);
		light->setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST_HIGH)
		{
			setVisible(false);
			light->setVisible(false);
		}
		else
		{
			setVisible(true);
			light->setVisible(true);
			timer++;

			rotZ = initRotZ+10*sinf(timer/40.0f);
			light->setRotZ(rotZ);
			updateTransformationMatrixSADX();
			light->updateTransformationMatrixSADX();
		}
	}
}

std::list<TexturedModel*>* SH_Spotlight::getModels()
{
	return &SH_Spotlight::models;
}

void SH_Spotlight::loadStaticModels()
{
	if (SH_Spotlight::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading SH_Spotlight static models...\n");
	#endif

	loadObjModel(&SH_Spotlight::models, "res/Models/SpeedHighway/", "Spotlight.obj");
	loadObjModel(&SH_Spotlight::modelsLight, "res/Models/SpeedHighway/", "SpotlightLight.obj");
}

void SH_Spotlight::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting SH_Spotlight static models...\n");
	#endif

	Entity::deleteModels(&SH_Spotlight::models);
	Entity::deleteModels(&SH_Spotlight::modelsLight);
}
