#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "tpfloatingpad.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
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

	std::fprintf(stdout, "Loading TP_FloatingPad static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/TwinklePark/", "FloatingPad.obj");
	for (auto newModel : (*newModels))
	{
		TP_FloatingPad::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (TP_FloatingPad::cmOriginal == nullptr)
	{
		TP_FloatingPad::cmOriginal = loadCollisionModel("Models/TwinklePark/", "FloatingPad");
	}
}

void TP_FloatingPad::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting TP_FloatingPad static models...\n");
	for (auto model : TP_FloatingPad::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	TP_FloatingPad::models.clear();

	if (TP_FloatingPad::cmOriginal != nullptr)
	{
		TP_FloatingPad::cmOriginal->deleteMe();
		delete TP_FloatingPad::cmOriginal;
		Global::countDelete++;
		TP_FloatingPad::cmOriginal = nullptr;
	}
}
