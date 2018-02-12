#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "spinner.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/player.h"
#include "../toolbox/maths.h"
#include "../animation/body.h"
#include "../entities/camera.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> Spinner::modelsBody;
std::list<TexturedModel*> Spinner::modelsBlades;

float Spinner::colHorizontal = 6;
float Spinner::colVertical = 7.3f;

Spinner::Spinner()
{

}

Spinner::Spinner(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();

	blades = new Body(&Spinner::modelsBlades);
	blades->setVisible(true);
	Global::countNew++;
	Main_addEntity(blades);
	blades->setPosition(&position);
}

void Spinner::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
		blades->setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
			blades->setVisible(false);
		}
		else
		{
			setVisible(true);
			blades->setVisible(true);
			if (Global::gamePlayer->getX() > getX() - colHorizontal - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getX() < getX() + colHorizontal + Global::gamePlayer->getHitboxHorizontal() &&
				Global::gamePlayer->getZ() > getZ() - colHorizontal - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getZ() < getZ() + colHorizontal + Global::gamePlayer->getHitboxHorizontal() &&
				Global::gamePlayer->getY() + Global::gamePlayer->getHitboxVertical() >= getY() - colVertical && Global::gamePlayer->getY() - Global::gamePlayer->getHitboxVertical() <= getY() + colVertical)
			{
				if (Global::gamePlayer->isVulnerable())
				{
					Global::gamePlayer->takeDamage(getPosition());
				}
				else
				{
					die();
					Global::gamePlayer->rebound(getPosition());
				}
			}

			float xDiff = (getX() - Global::gamePlayer->getX());
			float zDiff = (getZ() - Global::gamePlayer->getZ());
			setRotY(toDegrees(atan2f(zDiff, -xDiff)));

			blades->increaseRotation(0, 25, 0);
			updateTransformationMatrix();
			blades->updateTransformationMatrix();
		}
	}
}

void Spinner::die()
{
	//AudioSources.play(28, getPosition());

	Main_deleteEntity(this);
	Main_deleteEntity(blades);

	float height = 10.0f;
	float spread = 20.0f;

	for (int i = 7; i != 0; i--)
	{
		/*
		new Particle(ParticleResources.textureExplosion1,
			new Vector3f(getX() + spread*(float)(Math.random() - 0.5),
				getY() + spread*(float)(Math.random() - 0.5) + height,
				getZ() + spread*(float)(Math.random() - 0.5)), new Vector3f(0, 0, 0),
			0, 45, 0, 3 * (float)Math.random() + 6, 0);
			*/
	}

	/*
	new Particle(ParticleResources.textureExplosion2,
		new Vector3f(getX(),
			getY() + height,
			getZ()), new Vector3f(0, 0, 0),
		0, 55, 0, 20, 0);
		*/
}

std::list<TexturedModel*>* Spinner::getModels()
{
	return &Spinner::modelsBody;
}

void Spinner::loadStaticModels()
{
	if (Spinner::modelsBody.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading Spinner static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/Spinner/", "Body.obj");
	for (auto newModel : (*newModels))
	{
		Spinner::modelsBody.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	std::list<TexturedModel*>* newModels2 = loadObjModel("res/Models/Spinner/", "Blades.obj");
	for (auto newModel : (*newModels2))
	{
		Spinner::modelsBlades.push_back(newModel);
	}
	delete newModels2;
	Global::countDelete++;
}

void Spinner::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting Spinner static models...\n");
	for (auto model : Spinner::modelsBody)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	Spinner::modelsBody.clear();


	for (auto model : Spinner::modelsBlades)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	Spinner::modelsBlades.clear();
}

bool Spinner::canHomingAttackOn()
{
	return true;
}