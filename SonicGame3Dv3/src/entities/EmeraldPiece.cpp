#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "emeraldpiece.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/camera.h"
#include "../entities/playersonic.h"
#include "../toolbox/maths.h"
#include "../audio/audioplayer.h"
#include "../particles/particle.h"
#include "../particles/particleresources.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EmeraldPiece::models;

float EmeraldPiece::hitboxH = 1.5f*2;
float EmeraldPiece::hitboxV = 3.4f*2;

EmeraldPiece::EmeraldPiece()
{

}

EmeraldPiece::EmeraldPiece(float x, float y, float z, int pieceNumber)
{
	position.x = x;
	position.y = y;
	position.z = z;
	this->pieceNumber = pieceNumber;
	scale = 2.0f;
}

void EmeraldPiece::step()
{
	increaseRotation(0, 10, 0);

	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST_HIGH)
	{
		setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST_HIGH)
		{
			setVisible(false);
		}
		else
		{
			setVisible(true);

			if (Global::gamePlayer->getX() > getX() - hitboxH - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getX() < getX() + hitboxH + Global::gamePlayer->getHitboxHorizontal() &&
				Global::gamePlayer->getZ() > getZ() - hitboxH - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getZ() < getZ() + hitboxH + Global::gamePlayer->getHitboxHorizontal() &&
				Global::gamePlayer->getY() > getY() - hitboxV - Global::gamePlayer->getHitboxVertical()   && Global::gamePlayer->getY() < getY() + hitboxV)
			{
				AudioPlayer::play(35, getPosition());

				for (int i = 0; i < 10; i++)
				{
					Vector3f pos(
						getX() + Maths::random() * 8 - 4,
						getY() + Maths::random() * 8 - 4,
						getZ() + Maths::random() * 8 - 4);

					Vector3f vel(0, 0.4f, 0);

					new Particle(ParticleResources::textureSparkleGreen, &pos, &vel,
						0.025f, 30, 0, 7, -(7.0f / 30.0f), false);
				}

				Main_deleteEntity(this);
				return;
			}

			updateTransformationMatrix();
		}
	}
}

int EmeraldPiece::getPieceNumber()
{
	return pieceNumber;
}

std::list<TexturedModel*>* EmeraldPiece::getModels()
{
	return &EmeraldPiece::models;
}

void EmeraldPiece::loadStaticModels()
{
	if (EmeraldPiece::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EmeraldPiece static models...\n");

	loadObjModel(&EmeraldPiece::models, "res/Models/EmeraldPiece/", "EmeraldPiece.obj");
}

void EmeraldPiece::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EmeraldPiece static models...\n");

	Entity::deleteModels(&EmeraldPiece::models);
}
