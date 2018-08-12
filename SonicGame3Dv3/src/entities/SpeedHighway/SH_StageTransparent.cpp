#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "shstagetransparent.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"

#include <list>

std::list<TexturedModel*> SH_StageTransparent::models;

SH_StageTransparent::SH_StageTransparent()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();
}

void SH_StageTransparent::step()
{

}

std::list<TexturedModel*>* SH_StageTransparent::getModels()
{
	return &SH_StageTransparent::models;
}

void SH_StageTransparent::loadStaticModels()
{
	if (SH_StageTransparent::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading SH_StageTransparent static models...\n");
	#endif

	loadObjModel(&SH_StageTransparent::models, "res/Models/SpeedHighway/", "SpeedHighwayTransparent.obj");
}

void SH_StageTransparent::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting SH_StageTransparent static models...\n");
	#endif

	Entity::deleteModels(&SH_StageTransparent::models);
}
