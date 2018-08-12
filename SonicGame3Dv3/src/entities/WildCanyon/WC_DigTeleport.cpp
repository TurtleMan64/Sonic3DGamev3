#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "wcdigteleport.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/controllableplayer.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"
#include "../../particles/particle.h"
#include "../../particles/particleresources.h"

#include <list>

std::list<TexturedModel*> WC_DigTeleport::models;
CollisionModel* WC_DigTeleport::cmOriginal;

WC_DigTeleport::WC_DigTeleport(
	float x, float y, float z, 
	float yRot,
	float xTarget, float yTarget, float zTarget)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotY = yRot;
	scale = 1;
	visible = true;

	teleportLocation.set(xTarget, yTarget, zTarget);

	updateTransformationMatrix();

	collideModelOriginal = WC_DigTeleport::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/WildCanyon/Objects/", "DigTeleport");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void WC_DigTeleport::step()
{
	if (collideModelTransformed->playerIsOn)
	{
		if (Global::gamePlayer->getDiggingTimer() == 50)
		{
			Vector3f partVel(0, 0, 0);
			new Particle(ParticleResources::textureBlackFadeOutAndIn, Global::gameCamera->getFadePosition1(), &partVel, 0, 50, 0, 400, 0, true);
		}
		else if (Global::gamePlayer->getDiggingTimer() == 25)
		{
			Global::gamePlayer->setPosition(&teleportLocation);
		}
	}
}

std::list<TexturedModel*>* WC_DigTeleport::getModels()
{
	return &WC_DigTeleport::models;
}

void WC_DigTeleport::loadStaticModels()
{
	if (WC_DigTeleport::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading WC_DigTeleport static models...\n");
	#endif

	loadObjModel(&WC_DigTeleport::models, "res/Models/WildCanyon/Objects/", "DigTeleport.obj");

	if (WC_DigTeleport::cmOriginal == nullptr)
	{
		WC_DigTeleport::cmOriginal = loadCollisionModel("Models/WildCanyon/Objects/", "DigTeleport");
	}
}

void WC_DigTeleport::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting WC_DigTeleport static models...\n");
	#endif

	Entity::deleteModels(&WC_DigTeleport::models);
	Entity::deleteCollisionModel(&WC_DigTeleport::cmOriginal);
}
