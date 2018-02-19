#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <string>
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
#include "../entities/player.h"
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

#include <windows.h>
#include <tchar.h>


std::unordered_map<Entity*, Entity*> gameEntities;
std::list<Entity*> gameEntitiesToAdd;
std::list<Entity*> gameEntitiesToDelete;

std::unordered_map<Entity*, Entity*> gameTransparentEntities;

Camera* Global::gameCamera = nullptr;
Player* Global::gamePlayer = nullptr;
Stage* Global::gameStage = nullptr;
SkySphere* Global::gameSkySphere = nullptr;
Light* Global::gameLightSun = nullptr;
Light* Global::gameLightMoon = nullptr;

WaterRenderer* Global::gameWaterRenderer = nullptr;
WaterFrameBuffers* Global::gameWaterFBOs = nullptr;
std::list<WaterTile*>* Global::gameWaterTiles = nullptr;

bool Global::useHighQualityWater = true;
unsigned Global::HQWaterReflectionWidth = 1280;
unsigned Global::HQWaterReflectionHeight = 720;
unsigned Global::HQWaterRefractionWidth = 1280;
unsigned Global::HQWaterRefractionHeight = 720;

bool Global::renderParticles = true;

//Emerald Coast
EC_Shark* Global::ecShark = nullptr;


extern bool INPUT_JUMP;
extern bool INPUT_ACTION;
extern bool INPUT_ACTION2;

extern bool INPUT_PREVIOUS_JUMP;
extern bool INPUT_PREVIOUS_ACTION;
extern bool INPUT_PREVIOUS_ACTION2;

int Global::countNew = 0;
int Global::countDelete = 0;
int Global::gameState = 0;
int Global::levelID = 0;
int Global::bufferTime = -1;
bool Global::shouldRestartLevel = false;
std::string Global::levelName = "";
int Global::gameRingCount = 0;
int Global::gameClock = 0;

bool Global::unlockedSonicDoll = true;
bool Global::unlockedMechaSonic = true;
bool Global::unlockedDage4 = true;
bool Global::unlockedManiaSonic = true;
bool Global::unlockedAmy = true;

std::default_random_engine* Global::generator = new std::default_random_engine;
std::normal_distribution<double>* Global::distribution = new std::normal_distribution<double>(0.0, 1.0);

void increaseProcessPriority();

int main()
{
	increaseProcessPriority();

	Global::countNew = 0;
	Global::countDelete = 0;

	srand(0);

	createDisplay();

	Input_init();

	Master_init();

	TextMaster::init();

	PauseScreen::init();

	GuiManager::init();

	AudioMaster::init();

	if (Global::renderParticles)
	{
		ParticleResources::loadParticles();
	}

	CollisionChecker::initChecker();
	AnimationResources::createAnimations();

	//This light never gets deleted.
	Light lightSun;
	Global::gameLightSun = &lightSun;

	//This light never gets deleted.
	Light lightMoon;
	Global::gameLightMoon = &lightMoon;

	//This camera is never deleted.
	Camera cam;
	Global::gameCamera = &cam;

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
		Global::gameWaterRenderer = new WaterRenderer(waterShader, Master_getProjectionMatrix(), Global::gameWaterFBOs); Global::countNew++;
		Global::gameWaterTiles = new std::list<WaterTile*>; Global::countNew++;
		for (int r = -9; r < 9; r++) //-18 , 18
		{
			for (int c = -9; c < 9; c++) //-18  18
			{
				Global::gameWaterTiles->push_back(new WaterTile(r * 2000.0f, c * 2000.0f, 0.0f)); Global::countNew++;
			}
		}
	}

	ParticleMaster::init(Master_getProjectionMatrix());


	double seconds = 0.0;
	double previousTime = 0.0;
	glfwSetTime(0);

	int frameCount = 0;

	PauseScreen::pause();

	while (Global::gameState != STATE_EXITING && displayWantsToClose() == 0)
	{
		Input_pollInputs();
		GLenum err = glGetError();

		if (err == GL_NO_ERROR)
		{
			//std::fprintf(stdout, "NO ERROR\n");
		}
		else
		{
			std::fprintf(stdout, "########  ERROR  ########\n");
			std::fprintf(stdout, "%d\n", err);
		}

		if (Global::bufferTime >= 0)
		{
			Global::bufferTime -= 1;
		}
		if (Global::bufferTime == 0)
		{
			GuiManager::startTimer();
			if (Global::gamePlayer != nullptr)
			{
				Global::gamePlayer->setCanMove(true);
			}
		}

		if (Global::shouldRestartLevel)
		{
			Global::shouldRestartLevel = false;
			LevelLoader_loadLevel(Global::levelName);
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
		for (auto e : gameTransparentEntities)
		{
			Master_processTransparentEntity(e.first);
		}
		Master_processEntity(&skySphere);
		Master_processEntity(&stage);


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

		Master_clearEntities();
		Master_clearTransparentEntities();

		GuiManager::refresh();
		TextMaster::render();

		updateDisplay();

		frameCount++;
		seconds = glfwGetTime();

		if (seconds - previousTime >= 1.0)
		{
			//std::fprintf(stdout, "fps: %f\n", frameCount / (seconds - previousTime));
			//std::fprintf(stdout, "diff: %d\n", Global::countNew - Global::countDelete);
			//Loader_printInfo();
			frameCount = 0;
			previousTime = seconds;
		}
	}

	Master_cleanUp();
	Loader_cleanUp();
	TextMaster::cleanUp();
	AudioMaster::cleanUp();
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
		if (entityToDelete.first->isPlayer())
		{
			Global::gamePlayer = nullptr;
			SkyManager::setCenterObject(nullptr);
		}
		delete entityToDelete.first;
		Global::countDelete++;
	}
	gameEntities.clear();
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

}