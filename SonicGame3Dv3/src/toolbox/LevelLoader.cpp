#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <AL/al.h>

#include <chrono>
#include <thread>

#include "levelloader.h"
#include "../engineTester/main.h"
#include "../entities/stage.h"
#include "../entities/ring.h"
#include "../entities/playersonic.h"
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
#include "../entities/EmeraldCoast/ecpalmtree.h"
#include "../entities/EmeraldCoast/ecumbrella.h"
#include "../toolbox/maths.h"
#include "../entities/goalsign.h"
#include "../entities/spikeball.h"
#include "../entities/maniasonicmodel.h"
#include "../entities/spinner.h"
#include "../entities/EmeraldCoast/ecdolphin.h"
#include "../particles/particleresources.h"
#include "../particles/particle.h"
#include "../entities/killbox.h"
#include "../entities/TwinklePark/tpflatwater.h"
#include "../entities/TwinklePark/tpfloatingpad.h"
#include "../audio/audioplayer.h"
#include "../entities/EmeraldCoast/ecsinkingplatform.h"
#include "../entities/TwinklePark/tpspinningfloor.h"
#include "../entities/FireField/ffhealpads.h"
#include "../audio/source.h"
#include "../entities/EmeraldCoast/ecstagetransparent.h"
#include "../entities/Snowhead/shdstagetransparent.h"
#include "../entities/SpeedHighway/shturnasi.h"
#include "../entities/EmeraldCoast/ecbigrock.h"
#include "../entities/EmeraldCoast/ecrockplatform.h"
#include "../entities/EmeraldCoast/ecseagull.h"
#include "../entities/itemcapsule.h"
#include "../entities/SpeedHighway/shcraneplatform.h"
#include "../entities/point.h"
#include "../entities/SpeedHighway/shcraneplatformpath.h"
#include "../entities/soundemitter.h"
#include "../entities/SpeedHighway/shstagetransparent.h"
#include "../entities/SpeedHighway/shlamppost.h"
#include "../entities/SpeedHighway/shcone.h"
#include "../entities/SpeedHighway/shspotlight.h"
#include "../entities/SpeedHighway/shelevatorplatformpath.h"
#include "../entities/SpeedHighway/shelevatorplatform.h"
#include "../entities/capsule.h"
#include "../toolbox/pausescreen.h"
#include "../entities/playertails.h"
#include "../entities/controllableplayer.h"
#include "../entities/playerknuckles.h"
#include "../entities/stagetransparent.h"
#include "../entities/emeraldpiece.h"
#include "../entities/emeraldmanager.h"
#include "../guis/guitextureresources.h"
#include "../entities/WildCanyon/wcbreeze.h"
#include "../entities/goaltrigger.h"
#include "../entities/DelfinoPlaza/dppalmtree.h"
#include "../entities/DelfinoPlaza/dpleaves.h"
#include "../entities/NokiBay/nbpalmtree.h"
#include "../entities/NokiBay/nbwaterplatform.h"
#include "../entities/NokiBay/nbwaterplatformbounce.h"
#include "mainmenu.h"
#include "../entities/chao.h"
#include "../entities/GreenHillZone/ghfloatingplatform.h"
#include "../entities/GreenHillZone/ghfallingplatform.h"
#include "../entities/GreenHillZone/ghrock.h"
#include "../entities/GreenHillZone/ghtotem.h"
#include "../entities/GreenHillZone/ghtotemwings.h"
#include "../entities/GreenHillZone/ghtree.h"
#include "../entities/GreenHillZone/ghgrass.h"
#include "../entities/GreenHillZone/ghsunflower.h"
#include "../entities/GreenHillZone/ghflower.h"
#include "../entities/rhinotank.h"
#include "../entities/motobug.h"
#include "../entities/npc.h"
#include "../entities/Snowhead/shdgoronelder.h"
#include "../entities/Snowhead/shdgoronkid.h"
#include "../entities/PumpkinHill/phclouds.h"
#include "../entities/DryLagoon/dlturtle.h"
#include "../entities/camerabox.h"
#include "../entities/RadicalHighway/rhramp.h"
#include "../entities/WildCanyon/wcdigteleport.h"
#include "../entities/checkpoint.h"
#include "../entities/SpeedHighway/shfloatingplatform.h"
#include "../entities/Boss/bmanager.h"
#include "../entities/Boss/bplatform.h"
#include "../entities/Boss/bmeteor.h"
#include "../entities/Boss/bearth.h"
#include "../entities/Boss/bmetalsonic.h"
#include "../entities/rocket.h"
#include "../entities/MetalHarbor/mhmanager.h"
#include "../entities/MetalHarbor/mhtank.h"
#include "../entities/MetalHarbor/mhgiantrocket.h"
#include "../entities/MetalHarbor/mhrocketbase.h"
#include "../entities/MetalHarbor/mhpathflat.h"
#include "../entities/MetalHarbor/mhpathflatsmall.h"
#include "../entities/MetalHarbor/mhpathdiagonal.h"

//float toFloat(char* input);
//int toInt(char* input);
//void processLine(char** data, int dataLength);
//void freeAllStaticModels();

void LevelLoader::loadTitle()
{
	Stage::deleteModels();
	Global::levelName = "";

	freeAllStaticModels();

	CollisionChecker::deleteAllCollideModels();

	SkyManager::setCenterObject(nullptr);
	Global::gamePlayer = nullptr;

	Main_deleteAllEntites();
	Main_deleteAllEntitesPass2();
	Main_deleteAllTransparentEntites();

	AudioPlayer::stopBGM();
	AudioPlayer::deleteBuffersBGM();

	Global::gameSkySphere->setVisible(false);

	Global::finishStageTimer = -1;

	Global::stageUsesWater = true;

	Global::gameRingCount = 0;
	Global::gameScore = 0;
	Global::gameLives = 4;
	GuiManager::setTimer(0, 0, 0);
	GuiManager::stopTimer();

	GuiManager::clearGuisToRender();

	MainMenu::loadResources();
	Global::gameState = STATE_TITLE;
	Global::gameIsNormalMode = false;
	Global::gameIsHardMode = false;
	Global::gameIsChaoMode = false;
	Global::gameIsRingMode = false;

	Global::spawnAtCheckpoint  = false;
	Global::checkpointX        = 0;
	Global::checkpointY        = 0;
	Global::checkpointZ        = 0;
	Global::checkpointRotY     = 0;
	Global::checkpointCamYaw   = 0;
	Global::checkpointCamPitch = 0;
	Global::checkpointTimeCen  = 0;
	Global::checkpointTimeSec  = 0;
	Global::checkpointTimeMin  = 0;
}

void LevelLoader::loadLevel(std::string levelFilename)
{
	std::string fname = levelFilename;

	if (fname == "")
	{
		return;
	}

	int stageFault = 0;

	if (!Global::isNewLevel)
	{
		if (Global::gameIsArcadeMode)
		{
			Global::gameLives--;
			if (Global::gameLives < 0)
			{
				LevelLoader::loadTitle();
				return;
			}
		}
	}

	if (Global::isNewLevel)
	{
		stageFault = 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		Global::spawnAtCheckpoint  = false;
		Global::checkpointX        = 0;
		Global::checkpointY        = 0;
		Global::checkpointZ        = 0;
		Global::checkpointRotY     = 0;
		Global::checkpointCamYaw   = 0;
		Global::checkpointCamPitch = 0;
		Global::checkpointTimeCen  = 0;
		Global::checkpointTimeSec  = 0;
		Global::checkpointTimeMin  = 0;
	}
	Global::isNewLevel = false;

	if (stageFault == 1)
	{
		freeAllStaticModels();
	}

	SkyManager::setCenterObject(nullptr);
	Global::gamePlayer = nullptr;

	Main_deleteAllEntites();
	Main_deleteAllEntitesPass2();
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

	AudioPlayer::stopBGM();
	//Delete existing bgm if loading a new stage
	if (stageFault == 1)
	{
		AudioPlayer::deleteBuffersBGM();
	}

	Global::stageUsesWater = true;
	if (Global::levelID == LVL_RADICAL_HIGHWAY ||
		Global::levelID == LVL_FIRE_FIELD ||
		Global::levelID == LVL_BOBOMB_BATTLEFIELD ||
		Global::levelID == LVL_PUMPKIN_HILL ||
		Global::levelID == LVL_SAND_HILL ||
		Global::levelID == LVL_SNOWHEAD ||
		Global::levelID == LVL_SPEED_HIGHWAY ||
		Global::levelID == LVL_WILD_CANYON ||
		Global::levelID == LVL_TWINKLE_PARK ||
		Global::levelID == LVL_BOSS)
	{
		Global::stageUsesWater = false;
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




	//Read in BGM

	std::string bgmHasLoopLine;
	getline(file, bgmHasLoopLine);

	int bgmHasLoop = stoi(bgmHasLoopLine);


	std::string numBGMLine;
	getline(file, numBGMLine);

	int numBGM = stoi(numBGMLine);

	while (numBGM > 0)
	{
		std::string line;
		getline(file, line);

		char* bgmFileName = (char*)line.c_str();

		if (stageFault == 1)
		{
			AudioPlayer::loadBGM(bgmFileName);
		}

		numBGM--;
	}


	//Finish the level positions and cam settings
	char finishBuf[512];

	std::string finishPosition;
	getline(file, finishPosition);
	memset(finishBuf, 0, 512);
	memcpy(finishBuf, finishPosition.c_str(), finishPosition.size());
	int finishLength = 0;
	char** finishSplit = split(finishBuf, ' ', &finishLength);
	Global::gameStage->finishPlayerPosition.x = toFloat(finishSplit[0]);
	Global::gameStage->finishPlayerPosition.y = toFloat(finishSplit[1]);
	Global::gameStage->finishPlayerPosition.z = toFloat(finishSplit[2]);
	free(finishSplit);

	std::string finishCamVars;
	getline(file, finishCamVars);
	memset(finishBuf, 0, 512);
	memcpy(finishBuf, finishCamVars.c_str(), finishCamVars.size());
	finishSplit = split(finishBuf, ' ', &finishLength);
	Global::gameStage->finishPlayerRotY  = toFloat(finishSplit[0]);
	Global::gameStage->finishCameraPitch = toFloat(finishSplit[1]);
	free(finishSplit);

	//Global death height
	std::string deathHeightLine;
	getline(file, deathHeightLine);

	Global::deathHeight = stof(deathHeightLine);

	GuiManager::clearGuisToRender();

	Global::gameIsNormalMode = false;
	Global::gameIsHardMode = false;
	Global::gameIsChaoMode = false;
	Global::gameIsRingMode = false;

	Level* currentLevel = &Global::gameLevelData[Global::levelID];
	std::string missionType = (currentLevel->missionData[Global::gameMissionNumber])[0];

	if (missionType == "Normal") Global::gameIsNormalMode = true;
	if (missionType == "Ring")   Global::gameIsRingMode   = true;
	if (missionType == "Chao")   Global::gameIsChaoMode   = true;
	if (missionType == "Hard")   Global::gameIsHardMode   = true;

	if (Global::gameIsRingMode)
	{
		Global::gameRingTarget = std::stoi((currentLevel->missionData[Global::gameMissionNumber])[2]);
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

			processLine(lineSplit, splitLength);
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
		Global::gamePlayer->setCanMoveTimer(60);
		Global::bufferTime = 60;
	}

	Global::gameRingCount = 0;
	Global::gameScore = 0;
	GuiManager::setTimer(0, 0, 0);
	GuiManager::stopTimer();

	if (Global::spawnAtCheckpoint)
	{
		GuiManager::setTimer(Global::checkpointTimeMin, Global::checkpointTimeSec, Global::checkpointTimeCen);
	}
	else
	{
		if (bgmHasLoop != 0)
		{
			//By default, first 2 buffers are the intro and loop, respectively
			AudioPlayer::playBGMWithIntro(0, 1);
		}
		else
		{
			AudioPlayer::playBGM(0);
		}
	}

	GuiManager::addGuiToRender(GuiTextureResources::textureRing);

	Global::finishStageTimer = -1;

	Vector3f partVel(0, 0, 0);
	new Particle(ParticleResources::textureBlackFade, Global::gameCamera->getFadePosition1(), &partVel, 0, 60, 0, 400, 0, true);

	Global::gameState = STATE_RUNNING;
}


void LevelLoader::processLine(char** dat, int datLength)
{
	if (dat[0][0] == '#')
	{
		return;
	}

	int id = std::stoi(dat[0]);

	switch (id)
	{
		case 0: //Ring
		{
			Ring::loadStaticModels();
			Ring* ring = new Ring(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			INCR_NEW
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
			INCR_NEW
			Main_addEntity(spring);
			return;
		}

		case 2: //Dashpad
		{
			Dashpad::loadStaticModels();
			Dashpad* dashpad = new Dashpad(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6]), //rotation
				toFloat(dat[7]), toFloat(dat[8]), toInt(dat[9]));  //power, camYaw, time
			INCR_NEW
			Main_addEntity(dashpad);
			return;
		}

		case 3: //Line of Rings
		{
			Ring::loadStaticModels();
			Vector3f pos1(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			Vector3f pos2(toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6]));
			int numRings = toInt(dat[7]);

			float xDiff = pos2.x - pos1.x;
			float yDiff = pos2.y - pos1.y;
			float zDiff = pos2.z - pos1.z;

			if (numRings > 1)
			{
				for (int i = 0; i < numRings; i++)
				{
					Ring* ring = new Ring(pos1.x + i*(xDiff / (numRings - 1)), 
										  pos1.y + i*(yDiff / (numRings - 1)),
										  pos1.z + i*(zDiff / (numRings - 1)));
					INCR_NEW
					Main_addEntity(ring);
				}
			}
			else
			{
				Ring* ring = new Ring(pos1.x, pos1.y, pos1.z);
				INCR_NEW
				Main_addEntity(ring);
			}

			return;
		}

		case 4: //Circle of Rings
		{
			Ring::loadStaticModels();
			Vector3f centerPos(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			float ringRadius = toFloat(dat[4]);
			int numRings = toInt(dat[5]);

			if (numRings > 1)
			{
				float degreeSegment = 360.0f / numRings;
				Vector3f newPoint(0, centerPos.y, 0);

				for (int i = 0; i < numRings; i++)
				{
					newPoint.x = centerPos.x + ringRadius*cosf(toRadians(degreeSegment*i));
					newPoint.z = centerPos.z + ringRadius*sinf(toRadians(degreeSegment*i));
					Ring* ring = new Ring(newPoint.x, newPoint.y, newPoint.z);
					INCR_NEW
					Main_addEntity(ring);
				}
			}
			else
			{
				Ring* ring = new Ring(centerPos.x, centerPos.y, centerPos.z);
				INCR_NEW
				Main_addEntity(ring);
			}

			return;
		}

		case 5: //Half Circle of Rings
		{
			Ring::loadStaticModels();
			Vector3f centerPos(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			float ringRadius = toFloat(dat[4]);
			int numRings = toInt(dat[5]);

			if (numRings > 1)
			{
				float degreeSegment = 180.0f / numRings;
				Vector3f newPoint(0, centerPos.y, 0);

				for (int i = 0; i < numRings; i++)
				{
					newPoint.x = centerPos.x + ringRadius*cosf(toRadians(degreeSegment*i));
					newPoint.z = centerPos.z + ringRadius*sinf(toRadians(degreeSegment*i));
					Ring* ring = new Ring(newPoint.x, newPoint.y, newPoint.z);
					INCR_NEW
					Main_addEntity(ring);
				}
			}
			else
			{
				Ring* ring = new Ring(centerPos.x, centerPos.y, centerPos.z);
				INCR_NEW
				Main_addEntity(ring);
			}

			return;
		}
		
		case 6: //Player
		{
			PlayerSonic::deleteStaticModels();
			PlayerSonic::loadStaticModels();
			PlayerSonic* player = new PlayerSonic(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			INCR_NEW
			Global::gamePlayer = player;
			SkyManager::setCenterObject(player);
			player->setCameraAngles(Global::gameCamera->getYaw(), Global::gameCamera->getPitch());
			Main_addEntity(player);

			if (Global::spawnAtCheckpoint)
			{
				player->setPosition(Global::checkpointX, Global::checkpointY, Global::checkpointZ);
				Global::gameCamera->setYaw(Global::checkpointCamYaw);
				Global::gameCamera->setPitch(Global::checkpointCamPitch);
				player->setCameraAngles(Global::checkpointCamYaw, Global::checkpointCamPitch);
				player->setRotY(Global::checkpointRotY);
			}

			return;
		}

		case 7: //Sky Sphere
		{
			SkySphere::loadModels(dat[1], dat[2], dat[3]);
			Global::gameSkySphere->setScale(toFloat(dat[4]));
			Global::gameSkySphere->setFollowsY((bool)toInt(dat[5]));
			Global::gameSkySphere->setVisible(true);
			return;
		}

		case 8: //Teleport Zone
		{
			TeleportZone* zone = new TeleportZone(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6]), //target pos
				toFloat(dat[7]), toFloat(dat[8]), toFloat(dat[9]), //new yaw, new pitch, size (radius*2)
				toInt(dat[10]), toInt(dat[11]));                   //new music to play intro and loop
			INCR_NEW
			Main_addEntity(zone);
			return;
		}

		case 9: //Goal Sign
		{
			GoalSign::loadStaticModels();
			GoalSign* sign = new GoalSign(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), toInt(dat[4]));
			INCR_NEW
			Main_addEntity(sign);
			return;
		}

		case 10: //Emerald Coast Palmtree
		{
			EC_Palmtree::loadStaticModels();
			EC_Palmtree* palmtree = new EC_Palmtree(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6]), //rotation
				toFloat(dat[7]), 0);                               //scale, kind
			INCR_NEW
			Main_addEntity(palmtree);
			return;
		}

		case 11: //Rhino Tank
		{
			RhinoTank::loadStaticModels();
			RhinoTank* rhino = new RhinoTank(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3])); //position
			INCR_NEW
			Main_addEntity(rhino);
			return;
		}

		case 12: //Emerald Coast Sinking Platform
		{
			EC_SinkingPlatform::loadStaticModels();
			EC_SinkingPlatform* plat = new EC_SinkingPlatform(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3])); //position
			INCR_NEW
			Main_addEntity(plat);
			return;
		}

		case 13: //Emerald Coast Double-Waterfall
		{
			EC_Waterfall::loadStaticModels();
			EC_Waterfall* waterfall = new EC_Waterfall(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]));                 //rotation, scale
			INCR_NEW
			Main_addTransparentEntity(waterfall);
			return;
		}

		case 14: //Emerald Coast Flat Water
		{
			EC_FlatWater::loadStaticModels();
			EC_FlatWater* water = new EC_FlatWater();
			INCR_NEW
			Main_addTransparentEntity(water);
			return;
		}

		case 15: //Moto Bug
		{
			MotoBug::loadStaticModels();
			MotoBug* bug = new MotoBug(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3])); //position
			INCR_NEW
			Main_addEntity(bug);
			return;
		}

		case 16: //Green Hill Rock
		{
			GH_Rock::loadStaticModels();
			GH_Rock* rock = new GH_Rock(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), 1.0f); //yrot, scale
			INCR_NEW
			Main_addEntity(rock);
			return;
		}

		case 17: //Green Hill Tree
		{
			GH_Tree::loadStaticModels();
			GH_Tree* tree = new GH_Tree(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5])); //yrot, scale
			INCR_NEW
			Main_addEntity(tree);
			return;
		}

		case 18: //Green Hill Sunflower
		{
			GH_Sunflower::loadStaticModels();
			GH_Sunflower* flower = new GH_Sunflower(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), 1.0f); //yrot, scale
			INCR_NEW
			Main_addEntity(flower);
			return;
		}

		case 19: //Green Hill Flower
		{
			GH_Flower::loadStaticModels();
			GH_Flower* flower = new GH_Flower(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), 1.0f); //yrot, scale
			INCR_NEW
			Main_addEntity(flower);
			return;
		}

		case 20: //Green Hill Totem
		{
			GH_Totem::loadStaticModels();
			GH_Totem* totem = new GH_Totem(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), 1.0f); //yrot, scale
			INCR_NEW
			Main_addEntity(totem);
			return;
		}

		case 21: //Green Hill Totem Wings
		{
			GH_TotemWings::loadStaticModels();
			GH_TotemWings* totem = new GH_TotemWings(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), 1.0f); //yrot, scale
			INCR_NEW
			Main_addEntity(totem);
			return;
		}

		case 22: //Green Hill Grass
		{
			GH_Grass::loadStaticModels();
			GH_Grass* grass = new GH_Grass(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), 1.0f); //yrot, scale
			INCR_NEW
			Main_addEntity(grass);
			return;
		}

		case 23: //Green Hill Falling Platform
		{
			GH_FallingPlatform::loadStaticModels();
			GH_FallingPlatform* platform = new GH_FallingPlatform(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), 1.0f); //yrot, scale
			INCR_NEW
			Main_addEntity(platform);
			return;
		}

		case 24: //Green Hill Floating Platform
		{
			GH_FloatingPlatform::loadStaticModels();
			GH_FloatingPlatform* platform = new GH_FloatingPlatform(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), 1.0f); //yrot, scale
			INCR_NEW
			Main_addEntity(platform);
			return;
		}

		case 25: //Goal Trigger
		{
			GoalTrigger::loadStaticModels();
			GoalTrigger* trigger = new GoalTrigger(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //scale
			INCR_NEW
			Main_addEntity(trigger);
			return;
		}
		
		case 26: //Emerald Coast Umbrella
		{
			EC_Umbrella::loadStaticModels();
			EC_Umbrella* umbrella = new EC_Umbrella(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6]), //rotation
				toFloat(dat[7]));                                  //type
			INCR_NEW
			Main_addEntity(umbrella);
			return;
		}

		case 27: //Item Capsule
		{
			ItemCapsule::loadStaticModels();
			ItemCapsule* capsule = new ItemCapsule(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]),                  //rotation
				toInt(dat[6]));                                    //type
			INCR_NEW
			Main_addEntity(capsule);
			return;
		}

		case 28: //Spinner
		{
			Spinner::loadStaticModels();
			Spinner* spinner = new Spinner(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			INCR_NEW
			Main_addEntity(spinner);
			return;
		}

		case 29: //Speed Ramp
		{
			SpeedRamp::loadStaticModels();
			SpeedRamp* ramp = new SpeedRamp(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]),                  //rotation
				toFloat(dat[6]), toInt(dat[7]));                   //power, time
			INCR_NEW
			Main_addEntity(ramp);
			return;
		}

		case 32: //NPC
		{
			NPC::loadStaticModels();

			std::string message = "";
			for (int i = 6; i < datLength-1; i++)
			{
				message = message + dat[i] + " ";
			}
			message = message + dat[datLength-1];

			NPC* npc = new NPC(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toInt(dat[5]), message); //yrot, id, message
			INCR_NEW
			Main_addEntity(npc);
			return;
		}

		case 34: //Kill Box
		{
			KillBox* killbox = new KillBox(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]),  //corner 1
				toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6])); //corner 2
			INCR_NEW
			Main_addEntity(killbox);
			return;
		}

		case 35: //Kid Goron
		{
			SHD_GoronKid::loadStaticModels();
			SHD_GoronKid* goron = new SHD_GoronKid(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3])); //position
			INCR_NEW
			Main_addEntity(goron);
			return;
		}

		case 36: //Elder Goron
		{
			SHD_GoronElder::loadStaticModels();

			std::string message = "";
			for (int i = 5; i < datLength-1; i++)
			{
				message = message + dat[i] + " ";
			}
			message = message + dat[datLength-1];

			SHD_GoronElder* goron = new SHD_GoronElder(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), message);
			INCR_NEW
			Main_addEntity(goron);
			return;
		}

		case 37: //Low quality water
		{
			if (Global::useHighQualityWater == true)
			{
				return;
			}

			LowQualityWater::loadStaticModels();
			LowQualityWater* water = new LowQualityWater(toFloat(dat[1]), toFloat(dat[2]));
			INCR_NEW
			Main_addTransparentEntity(water);
			return;
		}

		case 38: //Emerald Coast Chair
		{
			EC_Chair::loadStaticModels();
			EC_Chair* chair = new EC_Chair(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
										   toFloat(dat[4]), toFloat(dat[5]));                 //rotation
			INCR_NEW
			Main_addEntity(chair);
			return;
		}

		case 39: //Emerald Coast Straw Roof Hut
		{
			EC_StrawRoofHut::loadStaticModels();
			EC_StrawRoofHut* hut = new EC_StrawRoofHut(
											toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
										    toFloat(dat[4]));                                  //rotation
			INCR_NEW
			Main_addEntity(hut);
			return;
		}

		case 40: //Emerald Coast Hut
		{
			EC_Hut::loadStaticModels();
			EC_Hut* hut = new EC_Hut(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			INCR_NEW
			Main_addEntity(hut);
			return;
		}
		
		case 41: //Emerald Coast Dock
		{
			EC_Dock::loadStaticModels();
			EC_Dock* dock = new EC_Dock(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			INCR_NEW
			Main_addEntity(dock);
			return;
		}

		case 42: //Emerald Coast Concrete Pole
		{
			EC_Pole::loadStaticModels();
			EC_Pole* pole = new EC_Pole(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			INCR_NEW
			Main_addEntity(pole);
			return;
		}

		case 43: //Emerald Coast Dock Corner
		{
			EC_DockCorner::loadStaticModels();
			EC_DockCorner* dock = new EC_DockCorner(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			INCR_NEW
			Main_addEntity(dock);
			return;
		}

		case 44: //Emerald Coast Raft Small
		{
			EC_RaftSmall::loadStaticModels();
			EC_RaftSmall* raft = new EC_RaftSmall(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			INCR_NEW
			Main_addEntity(raft);
			return;
		}

		case 45: //Emerald Coast Raft
		{
			EC_Raft::loadStaticModels();
			EC_Raft* raft = new EC_Raft(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			INCR_NEW
			Main_addEntity(raft);
			return;
		}

		case 46: //Emerald Coast Shark
		{
			EC_Shark::loadStaticModels();
			EC_Shark* shark = new EC_Shark(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3])); //position
			INCR_NEW
			Global::ecShark = shark;
			Main_addEntity(shark);
			return;
		}

		case 47: //Spikeball
		{
			Spikeball::loadStaticModels();
			Spikeball* ball = new Spikeball(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]));                 //radius, angVel
			INCR_NEW
			Main_addEntity(ball);
			return;
		}

		case 48: //Emerald Coast Dolphin
		{
			EC_Dolphin::loadStaticModels();
			EC_Dolphin* dolphin = new EC_Dolphin(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), //rotY
				toFloat(dat[5]), toFloat(dat[6]), toFloat(dat[7]), //trigger position
				toFloat(dat[8])); //trigger radius
			INCR_NEW
			Main_addEntity(dolphin);
			return;
		}

		case 49: //Twinkle Park water
		{
			TP_FlatWater::loadStaticModels();
			TP_FlatWater* water = new TP_FlatWater;
			INCR_NEW
			Main_addTransparentEntity(water);
			return;
		}

		case 50: //Twinkle Park floating pad
		{
			TP_FloatingPad::loadStaticModels();
			TP_FloatingPad* pad = new TP_FloatingPad(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //rotY
			INCR_NEW
			Main_addEntity(pad);
			return;
		}

		case 51: //Twinkle Park spinning platform
		{
			TP_SpinningFloor::loadStaticModels();
			TP_SpinningFloor* plat = new TP_SpinningFloor(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3])); //position
			INCR_NEW
			Main_addEntity(plat);
			return;
		}

		case 52: //Fire field heal pad
		{
			FF_HealPads::loadStaticModels();
			FF_HealPads* plat = new FF_HealPads;
			INCR_NEW
			Main_addEntity(plat);
			return;
		}

		case 53: //Emerald Coast Transparent
		{
			EC_StageTransparent::loadStaticModels();
			EC_StageTransparent* trans = new EC_StageTransparent;
			INCR_NEW
			Main_addEntityPass2(trans);
			return;
		}

		case 54: //Snowhead Transparent
		{
			SHD_StageTransparent::loadStaticModels();
			SHD_StageTransparent* trans = new SHD_StageTransparent;
			INCR_NEW
			Main_addEntityPass2(trans);
			return;
		}

		case 55: //Speed Highway Fork+Bucket
		{
			SH_TurnAsi::loadStaticModels();
			SH_TurnAsi* turn = new SH_TurnAsi(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			INCR_NEW
			Main_addEntity(turn);
			return;
		}

		case 56: //Emerald Coast Big Rock
		{
			EC_BigRock::loadStaticModels();
			EC_BigRock* rock = new EC_BigRock(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6]), //rotation
				toFloat(dat[7]), toInt(dat[8]));                   //type
			INCR_NEW
			Main_addEntity(rock);
			return;
		}

		case 57: //Emerald Coast Rock Platform
		{
			EC_RockPlatform::loadStaticModels();
			EC_RockPlatform* rock = new EC_RockPlatform(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //rotation
			INCR_NEW
			Main_addEntity(rock);
			return;
		}

		case 58: //Seagull
		{
			EC_Seagull::loadStaticModels();
			EC_Seagull* rock = new EC_Seagull(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]),                                   //angle offset
				toFloat(dat[5]),                                   //flying speed
				toFloat(dat[6]),							       //flying radius
				toFloat(dat[7]),						           //radius amplitude
				toFloat(dat[8]),							       //radius delta
				toFloat(dat[9]),						           //height amplitude
				toFloat(dat[10]));							       //height delta
			INCR_NEW
			Main_addEntity(rock);
			return;
		}

		case 59: //Speed Highway Elevator Platform
		{
			SH_CranePlatform::loadStaticModels();
			SH_CranePlatform* cranePlat = new SH_CranePlatform(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]),				                   //rotY
				toFloat(dat[5]),				                   //speed
				toInt(dat[6]), toInt(dat[7]));	                   //point ids

			INCR_NEW
			Main_addEntity(cranePlat);
			return;
		}

		case 60: //Invisible point for paths
		{
			Point* point = new Point(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toInt(dat[4])); //point id

			INCR_NEW
			Main_addEntity(point);
			return;
		}

		case 61: //Path for the crane platform
		{
			SH_CranePlatformPath::loadStaticModels();
			SH_CranePlatformPath* cranePlatPath = new SH_CranePlatformPath(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //rotation

			INCR_NEW
			Main_addEntity(cranePlatPath);
			return;
		}
		
		case 62: //Path for the elevator platform
		{
			SH_ElevatorPlatformPath::loadStaticModels();
			SH_ElevatorPlatformPath* elevatorPlatPath = new SH_ElevatorPlatformPath(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //rotation

			INCR_NEW
			Main_addEntity(elevatorPlatPath);
			return;
		}

		case 63: //Speed Highway Elevator Platform
		{
			SH_ElevatorPlatform::loadStaticModels();
			SH_ElevatorPlatform* cranePlat = new SH_ElevatorPlatform(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]),				                   //rotY
				toFloat(dat[5]),				                   //speed
				toInt(dat[6]), toInt(dat[7]), toInt(dat[8]), toInt(dat[9]), //point ids
				toFloat(dat[10])); //timeOffset

			INCR_NEW
			Main_addEntity(cranePlat);
			return;
		}

		case 64: //Sound emitter
		{
			SoundEmitter* emitter = new SoundEmitter(
					toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
					toInt(dat[4])); //sound emitter id
			
			INCR_NEW
			Main_addEntity(emitter);
			return;
		}

		case 65: //Speed Highway Transparent
		{
			SH_StageTransparent::loadStaticModels();
			SH_StageTransparent* trans = new SH_StageTransparent;
			INCR_NEW
			Main_addEntityPass2(trans);
			return;
		}

		case 66: //Speed Highway Lamppost
		{
			SH_Lamppost::loadStaticModels();
			SH_Lamppost* post = new SH_Lamppost(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]),  //position
				toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6])); //rotation
			INCR_NEW
			Main_addEntity(post);
			return;
		}

		case 67: //Speed Highway Cone
		{
			SH_Cone::loadStaticModels();
			SH_Cone* cone = new SH_Cone(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6]), //rotation
				toInt(dat[7])); //cone kind
			INCR_NEW
			Main_addEntity(cone);
			return;
		}

		case 68: //Speed Highway Spotlight
		{
			SH_Spotlight::loadStaticModels();
			SH_Spotlight* spotlight = new SH_Spotlight(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]),  //position
				toFloat(dat[4]), toFloat(dat[5]), toFloat(dat[6])); //rotation
			INCR_NEW
			Main_addEntity(spotlight);
			return;
		}

		case 69: //Capsule
		{
			Capsule::loadStaticModels();
			Capsule* cap = new Capsule(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));  //position
			INCR_NEW
			Main_addEntity(cap);
			return;
		}
		
		case 70: //Tails
		{
			PlayerTails::deleteStaticModels();
			PlayerTails::loadStaticModels();
			PlayerTails* player = new PlayerTails(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			INCR_NEW
			Global::gamePlayer = player;
			SkyManager::setCenterObject(player);
			player->setCameraAngles(Global::gameCamera->getYaw(), Global::gameCamera->getPitch());
			Main_addEntity(player);

			if (Global::spawnAtCheckpoint)
			{
				player->setPosition(Global::checkpointX, Global::checkpointY, Global::checkpointZ);
				Global::gameCamera->setYaw(Global::checkpointCamYaw);
				Global::gameCamera->setPitch(Global::checkpointCamPitch);
				player->setCameraAngles(Global::checkpointCamYaw, Global::checkpointCamPitch);
				player->setRotY(Global::checkpointRotY);
			}

			return;
		}

		case 71: //Knuckles
		{
			PlayerKnuckles::deleteStaticModels();
			PlayerKnuckles::loadStaticModels();
			PlayerKnuckles* player = new PlayerKnuckles(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]));
			INCR_NEW
			Global::gamePlayer = player;
			SkyManager::setCenterObject(player);
			player->setCameraAngles(Global::gameCamera->getYaw(), Global::gameCamera->getPitch());
			Main_addEntity(player);

			if (Global::spawnAtCheckpoint)
			{
				player->setPosition(Global::checkpointX, Global::checkpointY, Global::checkpointZ);
				Global::gameCamera->setYaw(Global::checkpointCamYaw);
				Global::gameCamera->setPitch(Global::checkpointCamPitch);
				player->setCameraAngles(Global::checkpointCamYaw, Global::checkpointCamPitch);
				player->setRotY(Global::checkpointRotY);
			}

			return;
		}

		case 72: //Stage Transparent
		{
			StageTransparent* trans = new StageTransparent(dat[1], dat[2]);
			INCR_NEW
			if (strcmp("trans", dat[3]) == 0)
			{	
				Main_addTransparentEntity(trans);
			}
			else if (strcmp("pass2", dat[3]) == 0)
			{
				Main_addEntityPass2(trans);
			}
			else
			{
				std::fprintf(stdout, "Error: Stage Transparent object (72) not given 'trans' or 'pass2'\n");
			}
			return;
		}

		case 73: //Emerald Piece
		{
			EmeraldPiece::loadStaticModels();
			EmeraldPiece* piece = new EmeraldPiece(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toInt(dat[4]), toInt(dat[5]), //piece number, diggable,
				toFloat(dat[6]), toFloat(dat[7]), toFloat(dat[8]), //dig volume
				toInt(dat[9])); //is a hard mode piece
			INCR_NEW
			Main_addEntityPass2(piece);
			return;
		}

		case 74: //Emerald Manager
		{
			EmeraldManager* manager = new EmeraldManager;
			INCR_NEW
			Main_addEntity(manager);
			return;
		}

		case 75: //Breeze
		{
			WC_Breeze* breeze = new WC_Breeze(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5])); //radius, height
			INCR_NEW
			Main_addEntity(breeze);
			return;
		}

		case 76: //Delfino Plaza Palmtree
		{
			DP_Palmtree::loadStaticModels();
			DP_Palmtree* tree = new DP_Palmtree(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //rotation
			INCR_NEW
			Main_addEntity(tree);
			return;
		}

		case 77: //Delfino Plaza Leaves
		{
			DP_Leaves::loadStaticModels();
			DP_Leaves* leaves = new DP_Leaves(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //rotation
			INCR_NEW
			Main_addEntity(leaves);
			return;
		}

		case 78: //Noki Bay Palmtree
		{
			NB_Palmtree::loadStaticModels();
			NB_Palmtree* tree = new NB_Palmtree(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //rotation
			INCR_NEW
			Main_addEntity(tree);
			return;
		}

		case 79: //Noki Bay Water Platform
		{
			NB_WaterPlatform::loadStaticModels();
			NB_WaterPlatform* platform = new NB_WaterPlatform(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //rotation
			INCR_NEW
			Main_addEntity(platform);
			return;
		}

		case 80: //Noki Bay Water Platform Bounce
		{
			NB_WaterPlatformBounce::loadStaticModels();
			NB_WaterPlatformBounce* platform = new NB_WaterPlatformBounce(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //rotation
			INCR_NEW
			Main_addEntity(platform);
			return;
		}

		case 81: //Lost Chao
		{
			Chao::loadStaticModels();
			Chao* lostChao = new Chao(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //rotation
			INCR_NEW
			Main_addEntity(lostChao);
			return;
		}

		case 82: //Pumpkin Hill Clouds
		{
			PH_Clouds::loadStaticModels();
			PH_Clouds* clouds = new PH_Clouds(toFloat(dat[1]), toFloat(dat[2]));
			INCR_NEW
			Main_addTransparentEntity(clouds);
			return;
		}

		case 83: //Dry Lagoon Turtle
		{
			DL_Turtle::loadStaticModels();
			DL_Turtle* turtle = new DL_Turtle(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), toFloat(dat[4]),  //position, y rotation
				toFloat(dat[5]), toFloat(dat[6]), toFloat(dat[7]), toFloat(dat[8])); //target position, cam rotation
			INCR_NEW
			Main_addEntity(turtle);
			return;
		}

		case 84: //Camera Box
		{
			CameraBox::loadStaticModels();
			CameraBox* camBox = new CameraBox(
				toFloat(dat[ 1]), toFloat(dat[ 2]),                    //y rotation, pan speed
				toFloat(dat[ 3]), toFloat(dat[ 4]), toFloat(dat[5]),   //position
				toFloat(dat[ 6]), toFloat(dat[ 7]), toFloat(dat[ 8]),  //scale
				toFloat(dat[ 9]), toFloat(dat[10]), toFloat(dat[11]),  //point a
				toFloat(dat[12]), toFloat(dat[13]), toFloat(dat[14]),  //point b
				toInt  (dat[15]));                                     //flags
			INCR_NEW
			Main_addEntity(camBox);
			return;
		}

		case 85: //Radical Highawy Ramp
		{
			RH_Ramp::loadStaticModels();
			RH_Ramp* ramp = new RH_Ramp(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]));                 //rotation
			INCR_NEW
			Main_addEntity(ramp);
			return;
		}

		case 86: //Wild Canyon Teleport
		{
			WC_DigTeleport::loadStaticModels();
			WC_DigTeleport* warp = new WC_DigTeleport(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]),  //position
				toFloat(dat[4]),                                    //y rotation
				toFloat(dat[5]), toFloat(dat[6]), toFloat(dat[7])); //teleport position
			INCR_NEW
			Main_addEntity(warp);
			return;
		}

		case 87: //Checkpoint
		{
			Checkpoint::loadStaticModels();
			Checkpoint* check = new Checkpoint(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]));                                  //y rotation
			INCR_NEW
			Main_addEntity(check);
			return;
		}

		case 88: //Speed Highway Floating Platform
		{
			SH_FloatingPlatform::loadStaticModels();
			SH_FloatingPlatform* plat = new SH_FloatingPlatform(
				toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4]), toFloat(dat[5]));                 //y rotation, scale
			INCR_NEW
			Main_addEntity(plat);
			return;
		}

		case 89: //Final boss manager
		{
			B_Manager* manager = new B_Manager;
			INCR_NEW
			Main_addEntity(manager);
			return;
		}

		case 90: //Rocket
		{
			Rocket::loadStaticModels();
			Rocket* rocket = new Rocket(toInt(dat[1]), toInt(dat[2])); //Point IDs
			INCR_NEW
			Main_addEntity(rocket);
			return;
		}

		case 91: //Metal Harbor
		{
			MH_Manager* mh = new MH_Manager;
			INCR_NEW
			Main_addEntity(mh);
			return;
		}

		case 92: //Metal Harbor Tank
		{
			MH_Tank::loadStaticModels();
			MH_Tank* tank = new MH_Tank(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3])); //position
			INCR_NEW
			Main_addEntity(tank);
			return;
		}

		case 93: //Metal Harbor Giant Rocket
		{
			MH_GiantRocket::loadStaticModels();
			MH_GiantRocket* giantRocket = new MH_GiantRocket(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3])); //position
			INCR_NEW
			Main_addEntity(giantRocket);
			return;
		}

		case 94: //Metal Harbor Giant Rocket Base
		{
			MH_RocketBase::loadStaticModels();
			MH_RocketBase* rocketBase = new MH_RocketBase(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3])); //position
			INCR_NEW
			Main_addEntity(rocketBase);
			return;
		}

		case 95: //Metal Harbor Flat Path
		{
			MH_PathFlat::loadStaticModels();
			MH_PathFlat* pathFlat = new MH_PathFlat(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //y rotation
			INCR_NEW
			Main_addEntity(pathFlat);
			return;
		}

		case 96: //Metal Harbor Small Flat Path
		{
			MH_PathFlatSmall::loadStaticModels();
			MH_PathFlatSmall* pathFlatSmall = new MH_PathFlatSmall(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //y rotation
			INCR_NEW
			Main_addEntity(pathFlatSmall);
			return;
		}

		case 97: //Metal Harbor Diagonal Path
		{
			MH_PathDiagonal::loadStaticModels();
			MH_PathDiagonal* pathDiagonal = new MH_PathDiagonal(toFloat(dat[1]), toFloat(dat[2]), toFloat(dat[3]), //position
				toFloat(dat[4])); //y rotation
			INCR_NEW
			Main_addEntity(pathDiagonal);
			return;
		}

		default:
		{
			return;
		}
	}
}

void LevelLoader::loadLevelData()
{
	Global::gameLevelData.clear();

	std::ifstream file("res/Levels/LevelData.dat");
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file 'res/Levels/LevelData.dat'\n");
		file.close();
	}
	else
	{
		std::string line;
		getline(file, line);

		int levelCount = std::stoi(line.c_str());
		getline(file, line);

		while (levelCount > 0)
		{
			Level newLevel;

			getline(file, line);
			newLevel.fileName = line;

			getline(file, line);
			newLevel.displayName = line;

			getline(file, line);
			int missionCount = std::stoi(line);
			newLevel.numMissions = missionCount;

			while (missionCount > 0)
			{
				std::vector<std::string> missionData;

				getline(file, line);

				char lineBuf[256];
				memset(lineBuf, 0, 256);
				memcpy(lineBuf, line.c_str(), line.size());

				int splitLength = 0;
				char** lineSplit = split(lineBuf, ';', &splitLength);

				for (int i = 0; i < splitLength; i++)
				{
					missionData.push_back(lineSplit[i]);
				}

				free(lineSplit);

				newLevel.missionData.push_back(missionData);

				missionCount--;
			}

			Global::gameLevelData.push_back(newLevel);

			getline(file, line);

			levelCount--;
		}

		file.close();
	}
}

float LevelLoader::toFloat(char* input)
{
	return std::stof(input);
}

int LevelLoader::toInt(char* input)
{
	return std::stoi(input);
}

void LevelLoader::freeAllStaticModels()
{
	Ring::deleteStaticModels();
	PlayerSonic::deleteStaticModels();
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
	EC_Palmtree::deleteStaticModels();
	EC_Umbrella::deleteStaticModels();
	GoalSign::deleteStaticModels();
	Spikeball::deleteStaticModels();
	ManiaSonicModel::deleteStaticModels();
	Spinner::deleteStaticModels();
	EC_Dolphin::deleteStaticModels();
	TP_FlatWater::deleteStaticModels();
	TP_FloatingPad::deleteStaticModels();
	EC_SinkingPlatform::deleteStaticModels();
	TP_SpinningFloor::deleteStaticModels();
	FF_HealPads::deleteStaticModels();
	EC_StageTransparent::deleteStaticModels();
	SHD_StageTransparent::deleteStaticModels();
	SH_TurnAsi::deleteStaticModels();
	EC_BigRock::deleteStaticModels();
	EC_RockPlatform::deleteStaticModels();
	EC_Seagull::deleteStaticModels();
	ItemCapsule::deleteStaticModels();
	SH_CranePlatform::deleteStaticModels();
	SH_CranePlatformPath::deleteStaticModels();
	SH_StageTransparent::deleteStaticModels();
	SH_Lamppost::deleteStaticModels();
	SH_Cone::deleteStaticModels();
	SH_Spotlight::deleteStaticModels();
	SH_ElevatorPlatformPath::deleteStaticModels();
	SH_ElevatorPlatform::deleteStaticModels();
	Capsule::deleteStaticModels();
	PlayerTails::deleteStaticModels();
	PlayerKnuckles::deleteStaticModels();
	StageTransparent::deleteStaticModels();
	EmeraldPiece::deleteStaticModels();
	GoalTrigger::deleteStaticModels();
	DP_Palmtree::deleteStaticModels();
	DP_Leaves::deleteStaticModels();
	NB_Palmtree::deleteStaticModels();
	NB_WaterPlatform::deleteStaticModels();
	NB_WaterPlatformBounce::deleteStaticModels();
	Chao::deleteStaticModels();
	GH_FloatingPlatform::deleteStaticModels();
	GH_FallingPlatform::deleteStaticModels();
	GH_Rock::deleteStaticModels();
	GH_Totem::deleteStaticModels();
	GH_TotemWings::deleteStaticModels();
	GH_Tree::deleteStaticModels();
	GH_Grass::deleteStaticModels();
	GH_Sunflower::deleteStaticModels();
	GH_Flower::deleteStaticModels();
	RhinoTank::deleteStaticModels();
	MotoBug::deleteStaticModels();
	NPC::deleteStaticModels();
	SHD_GoronElder::deleteStaticModels();
	SHD_GoronKid::deleteStaticModels();
	PH_Clouds::deleteStaticModels();
	DL_Turtle::deleteStaticModels();
	CameraBox::deleteStaticModels();
	RH_Ramp::deleteStaticModels();
	WC_DigTeleport::deleteStaticModels();
	Checkpoint::deleteStaticModels();
	SH_FloatingPlatform::deleteStaticModels();
	B_Platform::deleteStaticModels();
	B_Meteor::deleteStaticModels();
	B_Earth::deleteStaticModels();
	B_MetalSonic::deleteStaticModels();
	Rocket::deleteStaticModels();
	MH_Tank::deleteStaticModels();
	MH_GiantRocket::deleteStaticModels();
	MH_RocketBase::deleteStaticModels();
	MH_PathFlat::deleteStaticModels();
	MH_PathFlatSmall::deleteStaticModels();
	MH_PathDiagonal::deleteStaticModels();
}