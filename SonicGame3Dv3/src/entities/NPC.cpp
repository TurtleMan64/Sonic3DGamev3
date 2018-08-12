#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "npc.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../toolbox/maths.h"
#include "../toolbox/split.h"
#include "camera.h"
#include "../fontMeshCreator/guitext.h"
#include "controllableplayer.h"
#include "../guis/guimanager.h"
#include "../audio/audioplayer.h"

#include <list>
#include <iostream>
#include <cstring>
#include <string>

std::list<TexturedModel*> NPC::models;
GUIText* NPC::messageGUI1 = nullptr;
GUIText* NPC::messageGUI2 = nullptr;

NPC::NPC()
{
	
}

NPC::~NPC()
{
	if (messageGUI1 != nullptr && (*messageGUI1->getTextString()) == myMessage1)
	{
		messageGUI1->deleteMe();
		delete messageGUI1; INCR_DEL
		messageGUI1 = nullptr;
	}
			
	if (messageGUI2 != nullptr && (*messageGUI2->getTextString()) == myMessage2)
	{
		messageGUI2->deleteMe();
		delete messageGUI2; INCR_DEL
		messageGUI2 = nullptr;
	}
}

NPC::NPC(float x, float y, float z, float rotY, int id, std::string message)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	scale = 1;
	visible = true;
	this->id = id;
	updateTransformationMatrix();

	char msgBuf[512];
	memset(msgBuf, 0, 512);
	memcpy(msgBuf, message.c_str(), message.size());

	int splitLength = 0;
	char** msg = split(msgBuf, '-', &splitLength);

	myMessage1 = "";
	myMessage2 = "";

	if (splitLength == 1)
	{
		myMessage2 = msg[0];
	}
	else if (splitLength > 1)
	{
		myMessage1 = msg[0];
		myMessage2 = msg[1];
	}

	free(msg);

	std::string lookup = Global::levelNameDisplay+"_NPC_"+std::to_string(id);

	found = false;
	if (Global::gameSaveData.find(lookup) != Global::gameSaveData.end())
	{
		std::string isFound = Global::gameSaveData[lookup];
		if (isFound == "true")
		{
			found = true;
		}
	}

	if (found)
	{
		Main_deleteEntity(this);
		return;
	}
}

void NPC::step()
{
	ControllablePlayer* p = Global::gamePlayer;
	float xDiff = p->getX()-getX();
	float zDiff = p->getZ()-getZ();
	float yDiff = p->getY()-getY();
	float mag = sqrtf((xDiff*xDiff)+(zDiff*zDiff));

	if (mag < 20 && yDiff > -3 && yDiff < 12)
	{
		if (found == false)
		{
			AudioPlayer::play(7, getPosition());
			found = true;

			std::string lookup = Global::levelNameDisplay+"_NPC_"+std::to_string(id);
			Global::gameSaveData[lookup] = "true";
			Global::saveSaveData();
		}
			
		if (messageGUI1 == nullptr && myMessage1 != "")
		{
			float size = 100.0f/myMessage1.length();
			size = std::fminf(size, 3);
			messageGUI1 = new GUIText(myMessage1, size, GuiManager::fontVip, 0, 0.8f, 1.0f, true, false, true); INCR_NEW
		}
			
		if (messageGUI2 == nullptr && myMessage2 != "")
		{
			float size = 100.0f/myMessage2.length();
			size = std::fminf(size, 3);
			messageGUI2 = new GUIText(myMessage2, size, GuiManager::fontVip, 0, 0.9f, 1.0f, true, false, true); INCR_NEW
		}
	}
	else
	{
		if (messageGUI1 != nullptr && (*messageGUI1->getTextString()) == myMessage1)
		{
			messageGUI1->deleteMe();
			delete messageGUI1; INCR_DEL
			messageGUI1 = nullptr;
		}
			
		if (messageGUI2 != nullptr && (*messageGUI2->getTextString()) == myMessage2)
		{
			messageGUI2->deleteMe();
			delete messageGUI2; INCR_DEL
			messageGUI2 = nullptr;
		}
	}
}

std::list<TexturedModel*>* NPC::getModels()
{
	return &NPC::models;
}

void NPC::loadStaticModels()
{
	if (NPC::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading NPC static models...\n");
	#endif

	loadObjModel(&NPC::models, "res/Models/WanamaDage/", "WanamaDage.obj");
}

void NPC::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting NPC static models...\n");
	#endif

	Entity::deleteModels(&NPC::models);

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
