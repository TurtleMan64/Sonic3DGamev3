#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include <string>
#include <cstring>
#include <unordered_map>
#include <list>

#include <ctime>
#include <random>

#include "main.h"
#include "../renderEngine/renderEngine.h"
#include "../toolbox/input.h"
#include "../models/models.h"
#include "../shaders/shaders.h"
#include "../textures/textures.h"
#include "../entities/entities.h"
#include "../toolbox/vector.h"
#include "../toolbox/matrix.h"
#include "../entities/camera.h"
#include "../objLoader/objLoader.h"
#include "../entities/light.h"
#include "../entities/ring.h"
#include "../entities/playersonic.h"
#include "../entities/stage.h"
#include "../toolbox/levelloader.h"
#include "../collision/collisionchecker.h"
#include "../entities/skysphere.h"
#include "../renderEngine/skymanager.h"
#include "../animation/animationresources.h"
#include "../fontRendering/textmaster.h"
#include "../fontMeshCreator/fonttype.h"
#include "../fontMeshCreator/guitext.h"
#include "../toolbox/pausescreen.h"
#include "../guis/guimanager.h"
#include "../entities/spring.h"
#include "../entities/EmeraldCoast/ecshark.h"
#include "../water/waterframebuffers.h"
#include "../water/watershader.h"
#include "../water/waterrenderer.h"
#include "../water/watertile.h"
#include "../audio/audiomaster.h"
#include "../audio/audioplayer.h"
#include "../particles/particlemaster.h"
#include "../particles/particleresources.h"
#include "../toolbox/split.h"
#include "../shadows/shadowmapmasterrenderer.h"
#include "../shadows2/shadowmapmasterrenderer2.h"
#include "../postProcessing/postprocessing.h"
#include "../postProcessing/fbo.h"
#include "../guis/guirenderer.h"
#include "../guis/guitextureresources.h"
#include "../toolbox/mainmenu.h"
#include "../toolbox/level.h"

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#endif

#define DEV_MODE

#ifdef DEV_MODE
#include <thread>
#endif


std::unordered_map<Entity*, Entity*> gameEntities;
std::list<Entity*> gameEntitiesToAdd;
std::list<Entity*> gameEntitiesToDelete;

std::unordered_map<Entity*, Entity*> gameEntitiesPass2;
std::list<Entity*> gameEntitiesPass2ToAdd;
std::list<Entity*> gameEntitiesPass2ToDelete;

std::unordered_map<Entity*, Entity*> gameTransparentEntities;
std::list<Entity*> gameTransparentEntitiesToAdd;
std::list<Entity*> gameTransparentEntitiesToDelete;

Camera* Global::gameCamera = nullptr;
ControllablePlayer* Global::gamePlayer = nullptr;
Stage* Global::gameStage = nullptr;
SkySphere* Global::gameSkySphere = nullptr;
Light* Global::gameLightSun = nullptr;
Light* Global::gameLightMoon = nullptr;

WaterRenderer* Global::gameWaterRenderer = nullptr;
WaterFrameBuffers* Global::gameWaterFBOs = nullptr;
std::list<WaterTile*>* Global::gameWaterTiles = nullptr;

int Global::finishStageTimer = -1;

Fbo* Global::gameMultisampleFbo = nullptr;
Fbo* Global::gameOutputFbo = nullptr;
Fbo* Global::gameOutputFbo2 = nullptr;

bool Global::debugDisplay = false;
bool Global::frozen = false;
bool Global::step = false;

bool Global::useHighQualityWater = true;
unsigned Global::HQWaterReflectionWidth = 1280;
unsigned Global::HQWaterReflectionHeight = 720;
unsigned Global::HQWaterRefractionWidth = 1280;
unsigned Global::HQWaterRefractionHeight = 720;

bool Global::renderParticles = true;

bool Global::renderBloom = false;

bool Global::renderShadowsFar = false;
bool Global::renderShadowsClose = false;
int Global::shadowsFarQuality = 0;

//Emerald Coast
EC_Shark* Global::ecShark = nullptr;


extern bool INPUT_JUMP;
extern bool INPUT_ACTION;
extern bool INPUT_ACTION2;

extern bool INPUT_PREVIOUS_JUMP;
extern bool INPUT_PREVIOUS_ACTION;
extern bool INPUT_PREVIOUS_ACTION2;

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

int Global::countNew = 0;
int Global::countDelete = 0;
int Global::gameState = 0;
int Global::levelID = 0;
int Global::bufferTime = -1;
bool Global::shouldLoadLevel = false;
bool Global::isNewLevel = false;
std::string Global::levelName = "";
std::string Global::levelNameDisplay = "";
int Global::gameRingCount = 0;
int Global::gameScore = 0;
int Global::gameClock = 0;
float Global::deathHeight = -100.0f;

int Global::gameMissionNumber = 0;
std::string Global::gameMissionDescription = "";
bool Global::gameIsNormalMode = false;
bool Global::gameIsHardMode = false;
bool Global::gameIsChaoMode = false;
bool Global::gameIsRingMode = false;
int Global::gameRingTarget = 100;
std::vector<Level> Global::gameLevelData;
std::unordered_map<std::string, std::string> Global::gameSaveData;

bool Global::unlockedSonicDoll = true;
bool Global::unlockedMechaSonic = true;
bool Global::unlockedDage4 = true;
bool Global::unlockedManiaSonic = true;
bool Global::unlockedAmy = true;

void increaseProcessPriority();

void doListenThread();

void listen();

int main()
{
	#ifdef DEV_MODE
	std::thread listenThread(doListenThread);
	#endif

	increaseProcessPriority();

	Global::countNew = 0;
	Global::countDelete = 0;

	srand(0);

	createDisplay();

	Global::loadSaveData();

	#ifndef DEV_MODE
	FreeConsole();
	#endif

	Input_init();

	//This camera is never deleted.
	Camera cam;
	Global::gameCamera = &cam;

	Master_init();

	LevelLoader_loadLevelData();

	TextMaster::init();

	PauseScreen::init();

	GuiManager::init();

	AudioMaster::init();

	MainMenu::init();

	if (Global::renderParticles)
	{
		ParticleResources::loadParticles();
	}

	GuiTextureResources::loadGuiTextures();

	CollisionChecker::initChecker();
	AnimationResources::createAnimations();

	//This light never gets deleted.
	Light lightSun;
	Global::gameLightSun = &lightSun;

	//This light never gets deleted.
	Light lightMoon;
	Global::gameLightMoon = &lightMoon;

	//This stage never gets deleted.
	Stage stage;
	Global::gameStage = &stage;

	//This sky sphere never gets deleted.
	SkySphere skySphere;
	Global::gameSkySphere = &skySphere;


	SkyManager::initSkyManager(nullptr, nullptr);
	SkyManager::setTimeOfDay(155.0f);
	cam.setYaw(180);

	lightSun.getPosition()->x = 0;
	lightSun.getPosition()->y = 0;
	lightSun.getPosition()->z = 0;
	lightMoon.getPosition()->y = -100000;

	if (Global::useHighQualityWater)
	{
		Global::gameWaterFBOs = new WaterFrameBuffers; Global::countNew++;
		WaterShader* waterShader = new WaterShader; Global::countNew++;
		Global::gameWaterRenderer = new WaterRenderer(waterShader, Master_getProjectionMatrix(), Global::gameWaterFBOs, Master_getShadowRenderer()); Global::countNew++;
		Global::gameWaterTiles = new std::list<WaterTile*>; Global::countNew++;
		for (int r = -6; r < 6; r++) //-9 , 9
		{
			for (int c = -8; c < 8; c++) //-12  12
			{
				Global::gameWaterTiles->push_back(new WaterTile(r * 3000.0f, c * 3000.0f, 0.0f)); Global::countNew++;
			}
		}
	}

	if (Global::renderBloom)
	{
		Global::gameMultisampleFbo = new Fbo(SCR_WIDTH, SCR_HEIGHT); Global::countNew++;
		Global::gameOutputFbo = new Fbo(SCR_WIDTH, SCR_HEIGHT, Fbo::DEPTH_TEXTURE); Global::countNew++;
		Global::gameOutputFbo2 = new Fbo(SCR_WIDTH, SCR_HEIGHT, Fbo::DEPTH_TEXTURE); Global::countNew++;
		PostProcessing::init();
	}

	ParticleMaster::init(Master_getProjectionMatrix());


	double seconds = 0.0;
	double previousTime = 0.0;
	glfwSetTime(0);

	int frameCount = 0;

	//PauseScreen::pause();
	Global::gameState = STATE_TITLE;

	while (Global::gameState != STATE_EXITING && displayWantsToClose() == 0)
	{
		Input_pollInputs();

		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{
			std::fprintf(stdout, "########  GL ERROR  ########\n");
			std::fprintf(stdout, "%d\n", err);
		}

		ALenum erral = alGetError();
		if (erral != AL_NO_ERROR)
		{
			std::fprintf(stdout, "########  AL ERROR  ########\n");
			std::fprintf(stdout, "%d\n", erral);
		}

		if (Global::bufferTime >= 0)
		{
			Global::bufferTime -= 1;
		}
		if (Global::bufferTime == 0)
		{
			GuiManager::startTimer();
		}



		//long double thisTime = std::time(0);
		//std::fprintf(stdout, "time: %f time\n", thisTime);

		//entities managment
		for (auto entityToAdd : gameEntitiesToAdd)
		{
			gameEntities.insert(std::pair<Entity*, Entity*>(entityToAdd, entityToAdd));
		}
		gameEntitiesToAdd.clear();

		for (auto entityToDelete : gameEntitiesToDelete)
		{
			gameEntities.erase(entityToDelete);
			delete entityToDelete;
			Global::countDelete++;
		}
		gameEntitiesToDelete.clear();


		//entities pass2 managment
		for (auto entityToAdd : gameEntitiesPass2ToAdd)
		{
			gameEntitiesPass2.insert(std::pair<Entity*, Entity*>(entityToAdd, entityToAdd));
		}
		gameEntitiesPass2ToAdd.clear();

		for (auto entityToDelete : gameEntitiesPass2ToDelete)
		{
			gameEntitiesPass2.erase(entityToDelete);
			delete entityToDelete;
			Global::countDelete++;
		}
		gameEntitiesPass2ToDelete.clear();



		MainMenu::step();
		PauseScreen::step();

		switch (Global::gameState)
		{
			case STATE_RUNNING:
			{
				//game logic
				GuiManager::increaseTimer();
				for (auto e : gameEntities)
				{
					e.first->step();
				}
				for (auto e : gameEntitiesPass2)
				{
					e.first->step();
				}
				for (auto e : gameTransparentEntities)
				{
					e.first->step();
				}
				skySphere.step();
				Global::gameCamera->refresh();
				if (Global::renderParticles)
				{
					ParticleMaster::update(Global::gameCamera);
				}
				Global::gameClock++;

				if (Global::debugDisplay && Global::frozen)
				{
					Global::gameState = STATE_DEBUG;
				}

				if (Global::gameIsRingMode)
				{
					if (Global::gameRingCount >= Global::gameRingTarget && Global::finishStageTimer == -1)
					{
						Global::finishStageTimer = 0;
						GuiManager::stopTimer();
					}
				}
				break;
			}

			case STATE_PAUSED:
			{
				break;
			}

			case STATE_CUTSCENE:
			{
				Global::gameCamera->refresh();
				break;
			}

			case STATE_TITLE:
			{
				Global::gameCamera->refresh();
				if (Global::renderParticles)
				{
					ParticleMaster::update(Global::gameCamera);
				}
				break;
			}

			case STATE_DEBUG:
			{
				if (Global::gamePlayer != nullptr)
				{
					Global::gamePlayer->debugAdjustCamera();
				}

				Input_pollInputs();
				if (Global::step)
				{
					Global::gameState = STATE_RUNNING;
					Global::step = false;
				}
				
				if (Global::debugDisplay == false || Global::frozen == false)
				{
					Global::gameState = STATE_RUNNING;
				}
				break;
			}

			default:
				break;
		}

		SkyManager::calculateValues();

		//prepare entities to render
		for (auto e : gameEntities)
		{
			Master_processEntity(e.first);
		}
		for (auto e : gameEntitiesPass2)
		{
			Master_processEntityPass2(e.first);
		}
		for (auto e : gameTransparentEntities)
		{
			Master_processTransparentEntity(e.first);
		}
		
		Master_processEntity(&stage);
		Master_renderShadowMaps(&lightSun);
		Master_processEntity(&skySphere);



		if (Global::useHighQualityWater)
		{
			glEnable(GL_CLIP_DISTANCE0);
			bool aboveWater = (cam.getPosition()->y > 0);

			//reflection render
			Global::gameWaterFBOs->bindReflectionFrameBuffer();
			float distance = 2 * (cam.getPosition()->y);
			if (aboveWater)
			{
				cam.getPosition()->y -= distance;
				cam.invertPitch();
				Master_render(&cam, 0, 1, 0, 0.3f);
				if (Global::renderParticles)
				{
					ParticleMaster::renderParticles(&cam, SkyManager::getOverallBrightness(), 1);
				}
				cam.getPosition()->y += distance;
				cam.invertPitch();
			}
			else
			{
				cam.getPosition()->y -= distance;
				cam.invertPitch();
				Master_render(&cam, 0, -1, 0, 0.3f);
				if (Global::renderParticles)
				{
					ParticleMaster::renderParticles(&cam, SkyManager::getOverallBrightness(), -1);
				}
				cam.getPosition()->y += distance;
				cam.invertPitch();
			}
			Global::gameWaterFBOs->unbindCurrentFrameBuffer();

			//refraction render
			Global::gameWaterFBOs->bindRefractionFrameBuffer();
			if (aboveWater)
			{
				Master_render(&cam, 0, -1, 0, 0.3f);
				if (Global::renderParticles)
				{
					ParticleMaster::renderParticles(&cam, SkyManager::getOverallBrightness(), -1);
				}
			}
			else
			{
				Master_render(&cam, 0, 1, 0, 0.3f);
				if (Global::renderParticles)
				{
					ParticleMaster::renderParticles(&cam, SkyManager::getOverallBrightness(), 1);
				}
			}
			Global::gameWaterFBOs->unbindCurrentFrameBuffer();

			glDisable(GL_CLIP_DISTANCE0);
		}

		if (Global::renderBloom)
		{
			Global::gameMultisampleFbo->bindFrameBuffer();
		}

		Vector3f camVel = cam.calcVelocity();
		if (Global::gamePlayer != nullptr)
		{
			Vector3f newVel = Global::gamePlayer->getOverallVel();
			camVel.set(&newVel);
		}
		AudioMaster::updateListenerData(cam.getPosition(), &camVel, cam.getYaw(), cam.getPitch());


		Master_render(&cam, 0, 1, 0, 1000);

		if (Global::useHighQualityWater)
		{
			Global::gameWaterRenderer->render(Global::gameWaterTiles, &cam, &lightSun);
		}
		if (Global::renderParticles)
		{
			ParticleMaster::renderParticles(&cam, SkyManager::getOverallBrightness(), 0);
		}

		if (Global::renderBloom)
		{
			Global::gameMultisampleFbo->unbindFrameBuffer();
			Global::gameMultisampleFbo->resolveToFbo(GL_COLOR_ATTACHMENT0, Global::gameOutputFbo);
			Global::gameMultisampleFbo->resolveToFbo(GL_COLOR_ATTACHMENT1, Global::gameOutputFbo2);
			PostProcessing::doPostProcessing(Global::gameOutputFbo->getColourTexture(), Global::gameOutputFbo2->getColourTexture());
		}

		Master_clearEntities();
		Master_clearEntitiesPass2();
		Master_clearTransparentEntities();

		GuiManager::refresh();
		TextMaster::render();

		updateDisplay();

		AudioPlayer::refreshBGM();

		frameCount++;
		seconds = glfwGetTime();

		if (Global::finishStageTimer >= 0)
		{
			if (Global::finishStageTimer == 0)
			{
				//Add score based on timer
				Global::gameScore += std::max(0, 11200 - 20*(GuiManager::getMinutes()*60 + GuiManager::getSeconds()));
			}

			Global::finishStageTimer++;

			if (Global::finishStageTimer > 460)
			{
				LevelLoader_loadTitle();
			}

			if (Global::finishStageTimer == 360)
			{
				Global::calculateRankAndUpdate();
			}
		}

		if (Global::shouldLoadLevel)
		{
			Global::shouldLoadLevel = false;
			LevelLoader_loadLevel(Global::levelName);
		}

		if (seconds - previousTime >= 1.0)
		{
			//std::fprintf(stdout, "fps: %f\n", frameCount / (seconds - previousTime));
			//std::fprintf(stdout, "diff: %d\n", Global::countNew - Global::countDelete);
			//Loader_printInfo();
			//std::fprintf(stdout, "entity counts: %d %d %d\n", gameEntities.size(), gameEntitiesPass2.size(), gameTransparentEntities.size());
			frameCount = 0;
			previousTime = seconds;
		}
	}

	Global::saveSaveData();

	#ifdef DEV_MODE
	listenThread.detach();
	#endif

	Master_cleanUp();
	Loader_cleanUp();
	TextMaster::cleanUp();
	AudioMaster::cleanUp();
	GuiRenderer::cleanUp();
	if (Global::gameWaterFBOs != nullptr)
	{
		Global::gameWaterFBOs->cleanUp();
	}
	closeDisplay();

	return 0;
}

//The newEntity should be created with the new keyword, as it will be deleted later
void Main_addEntity(Entity* entityToAdd)
{
	gameEntitiesToAdd.push_back(entityToAdd);
}

void Main_deleteEntity(Entity* entityToDelete)
{
	gameEntitiesToDelete.push_back(entityToDelete);
}

void Main_deleteAllEntites()
{
	//Make sure no entities get left behind in transition
	for (auto entityToAdd : gameEntitiesToAdd)
	{
		gameEntities.insert(std::pair<Entity*, Entity*>(entityToAdd, entityToAdd));
	}
	gameEntitiesToAdd.clear();

	for (auto entityToDelete : gameEntitiesToDelete)
	{
		gameEntities.erase(entityToDelete);
		delete entityToDelete;
		Global::countDelete++;
	}
	gameEntitiesToDelete.clear();


	//Delete all the rest
	for (auto entityToDelete : gameEntities)
	{
		delete entityToDelete.first;
		Global::countDelete++;
	}
	gameEntities.clear();
}

void Main_addEntityPass2(Entity* entityToAdd)
{
	gameEntitiesPass2ToAdd.push_back(entityToAdd);
}

void Main_deleteEntityPass2(Entity* entityToDelete)
{
	gameEntitiesPass2ToDelete.push_back(entityToDelete);
}

void Main_deleteAllEntitesPass2()
{
	//Make sure no entities get left behind in transition
	for (auto entityToAdd : gameEntitiesPass2ToAdd)
	{
		gameEntitiesPass2.insert(std::pair<Entity*, Entity*>(entityToAdd, entityToAdd));
	}
	gameEntitiesPass2ToAdd.clear();

	for (auto entityToDelete : gameEntitiesPass2ToDelete)
	{
		gameEntitiesPass2.erase(entityToDelete);
		delete entityToDelete;
		Global::countDelete++;
	}
	gameEntitiesPass2ToDelete.clear();

	for (auto entityToDelete : gameEntitiesPass2)
	{
		delete entityToDelete.first;
		Global::countDelete++;
	}
	gameEntitiesPass2.clear();
}

//Transparent entities shouldn't create new transparent entities from within their step function
void Main_addTransparentEntity(Entity* entityToAdd)
{
	gameTransparentEntities.insert(std::pair<Entity*, Entity*>(entityToAdd, entityToAdd));
}

void Main_deleteTransparentEntity(Entity* entityToDelete)
{
	gameTransparentEntities.erase(entityToDelete);
	delete entityToDelete;
	Global::countDelete++;
}

void Main_deleteAllTransparentEntites()
{
	for (auto entityToDelete : gameTransparentEntities)
	{
		delete entityToDelete.first;
		Global::countDelete++;
	}
	gameTransparentEntities.clear();
}

void increaseProcessPriority()
{
#ifdef _WIN32
	DWORD dwError;//, dwPriClass;

	if (!SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS))
	{
		dwError = GetLastError();
		_tprintf(TEXT("Failed to enter above normal mode (%d)\n"), (int)dwError);
	}

	// Display priority class

	//dwPriClass = GetPriorityClass(GetCurrentProcess());

	//_tprintf(TEXT("Current priority class is 0x%x\n"), dwPriClass);


	//DWORD dwThreadPri;

	if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL))
	{
		dwError = GetLastError();
		_tprintf(TEXT("Failed to enter above normal mode (%d)\n"), (int)dwError);
	}

	// Display thread priority

	//dwThreadPri = GetThreadPriority(GetCurrentThread());

	//_tprintf(TEXT("Current thread priority is 0x%x\n"), dwThreadPri);

#endif
}

void Global::checkErrorAL(const char* description)
{
	ALenum erral = alGetError();
	if (erral != AL_NO_ERROR)
	{
		fprintf(stdout, "########  AL ERROR  ########\n");
		fprintf(stdout, "%s     %d\n", description, erral);
	}
}

void Global::loadSaveData()
{
	Global::gameSaveData.clear();

	std::ifstream file("res/SaveData/SaveData.sav");
	if (!file.is_open())
	{
		std::fprintf(stdout, "No save data found. Creating new save file...\n");
		file.close();
		Global::saveSaveData();
	}
	else
	{
		std::string line;
		getline(file, line);

		while (!file.eof())
		{
			char lineBuf[512];
			memset(lineBuf, 0, 512);
			memcpy(lineBuf, line.c_str(), line.size());

			int splitLength = 0;
			char** lineSplit = split(lineBuf, ';', &splitLength);

			if (splitLength == 2)
			{
				Global::gameSaveData[lineSplit[0]] = lineSplit[1];
			}

			free(lineSplit);

			getline(file, line);
		}

		file.close();
	}
}

void Global::saveSaveData()
{
	std::ofstream file;
	file.open("res/SaveData/SaveData.sav", std::ios::out | std::ios::trunc);

	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Failed to create/access 'res/SaveData/SaveData.sav'\n");
		file.close();
	}
	else
	{
		std::unordered_map<std::string, std::string>::iterator it = Global::gameSaveData.begin();
 
		while (it != Global::gameSaveData.end())
		{
			file << it->first+";"+it->second+"\n";
			
			it++;
		}

		file.close();
	}
}

void Global::calculateRankAndUpdate()
{
	Level* currentLevel = &Global::gameLevelData[Global::levelID];

	if (Global::gameMissionNumber < currentLevel->numMissions)
	{
		std::string missionType = (currentLevel->missionData[Global::gameMissionNumber])[0];

		std::string missionRankString = "ERROR";
		switch (Global::gameMissionNumber)
		{
			case 0: missionRankString = "_M1_RANK"; break;
			case 1: missionRankString = "_M2_RANK"; break;
			case 2: missionRankString = "_M3_RANK"; break;
			case 3: missionRankString = "_M4_RANK"; break;
			default: break;
		}

		std::string missionScoreString = "ERROR";
		switch (Global::gameMissionNumber)
		{
			case 0: missionScoreString = "_M1_SCORE"; break;
			case 1: missionScoreString = "_M2_SCORE"; break;
			case 2: missionScoreString = "_M3_SCORE"; break;
			case 3: missionScoreString = "_M4_SCORE"; break;
			default: break;
		}

		std::string missionTimeString = "ERROR";
		switch (Global::gameMissionNumber)
		{
			case 0: missionTimeString = "_M1_TIME"; break;
			case 1: missionTimeString = "_M2_TIME"; break;
			case 2: missionTimeString = "_M3_TIME"; break;
			case 3: missionTimeString = "_M4_TIME"; break;
			default: break;
		}

		int newScore = Global::gameScore;
		int savedScore = -1;

		if (Global::gameSaveData.find(currentLevel->displayName+missionScoreString) != Global::gameSaveData.end())
		{
			std::string savedScoreString = Global::gameSaveData[currentLevel->displayName+missionScoreString];
			savedScore = std::stoi(savedScoreString);
		}

		if (newScore > savedScore)
		{
			std::string newScoreString = std::to_string(newScore);
			Global::gameSaveData[currentLevel->displayName+missionScoreString] = newScoreString;
			Global::saveSaveData();
		}

		int newTime = GuiManager::getTotalTimerInFrames();
		int savedTime = 360000;

		if (Global::gameSaveData.find(currentLevel->displayName+missionTimeString) != Global::gameSaveData.end())
		{
			std::string savedTimeString = Global::gameSaveData[currentLevel->displayName+missionTimeString];
			savedTime = std::stoi(savedTimeString);
		}

		if (newTime < savedTime)
		{
			std::string newTimeString = std::to_string(newTime);
			Global::gameSaveData[currentLevel->displayName+missionTimeString] = newTimeString;
			Global::saveSaveData();
		}

		if (missionType == "Normal" || missionType == "Hard")
		{
			if (newScore > savedScore)
			{
				int scoreForRankA = std::stoi((currentLevel->missionData[Global::gameMissionNumber])[1]);
				int scoreForRankB = (3*scoreForRankA)/4;
				int scoreForRankC = (2*scoreForRankA)/3;
				int scoreForRankD = (1*scoreForRankA)/2;

				int newRank = 0; //0 = E, 4 = A

				if      (newScore >= scoreForRankA) newRank = 4;
				else if (newScore >= scoreForRankB) newRank = 3;
				else if (newScore >= scoreForRankC) newRank = 2;
				else if (newScore >= scoreForRankD) newRank = 1;

				std::string newRankString = "ERROR";
				switch (newRank)
				{
					case 0: newRankString = "E"; break;
					case 1: newRankString = "D"; break;
					case 2: newRankString = "C"; break;
					case 3: newRankString = "B"; break;
					case 4: newRankString = "A"; break;
					default: break;
				}

				Global::gameSaveData[currentLevel->displayName+missionRankString]  = newRankString;

				Global::saveSaveData();
			}
		}
		else if (missionType == "Ring" || missionType == "Chao")
		{
			if (newTime < savedTime)
			{
				int timeForRankA = std::stoi((currentLevel->missionData[Global::gameMissionNumber])[1]);
				int timeForRankB = (4*timeForRankA)/3;
				int timeForRankC = (3*timeForRankA)/2;
				int timeForRankD = (2*timeForRankA)/1;

				int newRank = 0; //0 = E, 4 = A

				if      (newTime <= timeForRankA) newRank = 4;
				else if (newTime <= timeForRankB) newRank = 3;
				else if (newTime <= timeForRankC) newRank = 2;
				else if (newTime <= timeForRankD) newRank = 1;

				std::string newRankString = "ERROR";
				switch (newRank)
				{
					case 0: newRankString = "E"; break;
					case 1: newRankString = "D"; break;
					case 2: newRankString = "C"; break;
					case 3: newRankString = "B"; break;
					case 4: newRankString = "A"; break;
					default: break;
				}

				Global::gameSaveData[currentLevel->displayName+missionRankString] = newRankString;

				Global::saveSaveData();
			}
		}
	}
}

void doListenThread()
{
#ifdef _WIN32
	DWORD dwError;

	if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL))
	{
		dwError = GetLastError();
		_tprintf(TEXT("Failed to enter above normal mode (%d)\n"), (int)dwError);
	}
#endif

	listen();
}

//listen on stdin for coordinates
void listen()
{
	int loop = 1;
	std::string input;

	while (loop == 1)
	{
		std::getline(std::cin, input);

		if (input == "exit")
		{
			loop = 0;
		}
		else if (input.size() > 1)
		{
			fprintf(stdout, "input = '%s'\n", input.c_str());
			Global::gamePlayer->setGroundSpeed(0, 0);
			Global::gamePlayer->setxVelAir(0);
			Global::gamePlayer->setxVelAir(0);
			Global::gamePlayer->setyVel(0);
			if (input == "goff")
			{
				Global::gamePlayer->setGravity(0);
			}
			else if (input == "gon")
			{
				Global::gamePlayer->setGravity(0.08f);
			}
			else if (input.c_str()[0] == 'x')
			{
				const char* data = &input.c_str()[1];
				Global::gamePlayer->setX(std::stof(data));
				Global::gamePlayer->setGravity(0);
			}
			else if (input.c_str()[0] == 'y')
			{
				const char* data = &input.c_str()[1];
				Global::gamePlayer->setY(std::stof(data));
				Global::gamePlayer->setGravity(0);
			}
			else if (input.c_str()[0] == 'z')
			{
				const char* data = &input.c_str()[1];
				Global::gamePlayer->setZ(std::stof(data));
				Global::gamePlayer->setGravity(0);
			}
			else
			{
				char lineBuf[256]; //Buffer to copy line into
				memset(lineBuf, 0, 256);
				memcpy(lineBuf, input.c_str(), input.size());

				int splitLength = 0;
				char** lineSplit = split(lineBuf, ' ', &splitLength);

				if (splitLength == 3)
				{
					Global::gamePlayer->setX(std::stof(lineSplit[0]));
					Global::gamePlayer->setY(std::stof(lineSplit[1]));
					Global::gamePlayer->setZ(std::stof(lineSplit[2]));
					Global::gamePlayer->setGravity(0);
				}
				free(lineSplit);
			}
		}
	}
}
