#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "itemcapsule.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/player.h"
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

std::list<TexturedModel*> ItemCapsule::modelsSolid;
std::list<TexturedModel*> ItemCapsule::modelsGlass;

std::list<TexturedModel*> ItemCapsule::modelsItem1Up;
std::list<TexturedModel*> ItemCapsule::modelsItemBomb;
std::list<TexturedModel*> ItemCapsule::modelsItemInvincible;
std::list<TexturedModel*> ItemCapsule::modelsItemBarrierG;
std::list<TexturedModel*> ItemCapsule::modelsItemRing5;
std::list<TexturedModel*> ItemCapsule::modelsItemRing10;
std::list<TexturedModel*> ItemCapsule::modelsItemRing20;
std::list<TexturedModel*> ItemCapsule::modelsItemSpeedUp;
std::list<TexturedModel*> ItemCapsule::modelsItemBarrierB;

float ItemCapsule::colHorizontal = 6.5f;
float ItemCapsule::colVertical = 15.0f;

ItemCapsule::ItemCapsule()
{

}

ItemCapsule::ItemCapsule(float x, float y, float z, float yRot, float zRot, int type)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	rotY = yRot;
	rotZ = zRot;
	rotSpin = 0;
	scale = 1;
	itemType = type;
	visible = true;
	updateTransformationMatrix();

	entityGlass = new Body(&ItemCapsule::modelsGlass);
	entityGlass->setVisible(true);
	Global::countNew++;
	Main_addTransparentEntity(entityGlass);
	entityGlass->setPosition(&position);
	entityGlass->setRotY(yRot);
	entityGlass->setRotZ(zRot);
	entityGlass->updateTransformationMatrix();

	switch (type)
	{
		case 0:
			entityItem = new Body(&ItemCapsule::modelsItemSpeedUp);
			break;

		case 1:
			entityItem = new Body(&ItemCapsule::modelsItemInvincible);
			break;

		case 2:
			entityItem = new Body(&ItemCapsule::modelsItemRing5);
			break;

		case 3:
			entityItem = new Body(&ItemCapsule::modelsItemRing10);
			break;

		case 4:
			entityItem = new Body(&ItemCapsule::modelsItemRing20);
			break;

		case 5:
			entityItem = new Body(&ItemCapsule::modelsItemBarrierG);
			break;

		case 6:
			entityItem = new Body(&ItemCapsule::modelsItem1Up);
			break;

		case 7:
			entityItem = new Body(&ItemCapsule::modelsItemBomb);
			break;

		default:
			entityItem = new Body(&ItemCapsule::modelsItemBarrierB);
			break;
	}
	entityItem->setVisible(true);
	Global::countNew++;
	Main_addEntity(entityItem);
	entityItem->setPosition(&position);
	entityItem->setRotY(yRot);
	entityItem->setRotZ(zRot);
}

void ItemCapsule::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
		entityItem->setVisible(false);
		entityGlass->setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
			entityItem->setVisible(false);
			entityGlass->setVisible(false);
		}
		else
		{
			setVisible(true);
			entityItem->setVisible(true);
			entityGlass->setVisible(true);
			if (Global::gamePlayer->getX() > getX() - colHorizontal - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getX() < getX() + colHorizontal + Global::gamePlayer->getHitboxHorizontal() &&
				Global::gamePlayer->getZ() > getZ() - colHorizontal - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getZ() < getZ() + colHorizontal + Global::gamePlayer->getHitboxHorizontal() &&
				Global::gamePlayer->getY() + Global::gamePlayer->getHitboxVertical() >= getY() && Global::gamePlayer->getY() <= getY() + colVertical)
			{
				die();
			}

			entityItem->increaseRotation(5, 0, 0);
			entityItem->updateTransformationMatrix();
		}
	}
}

void ItemCapsule::die()
{
	AudioPlayer::play(3, getPosition());

	Main_deleteEntity(this);
	Main_deleteEntity(entityItem);
	Main_deleteTransparentEntity(entityGlass);

	float height = 6.0f;
	float spread = 10.0f;

	for (int i = 4; i != 0; i--)
	{
		Vector3f pos(
			getX() + spread*(random() - 0.5f),
			getY() + spread*(random() - 0.5f) + height,
			getZ() + spread*(random() - 0.5f));

		Vector3f vel(0, 0, 0);

		new Particle(ParticleResources::textureExplosion1, &pos, &vel,
			0, 45, 0, 3 * random() + 6, 0, false);
	}

	Vector3f rebPos(getX(), getY() + 5, getZ());
	
	Global::gamePlayer->rebound(&rebPos);

	switch (itemType)
	{
		case 0:
			//speed shoes
			break;

		case 1:
			//invincible
			break;

		case 2:
			//increase rings by 5
			break;

		case 3:
			//increase rings by 10
			break;

		case 4:
			//increase rings by 20
			break;

		case 5:
			//green shield
			break;

		case 6:
			//1 up
			break;

		case 7:
			//bomb
			break;

		default:
			//electri shield
			break;
	}
}

std::list<TexturedModel*>* ItemCapsule::getModels()
{
	return &ItemCapsule::modelsSolid;
}

void ItemCapsule::loadStaticModels()
{
	if (ItemCapsule::modelsSolid.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading ItemCapsule static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/ItemCapsule/", "CapsuleSolid.obj");
	for (auto newModel : (*newModels)) { ItemCapsule::modelsSolid.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels2 = loadObjModel("res/Models/ItemCapsule/", "CapsuleTransparent.obj");
	for (auto newModel : (*newModels2)) { ItemCapsule::modelsGlass.push_back(newModel); }
	delete newModels2;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels3 = loadObjModel("res/Models/ItemCapsule/", "Item1Up.obj");
	for (auto newModel : (*newModels3)) { ItemCapsule::modelsItem1Up.push_back(newModel); }
	delete newModels3;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels4 = loadObjModel("res/Models/ItemCapsule/", "ItemBomb.obj");
	for (auto newModel : (*newModels4)) { ItemCapsule::modelsItemBomb.push_back(newModel); }
	delete newModels4;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels5 = loadObjModel("res/Models/ItemCapsule/", "ItemInvincible.obj");
	for (auto newModel : (*newModels5)) { ItemCapsule::modelsItemInvincible.push_back(newModel); }
	delete newModels5;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels6 = loadObjModel("res/Models/ItemCapsule/", "ItemBarrierG.obj");
	for (auto newModel : (*newModels6)) { ItemCapsule::modelsItemBarrierG.push_back(newModel); }
	delete newModels6;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels7 = loadObjModel("res/Models/ItemCapsule/", "ItemRing5.obj");
	for (auto newModel : (*newModels7)) { ItemCapsule::modelsItemRing5.push_back(newModel); }
	delete newModels7;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels8 = loadObjModel("res/Models/ItemCapsule/", "ItemRing10.obj");
	for (auto newModel : (*newModels8)) { ItemCapsule::modelsItemRing10.push_back(newModel); }
	delete newModels8;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels9 = loadObjModel("res/Models/ItemCapsule/", "ItemRing20.obj");
	for (auto newModel : (*newModels9)) { ItemCapsule::modelsItemRing20.push_back(newModel); }
	delete newModels9;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels10 = loadObjModel("res/Models/ItemCapsule/", "ItemSpeedUp.obj");
	for (auto newModel : (*newModels10)) { ItemCapsule::modelsItemSpeedUp.push_back(newModel); }
	delete newModels10;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels11 = loadObjModel("res/Models/ItemCapsule/", "ItemBarrierB.obj");
	for (auto newModel : (*newModels11)) { ItemCapsule::modelsItemBarrierB.push_back(newModel); }
	delete newModels11;
	Global::countDelete++;
}

void ItemCapsule::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting ItemCapsule static models...\n");

	ItemCapsule::deleteHelper(&ItemCapsule::modelsSolid);
	ItemCapsule::deleteHelper(&ItemCapsule::modelsGlass);
	ItemCapsule::deleteHelper(&ItemCapsule::modelsItem1Up);
	ItemCapsule::deleteHelper(&ItemCapsule::modelsItemBomb);
	ItemCapsule::deleteHelper(&ItemCapsule::modelsItemInvincible);
	ItemCapsule::deleteHelper(&ItemCapsule::modelsItemBarrierG);
	ItemCapsule::deleteHelper(&ItemCapsule::modelsItemRing5);
	ItemCapsule::deleteHelper(&ItemCapsule::modelsItemRing10);
	ItemCapsule::deleteHelper(&ItemCapsule::modelsItemRing20);
	ItemCapsule::deleteHelper(&ItemCapsule::modelsItemSpeedUp);
	ItemCapsule::deleteHelper(&ItemCapsule::modelsItemBarrierB);
}

void ItemCapsule::deleteHelper(std::list<TexturedModel*>* models)
{
	for (auto model : (*models))
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}
	models->clear();
}

bool ItemCapsule::canHomingAttackOn()
{
	return true;
}