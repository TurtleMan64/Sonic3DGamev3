#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "emeraldpiece.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/camera.h"
#include "../entities/controllableplayer.h"
#include "../toolbox/maths.h"
#include "../audio/audioplayer.h"
#include "../particles/particle.h"
#include "../particles/particleresources.h"
#include "emeraldmanager.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EmeraldPiece::models;

float EmeraldPiece::hitboxH = 1.5f*2;
float EmeraldPiece::hitboxV = 3.4f*2;
float EmeraldPiece::baseScale = 2.0f;
int   EmeraldPiece::lastPieceCollectedTimestamp = 0;

EmeraldPiece::EmeraldPiece()
{

}

EmeraldPiece::EmeraldPiece(
	float x, float y, float z, 
	int pieceNumber, int isDiggable, 
	float digSizeX, float digSizeY, float digSizeZ,
	int hardModePiece)
{
	position.x = x;
	position.y = y;
	position.z = z;
	this->pieceNumber = pieceNumber;
	this->isDiggable = (isDiggable != 0);
	this->digSizeX = digSizeX;
	this->digSizeY = digSizeY;
	this->digSizeZ = digSizeZ;
	this->hardModePiece = false;
	if (hardModePiece != 0)
	{
		this->hardModePiece = hardModePiece;
	}
	collectTimer = 0;
	scale = EmeraldPiece::baseScale;
	EmeraldPiece::lastPieceCollectedTimestamp = Global::gameClock;
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

			if (collectTimer == 0)
			{
				bool collected = false;

				if (isDiggable)
				{
					if (Global::gamePlayer->getDiggingTimer() == 20)
					{
						float xDiff = Global::gamePlayer->getX() - getX();
						float yDiff = Global::gamePlayer->getY() - getY();
						float zDiff = Global::gamePlayer->getZ() - getZ();
						float diff = xDiff*xDiff + yDiff*yDiff + zDiff*zDiff;

						if (diff < 40*40)
						{
							collected = true;
						}
					}
				}
				
				if (Global::gamePlayer->getX() > getX() - hitboxH - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getX() < getX() + hitboxH + Global::gamePlayer->getHitboxHorizontal() &&
					Global::gamePlayer->getZ() > getZ() - hitboxH - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getZ() < getZ() + hitboxH + Global::gamePlayer->getHitboxHorizontal() &&
					Global::gamePlayer->getY() > getY() - hitboxV - Global::gamePlayer->getHitboxVertical()   && Global::gamePlayer->getY() < getY() + hitboxV)
				{
					collected = true;
				}

				if (collected)
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

					EmeraldManager::collectPiece(this);
					collectTimer = collectTimerMax;

					Global::gameScore += std::max(0, 2000 - 20*((Global::gameClock - EmeraldPiece::lastPieceCollectedTimestamp)/60));

					EmeraldPiece::lastPieceCollectedTimestamp = Global::gameClock;
				}
			}
			else
			{
				setPosition(Global::gamePlayer->getPosition());
				position.y += 20;

				if (collectTimer <= collectTimerMax/2)
				{
					scale = EmeraldPiece::baseScale - EmeraldPiece::baseScale*((float)((collectTimerMax/2)-collectTimer))/(collectTimerMax/2);
				}

				collectTimer--;
				if (collectTimer <= 0)
				{
					Main_deleteEntityPass2(this);
					return;
				}
			}

			updateTransformationMatrix();
		}
	}
}

int EmeraldPiece::getPieceNumber()
{
	return pieceNumber;
}

bool EmeraldPiece::isEmeraldPiece()
{
	return true;
}

bool EmeraldPiece::isHardModePiece()
{
	return hardModePiece;
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

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EmeraldPiece static models...\n");
	#endif

	loadObjModel(&EmeraldPiece::models, "res/Models/EmeraldPiece/", "EmeraldPiece.obj");
}

void EmeraldPiece::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EmeraldPiece static models...\n");
	#endif

	Entity::deleteModels(&EmeraldPiece::models);
}
