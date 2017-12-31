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


std::unordered_map<Entity*, Entity*> gameEntities;
std::list<Entity*> gameEntitiesToAdd;
std::list<Entity*> gameEntitiesToDelete;

Camera* Global::gameCamera;
Player* Global::gamePlayer;
Stage* Global::gameStage;
SkySphere* Global::gameSkySphere;
Light* Global::gameLightSun;
Light* Global::gameLightMoon;

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

bool Global::unlockedSonicDoll = true;
bool Global::unlockedMechaSonic = true;
bool Global::unlockedDage4 = true;
bool Global::unlockedManiaSonic = true;

std::default_random_engine* Global::generator = new std::default_random_engine;
std::normal_distribution<double>* Global::distribution = new std::normal_distribution<double>(0.0, 1.0);


int main()
{
	Global::countNew = 0;
	Global::countDelete = 0;

	srand(0);

	createDisplay();

	Master_init();

	TextMaster::init();

	PauseScreen::init();

	GuiManager::init();

	//FontType font(Loader_loadTexture("res/Fonts/vipnagorgialla.png"), "res/Fonts/vipnagorgialla.fnt");

	//GUIText* text = new GUIText("this is a test text1", 3, &font, 0, 0, 1, false, true);

	//GUIText* text2 = new GUIText("this is a test text2", 3, &font, 0, 0.1f, 1, false, true);

	//GUIText* text3 = new GUIText("this is a test text3", 3, &font, 0, 0.2f, 1, false, true);

	//GUIText* text4 = new GUIText("this is a test text4", 3, &font, 0, 0.3f, 1, false, true);

	//GUIText* text5 = new GUIText("this is a test text5", 3, &font, 0, 0.4f, 1, false, true);
	//text->deleteMe();
	//delete text;
	//font.deleteMe();

	CollisionChecker::initChecker();
	AnimationResources::createAnimations();

	//Ring::loadStaticModels();
	//Player::loadStaticModels();

	//Ring* myRing = new Ring(0, 0, 0);
	//Global::countNew++;
	//myRing->setVisible(1);

	//Player* myPlayer = new Player(0, 0, -50);
	//Global::countNew++;
	//myPlayer->setVisible(1);

	//Global::gamePlayer = myPlayer;

	//Main_addEntity(myPlayer);
	//Main_addEntity(myRing);


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
	SkyManager::setTimeOfDay(155.5f);

	lightSun.getPosition()->y = 100000;
	lightMoon.getPosition()->y = -100000;


	double seconds = 0.0;
	double previousTime = 0.0;
	glfwSetTime(0);

	int frameCount = 0;

	PauseScreen::pause();

	while (Global::gameState != STATE_EXITING && displayWantsToClose() == 0)
	{
		Input_pollInputs();
		int err = glGetError();

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
				Global::gameCamera->refresh();
				GuiManager::increaseTimer();
				for (auto e : gameEntities)
				{
					e.first->step();
				}
				skySphere.step();
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

		//render entities
		for (auto e : gameEntities)
		{
			Master_processEntity(e.first);
		}
		Master_processEntity(&skySphere);
		Master_processEntity(&stage);

		Master_render(&cam);
		Master_clearEntities();

		GuiManager::refresh();
		TextMaster::render();

		updateDisplay();

		frameCount++;
		seconds = glfwGetTime();

		if (seconds - previousTime >= 1.0)
		{
			//std::fprintf(stdout, "fps: %f\n", frameCount / (seconds - previousTime));
			std::fprintf(stdout, "diff: %d\n", Global::countNew - Global::countDelete);
			Loader_printInfo();
			frameCount = 0;
			previousTime = seconds;
		}
	}

	Master_cleanUp();
	Loader_cleanUp();
	TextMaster::cleanUp();
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