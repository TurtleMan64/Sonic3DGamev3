#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "shlamppost.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../animation/body.h"
#include "../camera.h"

#include <list>

std::list<TexturedModel*> SH_Lamppost::models;
std::list<TexturedModel*> SH_Lamppost::modelsLight;

SH_Lamppost::SH_Lamppost(float x, float y, float z,
	float xRot, float yRot, float zRot)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = xRot;
	rotY = yRot;
	rotZ = zRot;
	scale = 1;
	visible = true;
	updateTransformationMatrixSADX();

	light = new Body(&SH_Lamppost::modelsLight);
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

void SH_Lamppost::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
		light->setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
			light->setVisible(false);
		}
		else
		{
			setVisible(true);
			light->setVisible(true);
		}
	}
}

std::list<TexturedModel*>* SH_Lamppost::getModels()
{
	return &SH_Lamppost::models;
}

void SH_Lamppost::loadStaticModels()
{
	if (SH_Lamppost::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading SH_Lamppost static models...\n");
	#endif

	loadObjModel(&SH_Lamppost::models, "res/Models/SpeedHighway/", "Lamppost.obj");
	loadObjModel(&SH_Lamppost::modelsLight, "res/Models/SpeedHighway/", "LamppostLight.obj");
}

void SH_Lamppost::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting SH_Lamppost static models...\n");
	#endif

	Entity::deleteModels(&SH_Lamppost::models);
	Entity::deleteModels(&SH_Lamppost::modelsLight);
}
