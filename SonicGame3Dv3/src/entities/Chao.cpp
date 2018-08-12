#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "chao.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/camera.h"
#include "../entities/controllableplayer.h"
#include "../toolbox/maths.h"
#include "../guis/guimanager.h"
#include "../audio/audioplayer.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> Chao::models;

float Chao::hitboxR = 3;
float Chao::hitboxV = 8;

Chao::Chao()
{

}

Chao::Chao(float x, float y, float z, float rotY)
{
	if (!Global::gameIsChaoMode)
	{
		Main_deleteEntity(this);
		return;
	}

	position.x = x;
	position.y = y;
	position.z = z;
	scale = 1.0f;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	isFound = false;
	updateTransformationMatrix();
}


void Chao::step()
{
	if (!isFound)
	{
		float playerX    = Global::gamePlayer->getX();
		float playerY    = Global::gamePlayer->getY();
		float playerZ    = Global::gamePlayer->getZ();
		float playerHbox = Global::gamePlayer->getHitboxHorizontal();
		float playerVbox = Global::gamePlayer->getHitboxVertical();

		if (playerX > getX() - hitboxR - playerHbox && playerX < getX() + hitboxR + playerHbox &&
			playerZ > getZ() - hitboxR - playerHbox && playerZ < getZ() + hitboxR + playerHbox &&
			playerY > getY() - playerVbox && playerY < getY() + hitboxV)
		{
			isFound = true;
			
			//AudioPlayer::play(2, getPosition());

			GuiManager::stopTimer();

			Global::finishStageTimer = 0;
		}
	}
}

std::list<TexturedModel*>* Chao::getModels()
{
	return &Chao::models;
}

void Chao::loadStaticModels()
{
	if (Chao::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading Chao static models...\n");
	#endif

	loadObjModel(&Chao::models, "res/Models/Chao/", "Chao.obj");
}

void Chao::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting Chao static models...\n");
	#endif

	Entity::deleteModels(&Chao::models);
}
