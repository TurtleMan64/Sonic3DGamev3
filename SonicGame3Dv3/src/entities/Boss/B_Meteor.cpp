#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "bmeteor.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> B_Meteor::models;

B_Meteor::B_Meteor()
{
	
}

B_Meteor::B_Meteor(float x, float y, float z, float velX, float velY, float velZ)
{
	position.x = x;
	position.y = y;
	position.z = z;
	xVel = velX;
	yVel = velY;
	zVel = velZ;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = true;
	timer = 0;
	updateTransformationMatrix();
}

void B_Meteor::step()
{
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
		}
	}
	
	timer++;

	if (timer > 1200)
	{
		Main_deleteEntity(this);
		return;
	}

	increasePosition(xVel, yVel, zVel);
	increaseRotation(xVel, yVel, zVel);
	updateTransformationMatrix();
}

std::list<TexturedModel*>* B_Meteor::getModels()
{
	return &B_Meteor::models;
}

void B_Meteor::loadStaticModels()
{
	if (B_Meteor::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading B_Meteor static models...\n");

	loadObjModel(&B_Meteor::models, "res/Models/Boss/Objects/", "Meteor.obj");
}

void B_Meteor::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting B_Meteor static models...\n");

	Entity::deleteModels(&B_Meteor::models);
}
