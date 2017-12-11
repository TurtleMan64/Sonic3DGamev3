#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "player.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> Player::models;

Player::Player()
{

}

Player::Player(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

void Player::step()
{
	//increaseRotation(0, 1, 0);
}

std::list<TexturedModel*>* Player::getModels()
{
	return &Player::models;
}

void Player::loadStaticModels()
{
	if (Player::models.size() > 0)
	{
		std::fprintf(stdout, "Player models gone astray");
		return;
	}

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/Amy/", "Head.obj");
	for (auto newModel : (*newModels))
	{
		Player::models.push_back(newModel);
	}
	delete newModels;
}

void Player::deleteStaticModels()
{
	for (auto model : Player::models)
	{
		model->deleteMe(); //delete opengl ids
		delete model;
	}

	Player::models.clear();
}