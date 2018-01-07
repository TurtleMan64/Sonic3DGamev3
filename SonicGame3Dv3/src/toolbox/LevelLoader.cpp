#include <iostream>
#include <string>
#include <fstream>

#include "levelloader.h"
#include "../engineTester/main.h"
#include "../entities/stage.h"
#include "../entities/ring.h"
#include "../entities/player.h"
#include "../toolbox/split.h"
#include "../toolbox/input.h"
#include "../collision/collisionchecker.h"
#include "../collision/collisionmodel.h"
#include "../objLoader/objLoader.h"
#include "../entities/skysphere.h"
#include "../renderEngine/skymanager.h"
#include "../entities/camera.h"
#include "../guis/guimanager.h"
#include "../entities/spring.h"
#include "../entities/dashpad.h"
#include "../entities/teleportzone.h"
#include "../entities/EmeraldCoast/ecwaterfall.h"
#include "../entities/EmeraldCoast/ecflatwater.h"
#include "../entities/lowqualitywater.h"
#include "../entities/EmeraldCoast/ecchair.h"
#include "../entities/EmeraldCoast/ecstrawroofhut.h"
#include "../entities/EmeraldCoast/echut.h"
#include "../entities/EmeraldCoast/ecraftsmall.h"
#include "../entities/EmeraldCoast/ecpole.h"
#include "../entities/EmeraldCoast/ecdock.h"
#include "../entities/EmeraldCoast/ecdockcorner.h"
#include "../entities/EmeraldCoast/ecraft.h"
#include "../entities/speedramp.h"
#include "../entities/EmeraldCoast/ecshark.h"

float toFloat(char* input);
int toInt(char* input);
void processLine(char** data);
void freeAllStaticModels();

void LevelLoader_loadTitle()
{
	Stage::deleteModels();
	Global::levelName = "";

	freeAllStaticModels();

	CollisionChecker::deleteAllCollideModels();

	Main_deleteAllEntites();

	Main_deleteAllTransparentEntites();
}

void LevelLoader_loadLevel(std::string levelFilename)
{
	std::string fname = levelFilename;

	if (fname == "")
	{
		return;
	}

	int stageFault = 1;

	if (Global::levelName == fname)
	{
		stageFault = 0;
	}

	Global::levelName = fname;

	freeAllStaticModels();
	Main_deleteAllEntites();
	Main_deleteAllTransparentEntites();

	if (stageFault == 1)
	{
		Stage::deleteModels(); //Only delete stage if loading a new stage
	}


	std::ifstream file("res/Levels/" + fname);
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file '%s'\n", ("res/Levels/" + fname).c_str());
		file.close();
		return;
	}


	//Run through the header content

	std::string modelFLoc;
	getline(file, modelFLoc);

	std::string modelFName;
	getline(file, modelFName);

	std::string colFLoc;
	getline(file, colFLoc);

	std::string numChunksLine;
	getline(file, numChunksLine);

	int numChunks = stoi(numChunksLine);

	if (stageFault == 1) //We need to load in new collision
	{
		CollisionChecker::deleteAllCollideModels();

		while (numChunks > 0)
		{
			std::string line;
			getline(file, line);

			char lineBuf[128]; //Buffer to copy line into
			memset(lineBuf, 0, 128);
			memcpy(lineBuf, line.c_str(), line.size());

			int splitLength = 0;
			char** lineSplit = split(lineBuf, ' ', &splitLength);



			CollisionModel* colModel = loadCollisionModel("Models/" + colFLoc + "/", lineSplit[0]);
			colModel->generateQuadTree(std::stoi(lineSplit[1]));
			CollisionChecker::addCollideModel(colModel);

			numChunks--;

			free(lineSplit);
		}
	}
	else //Keep the same quad tree collision
	{
		CollisionChecker::deleteAllCollideModelsExceptQuadTrees();

		while (numChunks > 0)
		{
			std::string line;
			getline(file, line);

			numChunks--;
		}
	}




	std::string sunColorDay;
	getline(file, sunColorDay);
	{
		char lineBuf[128];
		memset(lineBuf, 0, 128);
		memcpy(lineBuf, sunColorDay.c_str(), sunColorDay.size());
		int splitLength = 0;
		char** dat = split(lineBuf, ' ', &splitLength);

		Vector3f newSunColour(toFloat(dat[0]), toFloat(dat[1]), toFloat(dat[2]));
		SkyManager::setSunColorDay(&newSunColour);

		free(dat);
	}

	std::string sunColorNight;
	getline(file, sunColorNight);
	{
		char lineBuf[128];
		memset(lineBuf, 0, 128);
		memcpy(lineBuf, sunColorNight.c_str(), sunColorNight.size());
		int splitLength = 0;
		char** dat = split(lineBuf, ' ', &splitLength);

		Vector3f newSunColour(toFloat(dat[0]), toFloat(dat[1]), toFloat(dat[2]));
		SkyManager::setSunColorNight(&newSunColour);

		free(dat);
	}

	std::string moonColorDay;
	getline(file, moonColorDay);
	{
		char lineBuf[128];
		memset(lineBuf, 0, 128);
		memcpy(lineBuf, moonColorDay.c_str(), moonColorDay.size());
		int splitLength = 0;
		char** dat = split(lineBuf, ' ', &splitLength);

		Vector3f newMoonColour(toFloat(dat[0]), toFloat(dat[1]), toFloat(dat[2]));
		SkyManager::setMoonColorDay(&newMoonColour);

		free(dat);
	}

	std::string moonColorNight;
	getline(file, moonColorNight);
	{
		char lineBuf[128];
		memset(lineBuf, 0, 128);
		memcpy(lineBuf, moonColorNight.c_str(), moonColorNight.size());
		int splitLength = 0;
		char** dat = split(lineBuf, ' ', &splitLength);

		Vector3f newMoonColour(toFloat(dat[0]), toFloat(dat[1]), toFloat(dat[2]));
		SkyManager::setMoonColorNight(&newMoonColour);

		free(dat);
	}


	Vector3f fogDay;
	Vector3f fogNight;

	std::string fogColorDay;
	getline(file, fogColorDay);
	{
		char lineBuf[128];
		memset(lineBuf, 0, 128);
		memcpy(lineBuf, fogColorDay.c_str(), fogColorDay.size());
		int splitLength = 0;
		char** dat = split(lineBuf, ' ', &splitLength);

		fogDay.set(toFloat(dat[0]), toFloat(dat[1]), toFloat(dat[2]));

		free(dat);
	}

	std::string fogColorNight;
	getline(file, fogColorNight);
	{
		char lineBuf[128];
		memset(lineBuf, 0, 128);
		memcpy(lineBuf, fogColorNight.c_str(), fogColorNight.size());
		int splitLength = 0;
		char** dat = split(lineBuf, ' ', &splitLength);

		fogNight.set(toFloat(dat[0]), toFloat(dat[1]), toFloat(dat[2]));

		free(dat);
	}

	SkyManager::setFogColours(&fogDay, &fogNight);

	std::string fogVars;
	getline(file, fogVars);
	{
		char lineBuf[128];
		memset(lineBuf, 0, 128);
		memcpy(lineBuf, fogVars.c_str(), fogVars.size());
		int splitLength = 0;
		char** dat = split(lineBuf, ' ', &splitLength);

		SkyManager::setFogVars(toFloat(dat[0]), toFloat(dat[1]));

		free(dat);
	}

	std::string timeOfDay;
	getline(file, timeOfDay);
	if (stageFault == 1)
	{
		char lineBuf[128];
		memset(lineBuf, 0, 128);
		memcpy(lineBuf, timeOfDay.c_str(), timeOfDay.size());
		int splitLength = 0;
		char** dat = split(lineBuf, ' ', &splitLength);

		SkyManager::setTimeOfDay(toFloat(dat[0]));

		free(dat);
	}

	Global::gameSkySphere->setVisible(false);


	std::string camOrientation;
	getline(file, camOrientation);
	{
		char lineBuf[128];
		memset(lineBuf, 0, 128);
		memcpy(lineBuf, camOrientation.c_str(), camOrientation.size());
		int splitLength = 0;
		char** dat = split(lineBuf, ' ', &splitLength);

		Global::gameCamera->setYaw(toFloat(dat[0]));
		Global::gameCamera->setPitch(toFloat(dat[1]));

		free(dat);
	}



	//Now read through all the objects defined in the file

	std::string line;

	while (!file.eof())
	{
		getline(file, line);

		char lineBuf[512]; //Buffer to copy line into
		memset(lineBuf, 0, 512);
		memcpy(lineBuf, line.c_str(), line.size());

		int splitLength = 0;
		char** lineSplit = split(lineBuf, ' ', &splitLength);

		if (splitLength > 0)
		{
			Input_pollInputs();

			processLine(lineSplit);
		}
		free(lineSplit);
	}
	file.close();

	if (stageFault == 1)
	{
		Stage::loadModels((char*)modelFLoc.c_str(), (char*)modelFName.c_str());
	}

	if (Global::gamePlayer != nullptr)
	{
		Global::gamePlayer->setCanMove(false);
		Global::bufferTime = 60;
	}

	Global::gameRingCount = 0;
	GuiManager::setTimer(0, 0, 0);
	GuiManager::stopTimer();
}


void processLine(char** dat)
{
	int id = std::stoi(dat[0]);

	switch (id)
	{
		case 0: //Ring
		{
			Ring::loadStaticModels();
			Ring* ring = new Ring(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			Global::countNew++;
			Main_addEntity(ring);
			return;
		}

		case 1: //Spring
		{
			Spring::loadStaticModels();
			Spring* spring = new Spring(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]),                  //rotation
				toFloat(dat[6]), toInt(dat[7]));                   //power, time
			Global::countNew++;
			Main_addEntity(spring);
			return;
		}

		case 2: //Dashpad
		{
			Dashpad::loadStaticModels();
			Dashpad* dashpad = new Dashpad(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]),                  //rotation
				toFloat(dat[6]), toFloat(dat[7]), toInt(dat[8]));                 //power, camYaw, time
			Global::countNew++;
			Main_addEntity(dashpad);
			return;
		}
		
		case 6: //Player
		{
			Player::loadStaticModels();
			Player* player = new Player(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			Global::countNew++;
			Global::gamePlayer = player;
			SkyManager::setCenterObject(player);
			player->setCameraAngles(Global::gameCamera->getYaw(), Global::gameCamera->getPitch());
			Main_addEntity(player);
			return;
		}

		case 7: //Sky Sphere
		{
			SkySphere::loadModels(dat[1], dat[2], dat[3]);
			Global::gameSkySphere->setScale(toFloat(dat[4]));
			Global::gameSkySphere->setVisible(true);
			return;
		}

		case 8: //Teleport Zone
		{
			TeleportZone* zone = new TeleportZone(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]),
				toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6]),
				toFloat(dat[7]), toFloat(dat[8]), toFloat(dat[9]));
			Global::countNew++;
			Main_addEntity(zone);
			return;
		}

		case 13: //Emerald Coast Double-Waterfall
		{
			EC_Waterfall::loadStaticModels();
			EC_Waterfall* waterfall = new EC_Waterfall(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]));                 //rotation, scale
			Global::countNew++;
			Main_addTransparentEntity(waterfall);
			return;
		}

		case 14: //Emerald Coast Flat Water
		{
			EC_FlatWater::loadStaticModels();
			EC_FlatWater* water = new EC_FlatWater();
			Global::countNew++;
			Main_addTransparentEntity(water);
			return;
		}

		case 29: //Speed Ramp
		{
			SpeedRamp::loadStaticModels();
			SpeedRamp* ramp = new SpeedRamp(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]),                  //rotation
				toFloat(dat[6]));                                  //power
			Global::countNew++;
			Main_addEntity(ramp);
			return;
		}

		case 37: //Low quality water
		{
			LowQualityWater::loadStaticModels();
			LowQualityWater* water = new LowQualityWater(toFloat(dat[1]), toFloat(dat[2]));
			Global::countNew++;
			Main_addTransparentEntity(water);
			return;
		}

		case 38: //Emerald Coast Chair
		{
			EC_Chair::loadStaticModels();
			EC_Chair* chair = new EC_Chair(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
										   toFloat(dat[4]), toFloat(dat[5]));                 //rotation
			Global::countNew++;
			Main_addEntity(chair);
			return;
		}

		case 39: //Emerald Coast Straw Roof Hut
		{
			EC_StrawRoofHut::loadStaticModels();
			EC_StrawRoofHut* hut = new EC_StrawRoofHut(
											toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
										    toFloat(dat[4]));                                  //rotation
			Global::countNew++;
			Main_addEntity(hut);
			return;
		}

		case 40: //Emerald Coast Hut
		{
			EC_Hut::loadStaticModels();
			EC_Hut* hut = new EC_Hut(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			Global::countNew++;
			Main_addEntity(hut);
			return;
		}
		
		case 41: //Emerald Coast Dock
		{
			EC_Dock::loadStaticModels();
			EC_Dock* dock = new EC_Dock(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			Global::countNew++;
			Main_addEntity(dock);
			return;
		}

		case 42: //Emerald Coast Concrete Pole
		{
			EC_Pole::loadStaticModels();
			EC_Pole* pole = new EC_Pole(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			Global::countNew++;
			Main_addEntity(pole);
			return;
		}

		case 43: //Emerald Coast Dock Corner
		{
			EC_DockCorner::loadStaticModels();
			EC_DockCorner* dock = new EC_DockCorner(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			Global::countNew++;
			Main_addEntity(dock);
			return;
		}

		case 44: //Emerald Coast Raft Small
		{
			EC_RaftSmall::loadStaticModels();
			EC_RaftSmall* raft = new EC_RaftSmall(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			Global::countNew++;
			Main_addEntity(raft);
			return;
		}

		case 45: //Emerald Coast Raft
		{
			EC_Raft::loadStaticModels();
			EC_Raft* raft = new EC_Raft(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			Global::countNew++;
			Main_addEntity(raft);
			return;
		}

		case 46: //Emerald Coast Shark
		{
			EC_Shark::loadStaticModels();
			EC_Shark* shark = new EC_Shark(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3])); //position
			Global::countNew++;
			Global::ecShark = shark;
			Main_addEntity(shark);
			return;
		}

		default:
		{
			return;
		}
	}
}


float toFloat(char* input)
{
	return std::stof(input);
}

int toInt(char* input)
{
	return std::stoi(input);
}

void freeAllStaticModels()
{
	Ring::deleteStaticModels();
	Player::deleteStaticModels();
	SkySphere::deleteModels();
	Spring::deleteStaticModels();
	Dashpad::deleteStaticModels();
	EC_Waterfall::deleteStaticModels();
	EC_FlatWater::deleteStaticModels();
	LowQualityWater::deleteStaticModels();
	EC_Chair::deleteStaticModels();
	EC_StrawRoofHut::deleteStaticModels();
	EC_Hut::deleteStaticModels();
	EC_RaftSmall::deleteStaticModels();
	EC_Pole::deleteStaticModels();
	EC_Dock::deleteStaticModels();
	EC_DockCorner::deleteStaticModels();
	EC_Raft::deleteStaticModels();
	SpeedRamp::deleteStaticModels();
	EC_Shark::deleteStaticModels();
}