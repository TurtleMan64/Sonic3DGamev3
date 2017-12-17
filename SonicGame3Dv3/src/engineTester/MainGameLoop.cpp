#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <string>
#include <unordered_map>
#include <list>

#include <ctime>

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

int gameState = 0;

std::unordered_map<Entity*, Entity*> gameEntities;
std::list<Entity*> gameEntitiesToAdd;
std::list<Entity*> gameEntitiesToDelete;

Camera* Global::gameCamera;
Player* Global::gamePlayer;
Stage* Global::gameStage;

extern bool INPUT_JUMP;
extern bool INPUT_ACTION;
extern bool INPUT_ACTION2;

extern bool INPUT_PREVIOUS_JUMP;
extern bool INPUT_PREVIOUS_ACTION;
extern bool INPUT_PREVIOUS_ACTION2;

int Global::countNew = 0;
int Global::countDelete = 0;


int main()
{
	Global::countNew = 0;
	Global::countDelete = 0;

	createDisplay();

	Master_init();

	CollisionChecker::initChecker();

	//Ring::loadStaticModels();
	//Player::loadStaticModels();

	Ring* myRing = new Ring(0, 0, 0);
	Global::countNew++;
	myRing->setVisible(1);

	Player* myPlayer = new Player(0, 0, -50);
	Global::countNew++;
	myPlayer->setVisible(1);

	Global::gamePlayer = myPlayer;

	Main_addEntity(myPlayer);
	Main_addEntity(myRing);


	Light light;
	light.getPosition()->x = 0;
	light.getPosition()->y = 100000;
	light.getPosition()->z = 0;
	

	//This camera is never deleted.
	Camera cam;
	Global::gameCamera = &cam;

	//This stage never gets deleted.
	Stage stage;
	Global::gameStage = &stage;


	double seconds = 0.0;
	double previousTime = 0.0;
	glfwSetTime(0);

	int frameCount = 0;

	LevelLoader_loadLevel("EmeraldCoast.lvl");

	while (gameState == 0 && displayWantsToClose() == 0)
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


		if (INPUT_ACTION && !INPUT_PREVIOUS_ACTION)
		{
			//LevelLoader_loadLevel("EmeraldCoast.lvl");
		}

		if (INPUT_JUMP && !INPUT_PREVIOUS_JUMP)
		{
			//LevelLoader_loadTitle();
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


		//game logic
		for (auto e : gameEntities)
		{
			e.first->step();
		}


		//render entities
		for (auto e : gameEntities)
		{
			Master_processEntity(e.first);
		}
		Master_processEntity(&stage);

		Master_render(&light, &cam);

		updateDisplay();

		frameCount++;
		seconds = glfwGetTime();

		if (seconds - previousTime >= 1.0)
		{
			std::fprintf(stdout, "fps: %f\n", frameCount / (seconds - previousTime));
			std::fprintf(stdout, "diff: %d\n", Global::countNew - Global::countDelete);
			Loader_printInfo();
			frameCount = 0;
			previousTime = seconds;
		}
	}

	Master_cleanUp();
	Loader_cleanUp();
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