#include <glad/glad.h>

#include "./entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "rocket.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../toolbox/maths.h"
#include "../animation/body.h"
#include "../entities/camera.h"
#include "./camera.h"
#include "./point.h"
#include "../collision/collisionmodel.h"
#include "../collision/collisionchecker.h"
#include "../audio/audioplayer.h"
#include "../audio/source.h"
#include "../particles/particle.h"
#include "../particles/particleresources.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> Rocket::modelsRocket;
std::list<TexturedModel*> Rocket::modelsBase;
CollisionModel* Rocket::cmBase;


Rocket::Rocket()
{

}

Rocket::Rocket(int point1ID, int point2ID)
{
	extern std::list<Entity*> gameEntitiesToAdd;

	for (auto e : gameEntitiesToAdd)
	{
		if (e->isPoint())
		{
			Point* thisPoint = (Point*)e;
			if (thisPoint->getID() == point1ID)
			{
				pointPos1 = thisPoint->getPosition();
			}
			else if (thisPoint->getID() == point2ID)
			{
				pointPos2 = thisPoint->getPosition();
			}
		}
	}

	position = pointPos1;
	scale = 1;
	visible = true;
	storedSonicSpeed = 0;
	updateTransformationMatrix();

	base = new Body(&Rocket::modelsBase);
	base->setVisible(true);
	Global::countNew++;
	Main_addEntity(base);
	base->setPosition(&position);
	//fix slight position disparity from the position given with q
	base->setY(base->getY() - 1);

	collideModelOriginal = Rocket::cmBase;
	collideModelTransformed = loadCollisionModel("Models/Rocket/", "RocketPlatformCollision");
	CollisionChecker::addCollideModel(collideModelTransformed);
	updateCollisionModel();

	//rocket should be above the platform, now that the platform's position is set we can move it
	position.y += 9;

	timeOffset = 0;
	startupTimer = 0;

	speed = 15;
	height = 15;
	radius = 5;

	canMove = true;
	isMoving = false;

	rocketAppearSoundPlayed = false;

	//used for rotation
	float xDiff = (pointPos2.x - position.x);
	float yDiff = (pointPos2.y - position.y);
	float zDiff = -(pointPos2.z - position.z);

	rotY = toDegrees(atan2(zDiff, xDiff));
	rotZ = toDegrees(atan2(yDiff, sqrt(xDiff*xDiff + zDiff*zDiff)));
	base->setRotY(rotY);
	
	pointDifference = pointPos2 - pointPos1;
	pointDifferenceNormalized = pointDifference;
	pointDifferenceNormalized.normalize();

	pointLength = pointDifference.length();
}

void Rocket::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
		base->setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
			base->setVisible(false);
		}
		else if (isMoving || canMove)
		{
			setVisible(true);
			base->setVisible(true);

			Vector3f* playerPos = Global::gamePlayer->getPosition();

			if (!rocketAppearSoundPlayed && fabs(pow(playerPos->x - position.x, 2) + pow(playerPos->z - position.z, 2)) <= pow(radius * 30, 2) && playerPos->y > (position.y - (height * 20 / 2)) && playerPos->y < (position.y + (height * 20 / 2)))
			{
				rocketAppearSoundPlayed = true;
				rocketSource = AudioPlayer::play(54, getPosition(), 1, false);
			}

			if (!(fabs(pow(playerPos->x - position.x, 2) + pow(playerPos->z - position.z, 2)) <= pow(radius * 150, 2) && playerPos->y >(position.y - (height * 100 / 2)) && playerPos->y < (position.y + (height * 100 / 2))))
			{
				rocketAppearSoundPlayed = false;
				rocketSource = nullptr;
			}
			
			if (!isMoving && canMove && fabs(pow(playerPos->x - position.x, 2) + pow(playerPos->z - position.z, 2)) <= pow(radius, 2) && playerPos->y > (position.y - (height / 2)) && playerPos->y < (position.y + (height / 2)))
			{
				//start moving
				isMoving = true;
				canMove = false;

				rocketSource = AudioPlayer::play(55, getPosition(), 1, false);
			}

			if (timeOffset > 1 && isMoving) //stop moving
			{
				Global::gamePlayer->stopMoving();
				Global::gamePlayer->setOnRocket(false);
				Global::gamePlayer->setCanMoveTimer(0);

				position = pointPos1;
				position.y += 9;
				canMove = true;
				isMoving = false;
				timeOffset = 0;
				startupTimer = 0;

				//if (rocketSource != nullptr) //stop the sound currently playing if there is one
				//{
					//rocketSource->stop();
				//}

				//rocketSource = AudioPlayer::play(56, getPosition(), 1, false);
				//rocketSource->setPosition(pointPos2.x, pointPos2.y, pointPos2.z);
			}

			if (isMoving)
			{
				if (rocketSource != nullptr)
				{
					if (!rocketSource->isPlaying())
					{
						rocketSource = AudioPlayer::play(56, getPosition(), 1, false);
					}
				}
				else
				{
					rocketSource = AudioPlayer::play(56, getPosition(), 1, false);
				}

				int dirtToMake = 5;
				while (dirtToMake > 0)
				{
					Vector3f pos(getX() - (pointDifferenceNormalized.x * 12), getY() - (pointDifferenceNormalized.y * 12), getZ() - (pointDifferenceNormalized.z * 12));
					Vector3f vel(pointDifferenceNormalized);
					vel.x += (Maths::random() - 0.5f);
					vel.y += (Maths::random() - 0.5f);
					vel.z += (Maths::random() - 0.5f);

					new Particle(ParticleResources::textureDirt, &pos, &vel, 0.08f, 60, 0, 4 * Maths::random() + 0.5f, 0, false);
					new Particle(ParticleResources::textureDirt, &pos, &vel, 0.08f, 60, 0, 4 * Maths::random() + 0.5f, 0, false);

					dirtToMake--;
					}

				Global::gamePlayer->stopMoving();
				Global::gamePlayer->setOnRocket(true);
				Global::gamePlayer->setIsBall(false);
				Global::gamePlayer->setRotY(rotY);
				Global::gamePlayer->setCanMoveTimer(1000);

				if (startupTimer < 30)
				{
					Global::gamePlayer->setPosition(position.x, position.y, position.z);
					Global::gamePlayer->setDisplacement(pointDifferenceNormalized.x * -12, -12, pointDifferenceNormalized.z * -12);

					startupTimer += 1;
				}
				else
				{
					Vector3f moveDir;
					moveDir.x = (position.x - oldPos.x);
					moveDir.y = (position.y - oldPos.y);
					moveDir.z = (position.z - oldPos.z);

					oldPos.set(&position);

					position.x = pointPos1.x + (pointDifference.x * timeOffset);
					position.y = pointPos1.y + (pointDifference.y * timeOffset);
					position.z = pointPos1.z + (pointDifference.z * timeOffset);

					Vector3f displacement = new Vector3f();
					displacement = position - oldPos;
					
					Global::gamePlayer->setPosition(position.x, position.y, position.z);
					Global::gamePlayer->setDisplacement(moveDir.x, moveDir.y, moveDir.z);
					Global::gamePlayer->setDisplacement(pointDifferenceNormalized.x, -12, pointDifferenceNormalized.z);

					timeOffset += speed / pointLength;
				}
			}

			cmBase->transformModel(collideModelTransformed, base->getPosition());
			updateTransformationMatrix();
			base->updateTransformationMatrix();
		}

	}
}

std::list<TexturedModel*>* Rocket::getModels()
{
	return &Rocket::modelsRocket;
}

void Rocket::loadStaticModels()
{
	if (Rocket::modelsRocket.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading Rocket static models...\n");

	loadObjModel(&Rocket::modelsRocket, "res/Models/Rocket/", "Rocket.obj");
	loadObjModel(&Rocket::modelsBase, "res/Models/Rocket/", "RocketPlatform.obj");

	if (Rocket::cmBase == nullptr)
	{
		Rocket::cmBase = loadCollisionModel("Models/Rocket/", "RocketPlatformCollision");
	}
}

void Rocket::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting Rocket static models...\n");

	Entity::deleteModels(&Rocket::modelsRocket);
	Entity::deleteModels(&Rocket::modelsBase);
}