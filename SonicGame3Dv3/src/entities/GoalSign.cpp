#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "goalsign.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/camera.h"
#include "../entities/player.h"
#include "../collision/collisionchecker.h"
#include "../collision/triangle3d.h"
#include "../toolbox/maths.h"
#include "../guis/guimanager.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> GoalSign::models;

int GoalSign::triggersRemaining = 0;

float GoalSign::hitboxR = 6;
float GoalSign::hitboxV = 12;

GoalSign::GoalSign()
{

}

GoalSign::GoalSign(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->scale = 1.5f;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	rotateSpeed = 0;
	GoalSign::triggersRemaining = 0;
}


void GoalSign::step()
{
	if (triggersRemaining <= 0)
	{
		float playerX = Global::gamePlayer->getX();
		float playerY = Global::gamePlayer->getY();
		float playerZ = Global::gamePlayer->getZ();
		float playerHbox = Global::gamePlayer->getHitboxHorizontal();
		float playerVbox = Global::gamePlayer->getHitboxVertical();

		if (playerX > getX() - hitboxR - playerHbox && playerX < getX() + hitboxR + playerHbox &&
			playerZ > getZ() - hitboxR - playerHbox && playerZ < getZ() + hitboxR + playerHbox &&
			playerY > getY() - playerVbox && playerY < getY() + hitboxV)
		{
			if (rotateSpeed == 0)
			{
				//AudioSources.play(29, getPosition());

				GuiManager::stopTimer();

				float speed = Global::gamePlayer->getSpeed() * 2 + 3;
				rotateSpeed = fmin(48, speed);

				if (Global::levelName == "EmeraldCoast.lvl")
				{
					if (GuiManager::getTotalTimer() < 90 &&
						Global::gameRingCount >= 200)
					{
						if (Global::unlockedSonicDoll == false)
						{
							Global::unlockedSonicDoll = true;
							//AudioSources.play(35, getPosition());
							//MainGameLoop.saveSaveFile();
						}
					}
				}
				else if (Global::levelName == "GreenHillZone.lvl")
				{
					if (GuiManager::getTotalTimer() < 40)
					{
						if (Global::unlockedMechaSonic == false)
						{
							Global::unlockedMechaSonic = true;
							//AudioSources.play(35, getPosition());
							//MainGameLoop.saveSaveFile();
						}
					}
				}
				else if (Global::levelName == "MetalHarbor.lvl")
				{
					if (GuiManager::getTotalTimer() < 90)
					{
						if (Global::unlockedDage4 == false)
						{
							Global::unlockedDage4 = true;
							//AudioSources.play(35, getPosition());
							//MainGameLoop.saveSaveFile();
						}
					}
				}
			}
		}

		float minDec = fmax(0.02, rotateSpeed / 100);
		rotateSpeed = fmax(rotateSpeed - minDec, 0);

		increaseRotation(0, rotateSpeed, 0);
		updateTransformationMatrix();
		setVisible(true);
	}
	else
	{
		setVisible(false);
	}
}

std::list<TexturedModel*>* GoalSign::getModels()
{
	return &GoalSign::models;
}

void GoalSign::loadStaticModels()
{
	if (GoalSign::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading GoalSign static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/GoalSign/", "GoalSign.obj");
	for (auto newModel : (*newModels))
	{
		GoalSign::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


}

void GoalSign::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting GoalSign static models...\n");
	for (auto model : GoalSign::models)
	{
		model->deleteMe(); //delete opengl ids
		delete model;
		Global::countDelete++;
	}

	GoalSign::models.clear();
}

void GoalSign::addTrigger()
{
	GoalSign::triggersRemaining++;
}

void GoalSign::removeTrigger()
{
	GoalSign::triggersRemaining--;
}