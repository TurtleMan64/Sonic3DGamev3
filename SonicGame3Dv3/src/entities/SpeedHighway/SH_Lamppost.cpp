<<<<<<< HEAD
#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "shlamppost.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"

#include <list>

std::list<TexturedModel*> SH_Lamppost::models;

SH_Lamppost::SH_Lamppost(float x, float y, float z,
	float xRot, float yRot, float zRot)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = xRot;
	rotY = yRot;
	rotZ = zRot;
	scale = 1;
	visible = true;
	updateTransformationMatrixSADX();
}

void SH_Lamppost::step()
{

}

std::list<TexturedModel*>* SH_Lamppost::getModels()
{
	return &SH_Lamppost::models;
}

void SH_Lamppost::loadStaticModels()
{
	if (SH_Lamppost::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading SH_Lamppost static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/SpeedHighway/", "Lamppost.obj");
	for (auto newModel : (*newModels))
	{
		SH_Lamppost::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void SH_Lamppost::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting SH_Lamppost static models...\n");
	for (auto model : SH_Lamppost::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	SH_Lamppost::models.clear();
}
=======
#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "shlamppost.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"

#include <list>

std::list<TexturedModel*> SH_Lamppost::models;

SH_Lamppost::SH_Lamppost(float x, float y, float z,
	float xRot, float yRot, float zRot)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = xRot;
	rotY = yRot;
	rotZ = zRot;
	scale = 1;
	visible = true;
	updateTransformationMatrixSADX();
}

void SH_Lamppost::step()
{

}

std::list<TexturedModel*>* SH_Lamppost::getModels()
{
	return &SH_Lamppost::models;
}

void SH_Lamppost::loadStaticModels()
{
	if (SH_Lamppost::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading SH_Lamppost static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/SpeedHighway/", "Lamppost.obj");
	for (auto newModel : (*newModels))
	{
		SH_Lamppost::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void SH_Lamppost::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting SH_Lamppost static models...\n");
	for (auto model : SH_Lamppost::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	SH_Lamppost::models.clear();
}
>>>>>>> upstream/master
