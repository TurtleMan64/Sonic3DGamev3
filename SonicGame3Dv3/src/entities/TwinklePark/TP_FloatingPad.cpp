#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "tpfloatingpad.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> TP_FloatingPad::models;
CollisionModel* TP_FloatingPad::cmOriginal;

TP_FloatingPad::TP_FloatingPad()
{
	
}

TP_FloatingPad::TP_FloatingPad(float x, float y, float z, float rotY)
{
	position.x = x;
	position.y = y;
	origHeight = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();

	collideModelOriginal = TP_FloatingPad::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/TwinklePark/", "FloatingPad");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void TP_FloatingPad::step()
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

std::list<TexturedModel*>* TP_FloatingPad::getModels()
{
	return &TP_FloatingPad::models;
}

void TP_FloatingPad::loadStaticModels()
{
	if (TP_FloatingPad::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading TP_FloatingPad static models...\n");
	#endif

	loadObjModel(&TP_FloatingPad::models, "res/Models/TwinklePark/", "FloatingPad.obj");

	if (TP_FloatingPad::cmOriginal == nullptr)
	{
		TP_FloatingPad::cmOriginal = loadCollisionModel("Models/TwinklePark/", "FloatingPad");
	}
}

void TP_FloatingPad::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting TP_FloatingPad static models...\n");
	#endif

	Entity::deleteModels(&TP_FloatingPad::models);
	Entity::deleteCollisionModel(&TP_FloatingPad::cmOriginal);
}
