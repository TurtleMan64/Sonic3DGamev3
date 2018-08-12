#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "shdgoronelder.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../../toolbox/split.h"
#include "../camera.h"
#include "../../fontMeshCreator/guitext.h"
#include "../controllableplayer.h"
#include "../../guis/guimanager.h"
#include "shdgoronkid.h"

#include <list>
#include <iostream>
#include <cstring>
#include <string>

std::list<TexturedModel*> SHD_GoronElder::models;
GUIText* SHD_GoronElder::messageGUI1 = nullptr;
GUIText* SHD_GoronElder::messageGUI2 = nullptr;

SHD_GoronElder::SHD_GoronElder()
{
	
}

SHD_GoronElder::SHD_GoronElder(float x, float y, float z, float rotY, std::string messages)
{
	if (Global::gameIsChaoMode || Global::gameIsRingMode)
	{
		Main_deleteEntity(this);
		return;
	}

	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();

	char msgBuf[512];
	memset(msgBuf, 0, 512);
	memcpy(msgBuf, messages.c_str(), messages.size());
	int splitLength = 0;
	char** msg = split(msgBuf, '/', &splitLength);

	int split1Length = 0;
	char** msg1 = split(msg[0], '-', &split1Length);

	int split2Length = 0;
	char** msg2 = split(msg[1], '-', &split2Length);

	myMessage1[0] = msg1[0];
	myMessage1[1] = msg1[1];

	myMessage2[0] = msg2[0];
	myMessage2[1] = msg2[1];

	free(msg);
	free(msg1);
	free(msg2);
}

void SHD_GoronElder::step()
{
	ControllablePlayer* p = Global::gamePlayer;
	float xDiff = p->getX()-getX();
	float zDiff = p->getZ()-getZ();
	float yDiff = p->getY()-getY();
	float mag = sqrtf((xDiff*xDiff)+(zDiff*zDiff));

	if (mag < 40 && yDiff > -3 && yDiff < 12)
	{
		std::string* messageToUse1 = &myMessage1[0];
		std::string* messageToUse2 = &myMessage1[1];
		
		if (SHD_GoronKid::found)
		{
			messageToUse1 = &myMessage2[0];
			messageToUse2 = &myMessage2[1];
		}

		if (messageGUI1 == nullptr && (*messageToUse1) != "")
		{
			float size = 100.0f/(*messageToUse1).length();
			size = std::fminf(size, 3);
			messageGUI1 = new GUIText((*messageToUse1), size, GuiManager::fontVip, 0, 0.8f, 1.0f, true, false, true); INCR_NEW
		}
			
		if (messageGUI2 == nullptr && (*messageToUse2) != "")
		{
			float size = 100.0f/(*messageToUse2).length();
			size = std::fminf(size, 3);
			messageGUI2 = new GUIText((*messageToUse2), size, GuiManager::fontVip, 0, 0.9f, 1.0f, true, false, true); INCR_NEW
		}
	}
	else
	{
		if (messageGUI1 != nullptr)
		{
			messageGUI1->deleteMe();
			delete messageGUI1; INCR_DEL
			messageGUI1 = nullptr;
		}
			
		if (messageGUI2 != nullptr)
		{
			messageGUI2->deleteMe();
			delete messageGUI2; INCR_DEL
			messageGUI2 = nullptr;
		}
	}
}

std::list<TexturedModel*>* SHD_GoronElder::getModels()
{
	return &SHD_GoronElder::models;
}

void SHD_GoronElder::loadStaticModels()
{
	if (SHD_GoronElder::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading SHD_GoronElder static models...\n");
	#endif

	loadObjModel(&SHD_GoronElder::models, "res/Models/Gorons/", "Elder.obj");
}

void SHD_GoronElder::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting SHD_GoronElder static models...\n");
	#endif

	Entity::deleteModels(&SHD_GoronElder::models);

	if (messageGUI1 != nullptr)
	{
		messageGUI1->deleteMe();
		delete messageGUI1; INCR_DEL
		messageGUI1 = nullptr;
	}

	if (messageGUI2 != nullptr)
	{
		messageGUI2->deleteMe();
		delete messageGUI2; INCR_DEL
		messageGUI2 = nullptr;
	}
}
