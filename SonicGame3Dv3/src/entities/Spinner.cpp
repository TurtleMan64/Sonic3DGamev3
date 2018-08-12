#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "spinner.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../toolbox/maths.h"
#include "../animation/body.h"
#include "../entities/camera.h"
#include "../audio/audioplayer.h"
#include "../particles/particleresources.h"
#include "../particles/particle.h"

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
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();

	blades = new Body(&Spinner::modelsBlades);
	blades->setVisible(true);
	INCR_NEW
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
	AudioPlayer::play(3, getPosition());

	Global::gamePlayer->increaseCombo();

	Main_deleteEntity(this);
	Main_deleteEntity(blades);

	float height = 10.0f;
	float spread = 20.0f;

	for (int i = 7; i != 0; i--)
	{
		Vector3f pos(
			getX() + spread*(Maths::random() - 0.5f),
			getY() + spread*(Maths::random() - 0.5f) + height,
			getZ() + spread*(Maths::random() - 0.5f));

		Vector3f vel(0, 0, 0);

		new Particle(ParticleResources::textureExplosion1, &pos, &vel,
			0, 45, 0, 3 * Maths::random() + 6, 0, false);
	}

	Vector3f pos(
		getX(),
		getY() + height,
		getZ());

	Vector3f vel(0, 0, 0);
	
	new Particle(ParticleResources::textureExplosion2, &pos, &vel,
		0, 55, 0, 20, 0, false);

	Global::gameScore += 100;
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

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading Spinner static models...\n");
	#endif

	loadObjModel(&Spinner::modelsBody,   "res/Models/Spinner/", "Body.obj");
	loadObjModel(&Spinner::modelsBlades, "res/Models/Spinner/", "Blades.obj");
}

void Spinner::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting Spinner static models...\n");
	#endif

	Entity::deleteModels(&Spinner::modelsBody);
	Entity::deleteModels(&Spinner::modelsBlades);
}

bool Spinner::canHomingAttackOn()
{
	return true;
}

Vector3f Spinner::getHomingCenter()
{
	return Vector3f(getPosition());
}

bool Spinner::isEnemy()
{
	return true;
}