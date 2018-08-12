#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "itemcapsule.h"
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
#include "shieldmagnet.h"
#include "shieldgreen.h"

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

	entityGlass = new Body(&ItemCapsule::modelsGlass); INCR_NEW
	entityGlass->setVisible(true);
	Main_addTransparentEntity(entityGlass);
	entityGlass->setPosition(&position);
	entityGlass->setRotY(yRot);
	entityGlass->setRotZ(zRot);
	entityGlass->updateTransformationMatrix();

	centerPos = position+spherePositionFromAngles(toRadians(yRot), toRadians(zRot), 7.5f);

	switch (type)
	{
		case 0:  entityItem = new Body(&ItemCapsule::modelsItemSpeedUp);    INCR_NEW break;
		case 1:  entityItem = new Body(&ItemCapsule::modelsItemInvincible); INCR_NEW break;
		case 2:  entityItem = new Body(&ItemCapsule::modelsItemRing5);      INCR_NEW break;
		case 3:  entityItem = new Body(&ItemCapsule::modelsItemRing10);     INCR_NEW break;
		case 4:  entityItem = new Body(&ItemCapsule::modelsItemRing20);     INCR_NEW break;
		case 5:  entityItem = new Body(&ItemCapsule::modelsItemBarrierG);   INCR_NEW break;
		case 6:  entityItem = new Body(&ItemCapsule::modelsItem1Up);        INCR_NEW break;
		case 7:  entityItem = new Body(&ItemCapsule::modelsItemBomb);       INCR_NEW break;
		default: entityItem = new Body(&ItemCapsule::modelsItemBarrierB);   INCR_NEW break;
	}
	entityItem->setVisible(true);
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

			if (abs(getX() - Global::gamePlayer->getPosition()->x) < 50 && 
				abs(getZ() - Global::gamePlayer->getPosition()->z) < 50)
			{
				if ((Global::gamePlayer->getCenterPosition()-centerPos).lengthSquared() < (7.5f*7.5f + 6.0f*6.0f))
				{
					die();
				}


				//if (Global::gamePlayer->getX() > getX() - colHorizontal - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getX() < getX() + colHorizontal + Global::gamePlayer->getHitboxHorizontal() &&
				//	Global::gamePlayer->getZ() > getZ() - colHorizontal - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getZ() < getZ() + colHorizontal + Global::gamePlayer->getHitboxHorizontal() &&
				//	Global::gamePlayer->getY() + Global::gamePlayer->getHitboxVertical() >= getY() && Global::gamePlayer->getY() <= getY() + colVertical)
				//{
					//die();
				//}
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
			getX() + spread*(Maths::random() - 0.5f),
			getY() + spread*(Maths::random() - 0.5f) + height,
			getZ() + spread*(Maths::random() - 0.5f));

		Vector3f vel(0, 0, 0);

		new Particle(ParticleResources::textureExplosion1, &pos, &vel,
			0, 45, 0, 3 * Maths::random() + 6, 0, false);
	}

	Vector3f rebPos(getX(), getY() + 5, getZ());
	
	Global::gamePlayer->rebound(&rebPos);

	switch (itemType)
	{
		case 0:
			//speed shoes
			Global::gameScore += 100;
			Global::gamePlayer->setSpeedshoesTimer(1500);
			break;

		case 1:
			//invincible
			Global::gameScore += 100;
			Global::gamePlayer->setInvincibleTimer(1500);
			break;

		case 2:
			//increase rings by 5
			Global::increaseRingCount(5);
			Global::gameScore += 50;
			break;

		case 3:
			//increase rings by 10
			Global::increaseRingCount(10);
			Global::gameScore += 100;
			break;

		case 4:
			//increase rings by 20
			Global::increaseRingCount(20);
			Global::gameScore += 200;
			break;

		case 5:
		{
			//green shield
			Global::gameScore += 100;
			ShieldGreen* shield = new ShieldGreen; INCR_NEW
			Main_addTransparentEntity(shield);
			Global::gamePlayer->setShieldGreen(shield);
			break;
		}

		case 6:
			//1 up
			Global::gameScore += 300;
			Global::gameLives++;
			AudioPlayer::play(35, getPosition());
			break;

		case 7:
		{
			//bomb
			Global::gameScore += 100;

			float myX = getX();
			float myZ = getZ();
			float myY = getY();

			extern std::unordered_map<Entity*, Entity*> gameEntities;

			for (auto e : gameEntities)
			{
				if (e.first->isEnemy())
				{
					float xDiff = e.first->getX() - myX;
					float zDiff = e.first->getZ() - myZ;
					float yDiff = e.first->getY() - myY;
					float dist = xDiff*xDiff + zDiff*zDiff + yDiff*yDiff;
					if (dist < 300*300)
					{
						e.first->die();
					}
				}
			}

			break;
		}

		default:
		{
			//electric shield
			Global::gameScore += 100;
			ShieldMagnet* shield = new ShieldMagnet; INCR_NEW
			Main_addTransparentEntity(shield);
			Global::gamePlayer->setShieldMagnet(shield);
			break;
		}
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

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading ItemCapsule static models...\n");
	#endif

	loadObjModel(&ItemCapsule::modelsSolid,          "res/Models/ItemCapsule/", "CapsuleSolid.obj");
	loadObjModel(&ItemCapsule::modelsGlass, 		 "res/Models/ItemCapsule/", "CapsuleTransparent.obj");
	loadObjModel(&ItemCapsule::modelsItem1Up, 		 "res/Models/ItemCapsule/", "Item1Up.obj");
	loadObjModel(&ItemCapsule::modelsItemBomb, 		 "res/Models/ItemCapsule/", "ItemBomb.obj");
	loadObjModel(&ItemCapsule::modelsItemInvincible, "res/Models/ItemCapsule/", "ItemInvincible.obj");
	loadObjModel(&ItemCapsule::modelsItemBarrierG, 	 "res/Models/ItemCapsule/", "ItemBarrierG.obj");
	loadObjModel(&ItemCapsule::modelsItemRing5, 	 "res/Models/ItemCapsule/", "ItemRing5.obj");
	loadObjModel(&ItemCapsule::modelsItemRing10, 	 "res/Models/ItemCapsule/", "ItemRing10.obj");
	loadObjModel(&ItemCapsule::modelsItemRing20, 	 "res/Models/ItemCapsule/", "ItemRing20.obj");
	loadObjModel(&ItemCapsule::modelsItemSpeedUp, 	 "res/Models/ItemCapsule/", "ItemSpeedUp.obj");
	loadObjModel(&ItemCapsule::modelsItemBarrierB, 	 "res/Models/ItemCapsule/", "ItemBarrierB.obj");
}

void ItemCapsule::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting ItemCapsule static models...\n");
	#endif

	Entity::deleteModels(&ItemCapsule::modelsSolid);
	Entity::deleteModels(&ItemCapsule::modelsGlass);
	Entity::deleteModels(&ItemCapsule::modelsItem1Up);
	Entity::deleteModels(&ItemCapsule::modelsItemBomb);
	Entity::deleteModels(&ItemCapsule::modelsItemInvincible);
	Entity::deleteModels(&ItemCapsule::modelsItemBarrierG);
	Entity::deleteModels(&ItemCapsule::modelsItemRing5);
	Entity::deleteModels(&ItemCapsule::modelsItemRing10);
	Entity::deleteModels(&ItemCapsule::modelsItemRing20);
	Entity::deleteModels(&ItemCapsule::modelsItemSpeedUp);
	Entity::deleteModels(&ItemCapsule::modelsItemBarrierB);
}

bool ItemCapsule::canHomingAttackOn()
{
	return true;
}

Vector3f ItemCapsule::getHomingCenter()
{
	return centerPos;
}