#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "goaltrigger.h"
#include "goalsign.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "controllableplayer.h"

#include <list>

std::list<TexturedModel*> GoalTrigger::models;


GoalTrigger::GoalTrigger()
{

}

GoalTrigger::GoalTrigger(float x, float y, float z, float scale)
{
	position.x = x;
	position.y = y;
	position.z = z;
	this->scale = scale;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
    hitboxH = scale/2;
    hitboxV = scale/2;
    visible = false;
	isActive = true;
    GoalSign::addTrigger();
	updateTransformationMatrix();
}


void GoalTrigger::step()
{
    float playerX = Global::gamePlayer->getX();
    float playerY = Global::gamePlayer->getY();
    float playerZ = Global::gamePlayer->getZ();
    float playerHbox = Global::gamePlayer->getHitboxHorizontal();
    float playerVbox = Global::gamePlayer->getHitboxVertical();
    
	if (playerX > getX()-hitboxH-playerHbox && playerX < getX()+hitboxH+playerHbox &&
		playerZ > getZ()-hitboxH-playerHbox && playerZ < getZ()+hitboxH+playerHbox &&
		playerY > getY()-hitboxV-playerVbox && playerY < getY()+hitboxV &&
		isActive)
    {
		isActive = false;
        GoalSign::removeTrigger();

		if (isActive)
		{
			activeTimer = 240;
			isActive = false;
		}
    }

	if (activeTimer == 1)
	{
		isActive = true;
	}
	activeTimer = std::max(activeTimer-1, 0);

	//visible = isActive;
}

bool GoalTrigger::isGoalTrigger()
{
	return true;
}

std::list<TexturedModel*>* GoalTrigger::getModels()
{
	return &GoalTrigger::models;
}

void GoalTrigger::loadStaticModels()
{
	if (GoalTrigger::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading GoalTrigger static models...\n");
	#endif

	loadObjModel(&GoalTrigger::models, "res/Models/Box/", "Box.obj");
}

void GoalTrigger::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting GoalTrigger static models...\n");
	#endif

	Entity::deleteModels(&GoalTrigger::models);
}
