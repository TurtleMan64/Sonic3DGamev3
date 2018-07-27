#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "bearth.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> B_Earth::models;

B_Earth::B_Earth()
{
	scale = 35;
	visible = true;
}

void B_Earth::step()
{

}

std::list<TexturedModel*>* B_Earth::getModels()
{
	return &B_Earth::models;
}

void B_Earth::loadStaticModels()
{
	if (B_Earth::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading B_Earth static models...\n");

	loadObjModel(&B_Earth::models, "res/Models/Boss/Objects/", "Earth.obj");
}

void B_Earth::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting B_Earth static models...\n");

	Entity::deleteModels(&B_Earth::models);
}
