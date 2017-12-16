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

float toFloat(char* input);
void processLine(char** data);
void freeAllStaticModels();

void LevelLoader_loadTitle()
{
	Stage::deleteModels();
	Stage::stageName = "";

	freeAllStaticModels();

	CollisionChecker::deleteAllCollideModels();

	Main_deleteAllEntites();
}

void LevelLoader_loadLevel(char* levelFilename)
{
	std::string fname = levelFilename;

	if (fname == "")
	{
		return;
	}

	int stageFault = 1;

	if (Stage::stageName == fname)
	{
		stageFault = 0;
	}

	Stage::stageName = fname;

	freeAllStaticModels();
	Main_deleteAllEntites();

	if (stageFault == 1)
	{
		Stage::deleteModels(); //Only delete stage if loading a new stage
	}


	std::ifstream file("res/Data/" + fname);
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file '%s'\n", ("res/Data/" + fname).c_str());
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

	//CollisionChecker::deleteAllCollideModels();

	while (numChunks > 0)
	{
		std::string colFilename;
		getline(file, colFilename);

		//CollisionModel* colModel = loadCollisionModel("Models/" + colFLoc + "/", colFilename);
		//CollisionChecker::addCollideModel(colModel);

		numChunks--;
	}

	//TODO: set up sky manager
	std::string sunColorDay;
	getline(file, sunColorDay);

	std::string sunColorNight;
	getline(file, sunColorNight);

	std::string moonColorDay;
	getline(file, moonColorDay);

	std::string moonColorNight;
	getline(file, moonColorNight);



	std::string fogColorDay;
	getline(file, fogColorDay);

	std::string fogColorNight;
	getline(file, fogColorNight);

	std::string fogVars;
	getline(file, fogVars);



	std::string timeOfDay;
	getline(file, timeOfDay);
	if (stageFault == 1)
	{
		//TODO: set time of day in sky manager
	}


	std::string camOrientation;
	getline(file, camOrientation);




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
			pollInputs();

			processLine(lineSplit);
		}
		free(lineSplit);
	}
	file.close();

	if (stageFault == 1)
	{
		Stage::loadModels((char*)modelFLoc.c_str(), (char*)modelFName.c_str());
	}

	//Reset timer
	//Reset rings
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
		
		case 6: //Player
		{
			Player::loadStaticModels();
			Player* player = new Player(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			Global::countNew++;
			Global::gamePlayer = player;
			Main_addEntity(player);
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



void freeAllStaticModels()
{
	Ring::deleteStaticModels();
	Player::deleteStaticModels();
}