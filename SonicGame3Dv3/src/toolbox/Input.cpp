#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "input.h"

extern GLFWwindow* window;

int INPUT_JUMP = 0;
int INPUT_ACTION = 0;
int INPUT_ACTION2 = 0;

int INPUT_PREVIOUS_JUMP = 0;
int INPUT_PREVIOUS_ACTION = 0;
int INPUT_PREVIOUS_ACTION2 = 0;

float INPUT_X = 0;
float INPUT_Y = 0;

void pollInputs()
{
	glfwPollEvents();

	INPUT_PREVIOUS_JUMP = INPUT_JUMP;
	INPUT_PREVIOUS_ACTION = INPUT_ACTION;
	INPUT_PREVIOUS_ACTION2 = INPUT_ACTION2;
	INPUT_JUMP = 0;
	INPUT_ACTION = 0;
	INPUT_ACTION2 = 0;


	INPUT_X = 0;
	INPUT_Y = 0;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		INPUT_JUMP = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		INPUT_ACTION = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		INPUT_ACTION2 = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		INPUT_Y = -1;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		INPUT_Y = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		INPUT_X = -1;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		INPUT_X = 1;
	}
}