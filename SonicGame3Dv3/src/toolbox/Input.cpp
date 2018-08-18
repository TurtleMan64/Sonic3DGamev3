#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

#include "input.h"
#include "../renderEngine/skymanager.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../entities/camera.h"
#include "../entities/ring.h"
#include "maths.h"
#include "../toolbox/split.h"
#include <random>
#include <chrono>

extern GLFWwindow* window;

struct InputStruct Inputs{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

float input_zoom_buffer = 0; //set in callback

//vars for use by us
double mousePreviousX = 0;
double mousePreviousY = 0;

bool DEBUG_JUMP = false;
bool DEBUG_ACTION = false;
bool DEBUG_ACTION2 = false;
bool DEBUG_SHOULDER = false;
bool DEBUG_SELECT = false;
bool DEBUG_SPECIAL = false;
bool DEBUG_START = false;

bool DEBUG_PREVIOUS_JUMP = false;
bool DEBUG_PREVIOUS_ACTION = false;
bool DEBUG_PREVIOUS_ACTION2 = false;
bool DEBUG_PREVIOUS_SHOULDER = false;
bool DEBUG_PREVIOUS_SELECT = false;
bool DEBUG_PREVIOUS_SPECIAL = false;
bool DEBUG_PREVIOUS_START = false;

//settings

bool freeMouse = true;

float mouseSensitivityX = 0.25f;
float mouseSensitivityY = 0.25f;

float stickSensitivityX = 2.5f;
float stickSensitivityY = 2.5f;

float triggerSensitivity = 2;

float scrollSensitivity = 10.0f;

int CONTROLLER_ID = 0;

int BUTTON_A = 0;
int BUTTON_X = 1;
int BUTTON_B = 2;
int BUTTON_Y = 3;
int BUTTON_LB = 4;
int BUTTON_RB = 5;
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

	Inputs.tabInputPrevious = Inputs.tabInput;
	Inputs.tabInput = false;

	if (Global::gameState != STATE_DEBUG)
	{
		Inputs.INPUT_PREVIOUS_JUMP     = Inputs.INPUT_JUMP;
		Inputs.INPUT_PREVIOUS_ACTION   = Inputs.INPUT_ACTION;
		Inputs.INPUT_PREVIOUS_ACTION2  = Inputs.INPUT_ACTION2;
		Inputs.INPUT_PREVIOUS_SELECT   = Inputs.INPUT_SELECT;
		Inputs.INPUT_PREVIOUS_SHOULDER = Inputs.INPUT_SHOULDER;
		Inputs.INPUT_PREVIOUS_SPECIAL  = Inputs.INPUT_SPECIAL;
		Inputs.INPUT_PREVIOUS_START    = Inputs.INPUT_START;

		Inputs.INPUT_JUMP = false;
		Inputs.INPUT_ACTION = false;
		Inputs.INPUT_ACTION2 = false;
		Inputs.INPUT_SHOULDER = false;
		Inputs.INPUT_SELECT = false;
		Inputs.INPUT_SPECIAL = false;
		Inputs.INPUT_START = false;
	}

	DEBUG_PREVIOUS_JUMP = DEBUG_JUMP;
	DEBUG_PREVIOUS_ACTION = DEBUG_ACTION;
	DEBUG_PREVIOUS_ACTION2 = DEBUG_ACTION2;
	DEBUG_PREVIOUS_SHOULDER = DEBUG_SHOULDER;
	DEBUG_PREVIOUS_SELECT = DEBUG_SELECT;
	DEBUG_PREVIOUS_SPECIAL = DEBUG_SPECIAL;
	DEBUG_PREVIOUS_START = DEBUG_START;

	DEBUG_JUMP = false;
	DEBUG_ACTION = false;
	DEBUG_ACTION2 = false;
	DEBUG_SHOULDER = false;
	DEBUG_SELECT = false;
	DEBUG_SPECIAL = false;
	DEBUG_START = false;

	//Keys used for debug/frozen
	Inputs.INPUT_PREVIOUS_GRAVE      = Inputs.INPUT_GRAVE;
	Inputs.INPUT_PREVIOUS_SEMICOLON  = Inputs.INPUT_SEMICOLON;
	Inputs.INPUT_PREVIOUS_APOSTROPHE = Inputs.INPUT_APOSTROPHE;

	Inputs.INPUT_GRAVE = false;
	Inputs.INPUT_SEMICOLON = false;
	Inputs.INPUT_APOSTROPHE = false;


	Inputs.INPUT_X = 0;
	Inputs.INPUT_Y = 0;
	Inputs.INPUT_X2 = 0;
	Inputs.INPUT_Y2 = 0;

	Inputs.INPUT_ZOOM = 0;



	int present = glfwJoystickPresent(CONTROLLER_ID);
	if (present == 1)
	{
		int axesCount;
		const float *axes = glfwGetJoystickAxes(CONTROLLER_ID, &axesCount);

		Inputs.INPUT_X = axes[STICK_LX] * STICK_LX_SCALE;
		Inputs.INPUT_Y = axes[STICK_LY] * STICK_LY_SCALE;

		Inputs.INPUT_X2 = axes[STICK_RX] * STICK_RX_SCALE;
		Inputs.INPUT_Y2 = axes[STICK_RY] * STICK_RY_SCALE;

		if (abs(Inputs.INPUT_X)  < STICK_LXDEADZONE) { Inputs.INPUT_X  = 0; }
		if (abs(Inputs.INPUT_Y)  < STICK_LYDEADZONE) { Inputs.INPUT_Y  = 0; }
		if (abs(Inputs.INPUT_X2) < STICK_RXDEADZONE) { Inputs.INPUT_X2 = 0; }
		if (abs(Inputs.INPUT_Y2) < STICK_RYDEADZONE) { Inputs.INPUT_Y2 = 0; }

		Inputs.INPUT_X2 = Inputs.INPUT_X2 * stickSensitivityX;
		Inputs.INPUT_Y2 = Inputs.INPUT_Y2 * stickSensitivityY;


		float triggerLValue = 0;
		float triggerRValue = 0;


		float rawValue = (axes[TRIGGER_L] - LT_NEUTRAL) / LT_RANGE;
		if (rawValue >= TRIGGER_DEADZONE) { triggerLValue = rawValue; }

		rawValue = (axes[TRIGGER_R] - RT_NEUTRAL) / RT_RANGE;
		if (rawValue >= TRIGGER_DEADZONE) { triggerRValue = rawValue; }


		Inputs.INPUT_X2 += triggerSensitivity * (triggerLValue - triggerRValue);


		int buttonCount;
		const unsigned char *buttons = glfwGetJoystickButtons(CONTROLLER_ID, &buttonCount);

		DEBUG_JUMP     = buttons[BUTTON_A];
		DEBUG_ACTION   = buttons[BUTTON_B];
		DEBUG_ACTION2  = buttons[BUTTON_X];
		DEBUG_SPECIAL  = buttons[BUTTON_Y];
		DEBUG_SHOULDER = buttons[BUTTON_RB];
		DEBUG_START    = buttons[BUTTON_START];

		//const char *name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		//std::fprintf(stdout, "joystick name: %s\n", name);
	}


	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (freeMouse == false)
	{
		Inputs.INPUT_X2 += (float)(mouseSensitivityX*(xpos - mousePreviousX));
		Inputs.INPUT_Y2 += (float)(mouseSensitivityY*(ypos - mousePreviousY));
	}
	mousePreviousX = xpos;
	mousePreviousY = ypos;




	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		DEBUG_JUMP = true;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		DEBUG_ACTION = true;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		DEBUG_ACTION2 = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		DEBUG_SPECIAL = true;
	}
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		DEBUG_START = true;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		DEBUG_SHOULDER = true;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Inputs.INPUT_Y = -1;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Inputs.INPUT_Y = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Inputs.INPUT_X = -1;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Inputs.INPUT_X = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		Inputs.tabInput = true;
	}

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		SkyManager::increaseTimeOfDay(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		SkyManager::increaseTimeOfDay(-0.5f);
	}

	#ifdef DEV_MODE
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		Global::gameCamera->setRoll(Global::gameCamera->getRoll() + 4.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		Global::gameCamera->setRoll(Global::gameCamera->getRoll() - 4.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		float spoutSpd = 3.0f;
		float anglH = (float)(M_PI * 2 * ((rand() % 1024) / 1024.0));
		float randNumber = Maths::nextGaussian();
		float anglV = (toRadians((randNumber * 36 + 90)));

		float yspd = spoutSpd*sinf(anglV);
		float hpt  = spoutSpd*cosf(anglV);

		float xspd = hpt*cosf(anglH);
		float zspd = hpt*sinf(anglH);

		Vector3f* spawnPoint = Global::gamePlayer->getPosition();
		Ring* newRing = new Ring(spawnPoint->x, spawnPoint->y + 10, spawnPoint->z, xspd, yspd, zspd); INCR_NEW
		Main_addEntity(newRing);
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		if (Global::gamePlayer != nullptr)
		{
			Global::gamePlayer->goUp();
		}
	}

	// Debug
	if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
	{
		if (!Inputs.INPUT_PREVIOUS_GRAVE && Global::debugDisplay == false)
		{
			Global::debugDisplay = true;
		}
		else if (!Inputs.INPUT_PREVIOUS_GRAVE)
		{
			Global::debugDisplay = false;
		}
		Inputs.INPUT_GRAVE = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS)
	{
		if (!Inputs.INPUT_PREVIOUS_SEMICOLON && Global::debugDisplay && Global::frozen == false)
		{
			Global::frozen = true;
		}
		else if (!Inputs.INPUT_PREVIOUS_SEMICOLON && Global::debugDisplay)
		{
			Global::frozen = false;
		}
		Inputs.INPUT_SEMICOLON = true;
	}
	if (glfwGetKey(window, GLFW_KEY_APOSTROPHE) == GLFW_PRESS)
	{
		if (!Inputs.INPUT_PREVIOUS_APOSTROPHE && Global::debugDisplay && Global::frozen)
		{
			Global::step = true;
		}
		Inputs.INPUT_APOSTROPHE = true;
	}
	#endif

	if (Global::gameState != STATE_DEBUG)
	{
		Inputs.INPUT_JUMP     = DEBUG_JUMP;
		Inputs.INPUT_ACTION   = DEBUG_ACTION;
		Inputs.INPUT_ACTION2  = DEBUG_ACTION2;
		Inputs.INPUT_SHOULDER = DEBUG_SHOULDER;
		Inputs.INPUT_SELECT   = DEBUG_SELECT;
		Inputs.INPUT_SPECIAL  = DEBUG_SPECIAL;
		Inputs.INPUT_START    = DEBUG_START;
	}

	#ifdef DEV_MODE
	if (Inputs.INPUT_SHOULDER && !Inputs.INPUT_PREVIOUS_SHOULDER)
	{
		if (Global::gamePlayer != nullptr)
		{
			std::fprintf(stdout, "Time of day: %f\n", SkyManager::getTimeOfDay());
			std::fprintf(stdout, "[%f, %f, %f]\n", Global::gamePlayer->getPosition()->x, Global::gamePlayer->getPosition()->y, Global::gamePlayer->getPosition()->z);
			std::fprintf(stdout, "player rot = %f\n", Global::gamePlayer->getRotY());
			std::fprintf(stdout, "cam yaw: %f,   cam pitch: %f\n", Global::gameCamera->getYaw(), Global::gameCamera->getPitch());
			std::fprintf(stdout, "\n");
		}
	}
	#endif

	if (Inputs.tabInput && !Inputs.tabInputPrevious)
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

	float mag = sqrtf(Inputs.INPUT_X*Inputs.INPUT_X + Inputs.INPUT_Y*Inputs.INPUT_Y);
	if (mag > 1)
	{
		Inputs.INPUT_X = Inputs.INPUT_X / mag;
		Inputs.INPUT_Y = Inputs.INPUT_Y / mag;
	}

	if (input_zoom_buffer != 0)
	{
		Inputs.INPUT_ZOOM = scrollSensitivity*input_zoom_buffer;
		input_zoom_buffer = 0;
	}

	Inputs.approxXLeftPrevious = Inputs.approxXLeft;
	Inputs.approxXLeft = (int)round(Inputs.INPUT_X);
	Inputs.approxYLeftPrevious = Inputs.approxYLeft;
	Inputs.approxYLeft = (int)round(Inputs.INPUT_Y);

	if (Inputs.approxXLeft != 0)
	{
		Inputs.MENU_X = Inputs.approxXLeft - Inputs.approxXLeftPrevious;
	}

	if (Inputs.approxYLeft != 0)
	{
		Inputs.MENU_Y = Inputs.approxYLeft - Inputs.approxYLeftPrevious;
	}
}

void Input_init()
{
	Inputs.uniqueVar = 1149650285; //Value that is very easy to find with a memory scan

	//load sensitivity and button mappings from external file

	std::ifstream file("Settings/CameraSensitivity.ini");
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file 'Settings/CameraSensitivity.ini'\n");
		file.close();
	}
	else
	{
		std::string line;

		while (!file.eof())
		{
			getline(file, line);

			char lineBuf[512]; //Buffer to copy line into
			memset(lineBuf, 0, 512);
			memcpy(lineBuf, line.c_str(), line.size());

			int splitLength = 0;
			char** lineSplit = split(lineBuf, ' ', &splitLength);

			if (splitLength == 2)
			{
				if (strcmp(lineSplit[0], "Mouse_X") == 0)
				{
					mouseSensitivityX = std::stof(lineSplit[1], nullptr);
				}
				else if (strcmp(lineSplit[0], "Mouse_Y") == 0)
				{
					mouseSensitivityY = std::stof(lineSplit[1], nullptr);
				}
				else if (strcmp(lineSplit[0], "Stick_X") == 0)
				{
					stickSensitivityX = std::stof(lineSplit[1], nullptr);
				}
				else if (strcmp(lineSplit[0], "Stick_Y") == 0)
				{
					stickSensitivityY = std::stof(lineSplit[1], nullptr);
				}
				else if (strcmp(lineSplit[0], "Triggers") == 0)
				{
					triggerSensitivity = std::stof(lineSplit[1], nullptr);
				}
			}

			free(lineSplit);
		}
		file.close();
	}


	std::ifstream file2("Settings/ControllerConfig.ini");
	if (!file2.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file 'Settings/ControllerConfig.ini'\n");
		file2.close();
	}
	else
	{
		std::string line;

		while (!file2.eof())
		{
			getline(file2, line);

			char lineBuf[512]; //Buffer to copy line into
			memset(lineBuf, 0, 512);
			memcpy(lineBuf, line.c_str(), line.size());

			int splitLength = 0;
			char** lineSplit = split(lineBuf, ' ', &splitLength);

			if (splitLength == 2)
			{
				if (strcmp(lineSplit[0], "A") == 0)
				{
					BUTTON_A = std::stoi(lineSplit[1], nullptr, 10);
				}
				else if (strcmp(lineSplit[0], "B") == 0)
				{
					BUTTON_B = std::stoi(lineSplit[1], nullptr, 10);
				}
				else if (strcmp(lineSplit[0], "X") == 0)
				{
					BUTTON_X = std::stoi(lineSplit[1], nullptr, 10);
				}
				else if (strcmp(lineSplit[0], "Y") == 0)
				{
					BUTTON_Y = std::stoi(lineSplit[1], nullptr, 10);
				}
				else if (strcmp(lineSplit[0], "LB") == 0)
				{
					BUTTON_LB = std::stoi(lineSplit[1], nullptr, 10);
				}
				else if (strcmp(lineSplit[0], "RB") == 0)
				{
					BUTTON_RB = std::stoi(lineSplit[1], nullptr, 10);
				}
				else if (strcmp(lineSplit[0], "Start") == 0)
				{
					BUTTON_START = std::stoi(lineSplit[1], nullptr, 10);
				}
				else if (strcmp(lineSplit[0], "Controller_ID") == 0)
				{
					int raw = std::stoi(lineSplit[1], nullptr, 10);
					switch (raw)
					{
						case 0:  CONTROLLER_ID = GLFW_JOYSTICK_1;  break;
						case 1:  CONTROLLER_ID = GLFW_JOYSTICK_2;  break;
						case 2:  CONTROLLER_ID = GLFW_JOYSTICK_3;  break;
						case 3:  CONTROLLER_ID = GLFW_JOYSTICK_4;  break;
						case 4:  CONTROLLER_ID = GLFW_JOYSTICK_5;  break;
						case 5:  CONTROLLER_ID = GLFW_JOYSTICK_6;  break;
						case 6:  CONTROLLER_ID = GLFW_JOYSTICK_7;  break;
						case 7:  CONTROLLER_ID = GLFW_JOYSTICK_8;  break;
						case 8:  CONTROLLER_ID = GLFW_JOYSTICK_9;  break;
						case 9:  CONTROLLER_ID = GLFW_JOYSTICK_10; break;
						case 10: CONTROLLER_ID = GLFW_JOYSTICK_11; break;
						case 11: CONTROLLER_ID = GLFW_JOYSTICK_12; break;
						case 12: CONTROLLER_ID = GLFW_JOYSTICK_13; break;
						case 13: CONTROLLER_ID = GLFW_JOYSTICK_14; break;
						case 14: CONTROLLER_ID = GLFW_JOYSTICK_15; break;
						case 15: CONTROLLER_ID = GLFW_JOYSTICK_16; break;
						default: CONTROLLER_ID = GLFW_JOYSTICK_1;  break;
					}
				}
			}
			else if (splitLength == 4)
			{
				if (strcmp(lineSplit[0], "Stick_LX") == 0)
				{
					STICK_LX = std::stoi(lineSplit[1], nullptr, 10);
					STICK_LXDEADZONE = std::stof(lineSplit[2], nullptr);
					STICK_LX_SCALE = std::stof(lineSplit[3], nullptr);
				}
				else if (strcmp(lineSplit[0], "Stick_LY") == 0)
				{
					STICK_LY = std::stoi(lineSplit[1], nullptr, 10);
					STICK_LYDEADZONE = std::stof(lineSplit[2], nullptr);
					STICK_LY_SCALE = std::stof(lineSplit[3], nullptr);
				}
				else if (strcmp(lineSplit[0], "Stick_RX") == 0)
				{
					STICK_RX = std::stoi(lineSplit[1], nullptr, 10);
					STICK_RXDEADZONE = std::stof(lineSplit[2], nullptr);
					STICK_RX_SCALE = std::stof(lineSplit[3], nullptr);
				}
				else if (strcmp(lineSplit[0], "Stick_RY") == 0)
				{
					STICK_RY = std::stoi(lineSplit[1], nullptr, 10);
					STICK_RYDEADZONE = std::stof(lineSplit[2], nullptr);
					STICK_RY_SCALE = std::stof(lineSplit[3], nullptr);
				}
			}
			else if (splitLength == 5)
			{
				if (strcmp(lineSplit[0], "Trigger_L") == 0)
				{
					TRIGGER_L = std::stoi(lineSplit[1], nullptr, 10);
					LT_NEUTRAL = std::stof(lineSplit[2], nullptr);
					LT_MAX = std::stof(lineSplit[3], nullptr);
					TRIGGER_DEADZONE = std::stof(lineSplit[4], nullptr);
					LT_RANGE = LT_MAX - LT_NEUTRAL;
				}
				else if (strcmp(lineSplit[0], "Trigger_R") == 0)
				{
					TRIGGER_R = std::stoi(lineSplit[1], nullptr, 10);
					RT_NEUTRAL = std::stof(lineSplit[2], nullptr);
					RT_MAX = std::stof(lineSplit[3], nullptr);
					TRIGGER_DEADZONE = std::stof(lineSplit[4], nullptr);
					RT_RANGE = RT_MAX - RT_NEUTRAL;
				}
			}

			free(lineSplit);
		}
		file2.close();
	}

	glfwPollEvents();

	int present = glfwJoystickPresent(CONTROLLER_ID);
	if (present == 1)
	{
		int axesCount;
		glfwGetJoystickAxes(CONTROLLER_ID, &axesCount);
		STICK_LX  = std::min(STICK_LX,  axesCount - 1);
		STICK_LY  = std::min(STICK_LY,  axesCount - 1);
		STICK_RX  = std::min(STICK_RX,  axesCount - 1);
		STICK_RY  = std::min(STICK_RY,  axesCount - 1);
		TRIGGER_L = std::min(TRIGGER_L, axesCount - 1);
		TRIGGER_R = std::min(TRIGGER_R, axesCount - 1);

		int buttonCount;
		glfwGetJoystickButtons(CONTROLLER_ID, &buttonCount);
		BUTTON_A     = std::min(BUTTON_A,     buttonCount - 1);
		BUTTON_B     = std::min(BUTTON_B,     buttonCount - 1);
		BUTTON_X     = std::min(BUTTON_X,     buttonCount - 1);
		BUTTON_Y     = std::min(BUTTON_Y,     buttonCount - 1);
		BUTTON_LB    = std::min(BUTTON_LB,    buttonCount - 1);
		BUTTON_RB    = std::min(BUTTON_RB,    buttonCount - 1);
		BUTTON_START = std::min(BUTTON_START, buttonCount - 1);
	}
}