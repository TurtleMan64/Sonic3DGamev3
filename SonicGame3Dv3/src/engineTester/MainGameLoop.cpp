#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <string>
#include <unordered_map>
#include <list>

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

int gameState = 0;

std::unordered_map<Entity*, Entity*> gameEntities;
std::list<Entity*> gameEntitiesToAdd;
std::list<Entity*> gameEntitiesToDelete;

extern int INPUT_JUMP;
extern int INPUT_ACTION;
extern int INPUT_ACTION2;

extern int INPUT_PREVIOUS_JUMP;
extern int INPUT_PREVIOUS_ACTION;
extern int INPUT_PREVIOUS_ACTION2;

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
	createDisplay();

	//ShaderProgram shader("src/shaders/vertexShader.txt", "src/shaders/fragmentShader.txt");
	//Renderer renderer(&shader);

	Master_init();

	std::vector<float> verticies = {
		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		-0.5f,0.5f,0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f
	};

	/*
	std::vector<float> verticies = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};*/

	std::vector<int> indices = {
		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22
	};

	std::vector<float> textureCoords = {
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0
	};

	RawModel model = loadObjModel("res/fern.obj");

	//RawModel model = loadToVAO(&verticies, &textureCoords, &indices);
	ModelTexture texture(loadTexture("res/fern.png"));
	texture.setShineDamper(10);
	texture.setReflectivity(1);
	texture.setHasTransparency(1);
	texture.setUsesFakeLighting(1);

	TexturedModel textureModel(&model, &texture);
	Vector3f vec(0,0,-25);
	
	Entity* myEntity = new Entity(&textureModel, &vec, 0, 0, 0, 1);
	Main_addEntity(myEntity);

	Light light;
	light.getPosition()->x = 200;
	light.getPosition()->y = 200;
	light.getPosition()->z = 100;
	


	Camera cam;

	//std::fprintf(stdout, "	generated tex id #%d\n", texture.getID());

	double seconds = 0.0;
	double previousTime = 0.0;
	glfwSetTime(0);

	int frameCount = 0;



	/*
	Cherno
	float positions[6] = {
		-0.5f, -0.5f, 
		 0.0f,  0.5f, 
		 0.5f, -0.5f
	};


	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
	
	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"out vec3 colour;\n"
		"void main()\n"
		"{\n"
		"	 gl_Position = position;\n"
		"    colour = vec3(position.x+0.5, 1.0, position.y+0.5);\n"
		"}\n";

	std::string fragmentShader =
		"#version 330 core\n"
		"in vec3 colour;\n"
		"layout(location = 0) out vec4 out_Color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	 out_Color = vec4(1.0, 1.0, 0.0, 1.0);\n"
		"    out_Color = vec4(colour, 1.0)\n;"
		"}\n";
		

	//unsigned int shaderProgram = CreateShader(vertexShader, fragmentShader);
	//glUseProgram(shaderProgram);
	
	//glEnable(GL_TEXTURE_2D);

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
		}
		gameEntitiesToDelete.clear();



		//game logic
		for (auto e : gameEntities)
		{
			e.first->increaseRotation(0, 1, 0);
		}

		//if (INPUT_JUMP && !INPUT_PREVIOUS_JUMP)
		{
			//std::fprintf(stdout, "jump!\n");
		}
		cam.move();


		//render entities
		for (auto e : gameEntities)
		{
			Master_processEntity(e.first);
		}

		Master_render(&light, &cam);

		updateDisplay();

		frameCount++;
		seconds = glfwGetTime();

		if (seconds - previousTime >= 1.0)
		{
			std::fprintf(stdout, "fps: %f\n", frameCount / (seconds - previousTime));
			frameCount = 0;
			previousTime = seconds;
		}
	}
	Master_cleanUp();
	//glDeleteProgram(shaderProgram);
	//shader.cleanUp();
	cleanUp();
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
