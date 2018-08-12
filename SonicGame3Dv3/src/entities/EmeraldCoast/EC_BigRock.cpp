#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecbigrock.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EC_BigRock::modelsA;
std::list<TexturedModel*> EC_BigRock::modelsB;

EC_BigRock::EC_BigRock()
{
	
}

EC_BigRock::EC_BigRock(float x, float y, float z, float rotX, float rotY, float rotZ, float scale, int kind)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
	this->visible = true;
	this->kind = kind;
	updateTransformationMatrix();
	baseYrot = rotY;
}

void EC_BigRock::step()
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
		}
	}

	//rotY++;
	//updateTransformationMatrix();

	//fprintf(stdout, "%f\n", rotY - baseYrot);
}

std::list<TexturedModel*>* EC_BigRock::getModels()
{
	switch (kind)
	{
		case 0: return &EC_BigRock::modelsA;

		default: break;
	}

	return &EC_BigRock::modelsB;
}

void EC_BigRock::loadStaticModels()
{
	if (EC_BigRock::modelsA.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_BigRock static models...\n");
	#endif

	loadObjModel(&EC_BigRock::modelsA, "res/Models/EmeraldCoast/", "BigRockA.obj");
	loadObjModel(&EC_BigRock::modelsB, "res/Models/EmeraldCoast/", "BigRockB.obj");
}

void EC_BigRock::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_BigRock static models...\n");
	#endif

	Entity::deleteModels(&EC_BigRock::modelsA);
	Entity::deleteModels(&EC_BigRock::modelsB);
}
