#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "tpflatwater.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> TP_FlatWater::models;

Vector2f TP_FlatWater::v1(250.807f,   -19552.71f);
Vector2f TP_FlatWater::v2(-45.78894f, -19552.71f);
Vector2f TP_FlatWater::v3(0.31f,      -19258.832f);
Vector2f TP_FlatWater::v4(100.42f,    -19118.6757f);
Vector2f TP_FlatWater::v5(302.6468f,  -19126.6855f);
Vector2f TP_FlatWater::v6(428.088f,   -19224.79f);

Vector2f TP_FlatWater::b1(359.98f,   -19551.1f);
Vector2f TP_FlatWater::b2(-191.505f, -19551.3f);
Vector2f TP_FlatWater::b3(-136.747f, -19199.1f);
Vector2f TP_FlatWater::b4(-51.7859f, -19075.6f);
Vector2f TP_FlatWater::b5(66.4008f,  -18999.7f);
Vector2f TP_FlatWater::b6(360.015f,  -18999.7f);

TP_FlatWater::TP_FlatWater()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();
}

void TP_FlatWater::step()
{
	ControllablePlayer* p = Global::gamePlayer;
	float px = p->getX();
	float py = p->getY();
	float pz = p->getZ();
	if (pz < -10000)
	{
		visible = true;

		if (px > 127.0105f    && px < 710.52881f    &&
			pz > -21026.3418f && pz < -20442.82422f &&
			py < 173.54277f)
		{
			p->setInWater(173.54277f);
		}
		else if (py < 444.51f && py > 400)
		{
			if (CollisionChecker::checkPointInTriangle2D(px, pz, v1.x, v1.y, v2.x, v2.y, v3.x, v3.y) ||
				CollisionChecker::checkPointInTriangle2D(px, pz, v1.x, v1.y, v3.x, v3.y, v4.x, v4.y) ||
				CollisionChecker::checkPointInTriangle2D(px, pz, v1.x, v1.y, v4.x, v4.y, v5.x, v5.y) ||
				CollisionChecker::checkPointInTriangle2D(px, pz, v1.x, v1.y, v5.x, v5.y, v6.x, v6.y))
			{
				p->setInWater(444.51f);
			}
		}
		else if (py < 192.96f)
		{
			if (CollisionChecker::checkPointInTriangle2D(px, pz, b1.x, b1.y, b2.x, b2.y, b3.x, b3.y) ||
				CollisionChecker::checkPointInTriangle2D(px, pz, b1.x, b1.y, b3.x, b3.y, b4.x, b4.y) ||
				CollisionChecker::checkPointInTriangle2D(px, pz, b1.x, b1.y, b4.x, b4.y, b5.x, b5.y) ||
				CollisionChecker::checkPointInTriangle2D(px, pz, b1.x, b1.y, b5.x, b5.y, b6.x, b6.y))
			{
				p->setInWater(192.96f);
			}
		}
	}
	else
	{
		visible = false;
	}
}

std::list<TexturedModel*>* TP_FlatWater::getModels()
{
	return &TP_FlatWater::models;
}

void TP_FlatWater::loadStaticModels()
{
	if (TP_FlatWater::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading TP_FlatWater static models...\n");
	#endif

	loadObjModel(&TP_FlatWater::models, "res/Models/TwinklePark/", "FlatWater.obj");
}

void TP_FlatWater::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting TP_FlatWater static models...\n");
	#endif

	Entity::deleteModels(&TP_FlatWater::models);
}

std::string TP_FlatWater::getName()
{
	return "TP_FlatWater";
}