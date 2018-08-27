#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "mhpathdiagonal.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> MH_PathDiagonal::models;
CollisionModel* MH_PathDiagonal::cmOriginal;

MH_PathDiagonal::MH_PathDiagonal()
{

}

MH_PathDiagonal::MH_PathDiagonal(float x, float y, float z, float rotY)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();

	collideModelOriginal = MH_PathDiagonal::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/MetalHarbor/", "PathDiagonalCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void MH_PathDiagonal::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST * 2)
	{
		setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST * 2)
		{
			setVisible(false);
		}
		else
		{
			setVisible(true);
		}
	}
}

std::list<TexturedModel*>* MH_PathDiagonal::getModels()
{
	return &MH_PathDiagonal::models;
}

void MH_PathDiagonal::loadStaticModels()
{
	if (MH_PathDiagonal::models.size() > 0)
	{
		return;
	}

#ifdef DEV_MODE
	std::fprintf(stdout, "Loading MH_PathDiagonal static models...\n");
#endif

	loadObjModel(&MH_PathDiagonal::models, "res/Models/MetalHarbor/", "PathDiagonal.obj");

	if (MH_PathDiagonal::cmOriginal == nullptr)
	{
		MH_PathDiagonal::cmOriginal = loadCollisionModel("Models/MetalHarbor/", "PathDiagonalCollision");
	}
}

void MH_PathDiagonal::deleteStaticModels()
{
#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting MH_PathDiagonal static models...\n");
#endif

	Entity::deleteModels(&MH_PathDiagonal::models);
	Entity::deleteCollisionModel(&MH_PathDiagonal::cmOriginal);
}
