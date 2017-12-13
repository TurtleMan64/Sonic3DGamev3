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

int gameState = 0;

std::unordered_map<Entity*, Entity*> gameEntities;
std::list<Entity*> gameEntitiesToAdd;
std::list<Entity*> gameEntitiesToDelete;

Camera* Global::gameCamera;

extern int INPUT_JUMP;
extern int INPUT_ACTION;
extern int INPUT_ACTION2;

extern int INPUT_PREVIOUS_JUMP;
extern int INPUT_PREVIOUS_ACTION;
extern int INPUT_PREVIOUS_ACTION2;

int Global::countNew = 0;
int Global::countDelete = 0;

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


int main()
{
	Global::countNew = 0;
	Global::countDelete = 0;

	createDisplay();

	Master_init();

	Ring::loadStaticModels();
	Player::loadStaticModels();

	Ring* myRing = new Ring(0, 0, 0);
	Global::countNew++;
	myRing->setVisible(1);

	Player* gamePlayer = new Player(0, 0, -50);
	Global::countNew++;
	gamePlayer->setVisible(1);

	Main_addEntity(gamePlayer);
	Main_addEntity(myRing);


	Light light;
	light.getPosition()->x = 0;
	light.getPosition()->y = 100000;
	light.getPosition()->z = 0;
	


	Camera cam;
	Global::gameCamera = &cam;


	double seconds = 0.0;
	double previousTime = 0.0;
	glfwSetTime(0);

	int frameCount = 0;

	while (gameState == 0 && displayWantsToClose() == 0)
	{
		pollInputs();
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


		if (INPUT_ACTION && !INPUT_PREVIOUS_ACTION)
		{
			Ring::loadStaticModels();
		}

		if (INPUT_JUMP && !INPUT_PREVIOUS_JUMP)
		{
			Ring::deleteStaticModels();
		}


		//game logic
		for (auto e : gameEntities)
		{
			//e.first->increaseRotation(0, 1, 0);
			e.first->step();
		}

		//cam.move();


		//render entities
		for (auto e : gameEntities)
		{
			if (e.first->getVisible() == 1)
			{
				Master_processEntity(e.first);
			}
		}

		Master_render(&light, &cam);

		updateDisplay();

		frameCount++;
		seconds = glfwGetTime();

		if (seconds - previousTime >= 1.0)
		{
			//std::fprintf(stdout, "fps: %f\n", frameCount / (seconds - previousTime));
			std::fprintf(stdout, "diff: %d\n", Global::countNew - Global::countDelete);
			frameCount = 0;
			previousTime = seconds;
		}
	}

	Ring::deleteStaticModels();
	Player::loadStaticModels();

	Master_cleanUp();
	//glDeleteProgram(shaderProgram);
	//shader.cleanUp();
	Loader_cleanUp();
	closeDisplay();

	return 0;
}




//joystick input example

//int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
//std::fprintf(stdout, "%d", present);
//if (present == 1)
//{
	//int axesCount;
	//const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
	//std::fprintf(stdout, "axes count: %d\n", axesCount);

	//for (int i = 0; i < axesCount; i++)
	//{
		//std::fprintf(stdout, "axis[%d]: %f\n", i, axes[i]);
	//}
	//std::fprintf(stdout, "\n");


	//int buttonCount;
	//const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	//for (int i = 0; i < 10; i++)
	//{
		//std::fprintf(stdout, "buttons[%d]: %d\n", i, buttons[i]);
	//}
	//std::fprintf(stdout, "\n");

	//const char *name = glfwGetJoystickName(GLFW_JOYSTICK_1);
	//std::fprintf(stdout, "joystick name: %s\n", name);
//}

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
	for (auto entityToDelete : gameEntities)
	{
		delete entityToDelete.first;
		Global::countDelete++;
	}
	gameEntities.clear();
}