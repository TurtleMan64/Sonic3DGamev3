#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "input.h"
#include "../renderEngine/skymanager.h"
#include "../engineTester/main.h"
#include "../entities/player.h"

extern GLFWwindow* window;


//vars to be used as input by other code
bool INPUT_JUMP = false;
bool INPUT_ACTION = false;
bool INPUT_ACTION2 = false;
bool INPUT_SHOULDER = false;
bool INPUT_SELECT = false;
bool INPUT_SPECIAL = false;
bool INPUT_START = false;

bool INPUT_PREVIOUS_JUMP = false;
bool INPUT_PREVIOUS_ACTION = false;
bool INPUT_PREVIOUS_ACTION2 = false;
bool INPUT_PREVIOUS_SHOULDER = false;
bool INPUT_PREVIOUS_SELECT = false;
bool INPUT_PREVIOUS_SPECIAL = false;
bool INPUT_PREVIOUS_START = false;

float INPUT_X = 0;
float INPUT_Y = 0;
float INPUT_X2 = 0;
float INPUT_Y2 = 0;

int MENU_X = 0;
int MENU_Y = 0;

float INPUT_ZOOM = 0;
float input_zoom_buffer = 0; //set in callback


//vars for use by us
double mousePreviousX = 0;
double mousePreviousY = 0;

bool tabInput = false;
bool tabInputPrevious = false;

//bool pressedA = false;
//bool previousPressedA = false;
//bool pressedB = false;
//bool previousPressedB = false;
//bool pressedX = false;
//bool previousPressedX = false;
//bool pressedY = false;
//bool previousPressedY = false;
//bool pressedStart = false;
//bool previousPressedStart = false;

int approxXLeft = 0;
int approxXLeftPrevious = 0;
int approxYLeft = 0;
int approxYLeftPrevious = 0;


//settings

bool freeMouse = true;

float mouseSensitivityX = 0.25f;
float mouseSensitivityY = 0.25f;

float stickSensitivityX = 2.5f;
float stickSensitivityY = 2.5f;

float triggerSensitivity = 2;

float scrollSensitivity = 10.0f;

int BUTTON_A = 0;
int BUTTON_X = 1;
int BUTTON_B = 2;
int BUTTON_Y = 3;
int BUTTON_RB = 5;
int BUTTON_LB = 4;
int BUTTON_SELECT = 6;
int BUTTON_START = 7;

int STICK_LX = 0;
float STICK_LX_SCALE = 1;
int STICK_LY = 1;
float STICK_LY_SCALE = 1;
int STICK_RX = 3;
float STICK_RX_SCALE = 1;
int STICK_RY = 4;
float STICK_RY_SCALE = 1;

float STICK_LXDEADZONE = 0.1f;
float STICK_LYDEADZONE = 0.1f;
float STICK_RXDEADZONE = 0.1f;
float STICK_RYDEADZONE = 0.1f;

int TRIGGER_L = 7;
float LT_NEUTRAL = -1;
float LT_MAX = 1;
float LT_RANGE = 2;
int TRIGGER_R = 5;
float RT_NEUTRAL = -1;
float RT_MAX = 1;
float RT_RANGE = 2;

float TRIGGER_DEADZONE = 0.3f;



void Input_pollInputs()
{
	glfwPollEvents();

	tabInputPrevious = tabInput;
	tabInput = false;

	INPUT_PREVIOUS_JUMP = INPUT_JUMP;
	INPUT_PREVIOUS_ACTION = INPUT_ACTION;
	INPUT_PREVIOUS_ACTION2 = INPUT_ACTION2;
	INPUT_PREVIOUS_SHOULDER = INPUT_SHOULDER;
	INPUT_PREVIOUS_SELECT = INPUT_SELECT;
	INPUT_PREVIOUS_SPECIAL = INPUT_SPECIAL;
	INPUT_PREVIOUS_START = INPUT_START;

	INPUT_JUMP = false;
	INPUT_ACTION = false;
	INPUT_ACTION2 = false;
	INPUT_SHOULDER = false;
	INPUT_SELECT = false;
	INPUT_SPECIAL = false;
	INPUT_START = false;

	//previousPressedA = pressedA;
	//previousPressedB = pressedB;
	//previousPressedX = pressedX;
	//previousPressedY = pressedY;
	//previousPressedStart = pressedStart;

	//pressedA = false;
	//pressedB = false;
	//pressedX = false;
	//pressedY = false;
	//pressedStart = false;


	INPUT_X = 0;
	INPUT_Y = 0;
	INPUT_X2 = 0;
	INPUT_Y2 = 0;

	INPUT_ZOOM = 0;



	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	if (present == 1)
	{
		int axesCount;
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		//std::fprintf(stdout, "axes count: %d\n", axesCount);

		//for (int i = 0; i < axesCount; i++)
		{
			//std::fprintf(stdout, "axis[%d]: %f\n", i, axes[i]);
		}

		//std::fprintf(stdout, "axis[7]: %f\n", axes[7]);


		if (STICK_LX < axesCount) { INPUT_X = axes[STICK_LX] * STICK_LX_SCALE; }
		if (STICK_LY < axesCount) { INPUT_Y = axes[STICK_LY] * STICK_LY_SCALE; }

		if (STICK_RX < axesCount) { INPUT_X2 = axes[STICK_RX] * STICK_RX_SCALE; }
		if (STICK_RY < axesCount) { INPUT_Y2 = axes[STICK_RY] * STICK_RY_SCALE; }

		if (abs(INPUT_X) < STICK_LXDEADZONE) { INPUT_X = 0; }
		if (abs(INPUT_Y) < STICK_LYDEADZONE) { INPUT_Y = 0; }
		if (abs(INPUT_X2) < STICK_RXDEADZONE) { INPUT_X2 = 0; }
		if (abs(INPUT_Y2) < STICK_RYDEADZONE) { INPUT_Y2 = 0; }

		INPUT_X2 = INPUT_X2 * stickSensitivityX;
		INPUT_Y2 = INPUT_Y2 * stickSensitivityY;


		float triggerLValue = 0;
		float triggerRValue = 0;

		if (TRIGGER_L < axesCount)
		{
			float rawValue = (axes[TRIGGER_L] - LT_NEUTRAL) / LT_RANGE;
			if (rawValue >= TRIGGER_DEADZONE) { triggerLValue = rawValue; }
		}

		if (TRIGGER_R < axesCount)
		{
			float rawValue = (axes[TRIGGER_R] - RT_NEUTRAL) / RT_RANGE;
			if (rawValue >= TRIGGER_DEADZONE) { triggerRValue = rawValue; }
		}

		INPUT_X2 += triggerSensitivity * (triggerLValue - triggerRValue);

		//std::fprintf(stdout, "\n");


		int buttonCount;
		const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

		//for (int i = 0; i < 10; i++)
		{
			//std::fprintf(stdout, "buttons[%d]: %d\n", i, buttons[i]);
		}
		//std::fprintf(stdout, "\n");
		if (BUTTON_A < buttonCount) { INPUT_JUMP = buttons[BUTTON_A]; }
		if (BUTTON_B < buttonCount) { INPUT_ACTION = buttons[BUTTON_B]; }
		if (BUTTON_X < buttonCount) { INPUT_ACTION2 = buttons[BUTTON_X]; }
		if (BUTTON_Y < buttonCount) { INPUT_SPECIAL = buttons[BUTTON_Y]; }
		if (BUTTON_START < buttonCount) { INPUT_START = buttons[BUTTON_START]; }

		//const char *name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		//std::fprintf(stdout, "joystick name: %s\n", name);
	}
	

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	//std::fprintf(stdout, "%f %f\n", xpos, ypos);
	if (freeMouse == false)
	{
		INPUT_X2 += (float)(mouseSensitivityX*(xpos - mousePreviousX));
		INPUT_Y2 += (float)(mouseSensitivityY*(ypos - mousePreviousY));
	}
	mousePreviousX = xpos;
	mousePreviousY = ypos;




	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		INPUT_JUMP = true;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		INPUT_ACTION = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		INPUT_ACTION2 = true;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		INPUT_SPECIAL = true;
	}
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		INPUT_START = true;
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

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		tabInput = true;
	}

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		SkyManager::increaseTimeOfDay(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		SkyManager::increaseTimeOfDay(-0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		if (Global::gamePlayer != nullptr)
		{
			Global::gamePlayer->goUp();
		}
	}

	if (tabInput && !tabInputPrevious)
	{
		if (freeMouse)
		{
			freeMouse = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			freeMouse = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	float mag = (float)sqrt(INPUT_X*INPUT_X + INPUT_Y*INPUT_Y);
	if (mag > 1)
	{
		INPUT_X = INPUT_X / mag;
		INPUT_Y = INPUT_Y / mag;
	}

	if (input_zoom_buffer != 0)
	{
		INPUT_ZOOM = scrollSensitivity*input_zoom_buffer;
		input_zoom_buffer = 0;
	}

	approxXLeftPrevious = approxXLeft;
	approxXLeft = (int)round(INPUT_X);
	approxYLeftPrevious = approxYLeft;
	approxYLeft = (int)round(INPUT_Y);

	if (approxXLeft != 0)
	{
		MENU_X = approxXLeft - approxXLeftPrevious;
	}

	if(approxYLeft != 0)
	{
		MENU_Y = approxYLeft - approxYLeftPrevious;
	}
}

void Input_init()
{
	//load sensitivity and button mappings from external file
}