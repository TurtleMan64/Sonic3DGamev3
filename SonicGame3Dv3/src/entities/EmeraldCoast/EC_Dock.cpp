#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecdock.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"
#include "ecshark.h"
#include "../../audio/audioplayer.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EC_Dock::models;
CollisionModel* EC_Dock::cmOriginal;

EC_Dock::EC_Dock()
{
	
}

EC_Dock::EC_Dock(float x, float y, float z, float rotY)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();

	collideModelOriginal = EC_Dock::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/EmeraldCoast/", "DockCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void EC_Dock::step()
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

			float SharkX = Global::ecShark->getX();
			float SharkY = Global::ecShark->getY();
			float SharkZ = Global::ecShark->getZ();

			if (abs(getX() - SharkX) < 45 &&
				abs(getZ() - SharkZ) < 45 &&
				SharkY > 2)
			{
				CollisionChecker::deleteCollideModel(collideModelTransformed);
				collideModelTransformed = nullptr;
				Main_deleteEntity(this);
				AudioPlayer::play(19, getPosition());
			}
		}
	}
}

std::list<TexturedModel*>* EC_Dock::getModels()
{
	return &EC_Dock::models;
}

void EC_Dock::loadStaticModels()
{
	if (EC_Dock::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_Dock static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "Dock.obj");
	for (auto newModel : (*newModels))
	{
		EC_Dock::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (EC_Dock::cmOriginal == nullptr)
	{
		EC_Dock::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "DockCollision");
	}
}

void EC_Dock::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_Dock static models...\n");
	for (auto model : EC_Dock::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_Dock::models.clear();

	if (EC_Dock::cmOriginal != nullptr)
	{
		EC_Dock::cmOriginal->deleteMe();
		delete EC_Dock::cmOriginal;
		Global::countDelete++;
		EC_Dock::cmOriginal = nullptr;
	}
}
