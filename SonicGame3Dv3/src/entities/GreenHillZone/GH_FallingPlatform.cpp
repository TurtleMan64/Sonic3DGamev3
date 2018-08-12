#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ghfallingplatform.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"
#include "../../audio/audioplayer.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> GH_FallingPlatform::models;
CollisionModel* GH_FallingPlatform::cmOriginal;

GH_FallingPlatform::GH_FallingPlatform()
{
	
}

GH_FallingPlatform::GH_FallingPlatform(float x, float y, float z, float rotY, float scale)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	this->scale = scale;
	visible = true;
	timer = 24;
	updateTransformationMatrix();

	collideModelOriginal = GH_FallingPlatform::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/GreenHillZone/Objects/", "GreenHillFallingPlatform");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void GH_FallingPlatform::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
		}
		else
		{
			setVisible(true);

			if (collideModelTransformed->playerIsOn && timer == 24)
			{
				timer = 23;
			}
				
			if (timer < 24)
			{
				timer--;
			}
				
			if (timer == 0)
			{
				AudioPlayer::play(0, getPosition());
			}
				
			if (timer < 0)
			{
				increasePosition(0, timer/13.0f, 0);
				updateCollisionModel();
				updateTransformationMatrix();
			}
				
			if (timer == -600)
			{
				CollisionChecker::deleteCollideModel(collideModelTransformed);
				Main_deleteEntity(this);
			}
		}
	}
}

std::list<TexturedModel*>* GH_FallingPlatform::getModels()
{
	return &GH_FallingPlatform::models;
}

void GH_FallingPlatform::loadStaticModels()
{
	if (GH_FallingPlatform::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading GH_FallingPlatform static models...\n");
	#endif

	loadObjModel(&GH_FallingPlatform::models, "res/Models/GreenHillZone/Objects/", "GreenHillFallingPlatform.obj");

	if (GH_FallingPlatform::cmOriginal == nullptr)
	{
		GH_FallingPlatform::cmOriginal = loadCollisionModel("Models/GreenHillZone/Objects/", "GreenHillFallingPlatform");
	}
}

void GH_FallingPlatform::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting GH_FallingPlatform static models...\n");
	#endif

	Entity::deleteModels(&GH_FallingPlatform::models);
	Entity::deleteCollisionModel(&GH_FallingPlatform::cmOriginal);
}
