#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "shcone.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../camera.h"

#include <list>

std::list<TexturedModel*> SH_Cone::modelsA;
std::list<TexturedModel*> SH_Cone::modelsB;

SH_Cone::SH_Cone(float x, float y, float z,
	float xRot, float yRot, float zRot, int kind)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = xRot;
	rotY = yRot;
	rotZ = zRot;
	coneKind = kind;
	scale = 1;
	visible = true;
	updateTransformationMatrixSADX();
}

void SH_Cone::step()
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
}

std::list<TexturedModel*>* SH_Cone::getModels()
{
	switch (coneKind)
	{
		case 0:
			return &SH_Cone::modelsA;

		default:
			break;
	}

	return &SH_Cone::modelsB;
}

void SH_Cone::loadStaticModels()
{
	if (SH_Cone::modelsA.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading SH_Cone static models...\n");
	#endif

	loadObjModel(&SH_Cone::modelsA, "res/Models/SpeedHighway/", "ConeA.obj");
	loadObjModel(&SH_Cone::modelsB, "res/Models/SpeedHighway/", "ConeB.obj");
}

void SH_Cone::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting SH_Cone static models...\n");
	#endif

	Entity::deleteModels(&SH_Cone::modelsA);
	Entity::deleteModels(&SH_Cone::modelsB);
}
