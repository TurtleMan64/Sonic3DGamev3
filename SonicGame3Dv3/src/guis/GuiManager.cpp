//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

#include "guimanager.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../fontMeshCreator/guitext.h"
#include "../fontMeshCreator/fonttype.h"
#include "../toolbox/pausescreen.h"
#include "guirenderer.h"
#include "../toolbox/input.h"

#include <cmath>
#include <string>

float safeZone = 0.05f;

extern InputStruct Inputs;

//GUIText* GuiManager::textTimer = nullptr;

GUIText* GuiManager::timerColon  = nullptr;
GUIText* GuiManager::timerPeriod = nullptr;
GUIText* GuiManager::timerMin1[10];
GUIText* GuiManager::timerMin2[10];
GUIText* GuiManager::timerSec1[10];
GUIText* GuiManager::timerSec2[10];
GUIText* GuiManager::timerCen1[10];
GUIText* GuiManager::timerCen2[10];

bool GuiManager::timerIsRunning = false;
int GuiManager::centiseconds = 0;
int GuiManager::seconds = 0;
int GuiManager::minutes = 0;

GUIText* GuiManager::textRings = nullptr;
GUIText* GuiManager::textScore = nullptr;
GUIText* GuiManager::textLives = nullptr;

int GuiManager::previousRings = -1;
int GuiManager::previousScore = -1;
int GuiManager::previousLives = -1;

GUIText* GuiManager::textHorVel = nullptr;
GUIText* GuiManager::textVerVel = nullptr;
GUIText* GuiManager::textTotalVel = nullptr;
GUIText* GuiManager::textHoverCount = nullptr;
GUIText* GuiManager::textStoredSpindashSpeed = nullptr;

GUIText* GuiManager::textA = nullptr;
GUIText* GuiManager::textB = nullptr;
GUIText* GuiManager::textX = nullptr;
GUIText* GuiManager::textY = nullptr;

FontType* GuiManager::fontVip = nullptr;

float GuiManager::horVel = 0;
float GuiManager::verVel = 0;
float GuiManager::totalVel = 0;
int   GuiManager::hoverCount = 0;
float GuiManager::storedSpindashSpeed = 0;

std::list<GuiTexture*> GuiManager::guisToRender;

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

float fontScale = 1.5f;

void GuiManager::init()
{
	float w = 0.035f * (float) SCR_HEIGHT / (float) SCR_WIDTH;

	fontVip = PauseScreen::font;
	//textTimer = new GUIText("0", 1, fontVip, 0.01f, 0.01f, 1, false, false, false); INCR_NEW
	textRings = new GUIText("0", 1, fontVip, 0.01f, 0.01f, 1, false, false, false); INCR_NEW
	textScore = new GUIText("0", 1, fontVip, 0.01f, 0.01f, 1, false, false, false); INCR_NEW
	textLives = new GUIText("0", 1, fontVip, 0.01f, 0.98f, 1, false, false, false); INCR_NEW

	// Player debug text
	textHorVel              = new GUIText("Hor Vel:"     + std::to_string(horVel),              1, fontVip, 0.01f, 0.70f, 1, false, false, Global::debugDisplay); INCR_NEW
	textVerVel              = new GUIText("Ver Vel:"     + std::to_string(verVel),              1, fontVip, 0.01f, 0.75f, 1, false, false, Global::debugDisplay); INCR_NEW
	textTotalVel            = new GUIText("Total Vel:"   + std::to_string(horVel),              1, fontVip, 0.01f, 0.80f, 1, false, false, Global::debugDisplay); INCR_NEW
	textHoverCount          = new GUIText("Hover Count:" + std::to_string(hoverCount),          1, fontVip, 0.01f, 0.85f, 1, false, false, Global::debugDisplay); INCR_NEW
	textStoredSpindashSpeed = new GUIText("SSS:"         + std::to_string(storedSpindashSpeed), 1, fontVip, 0.01f, 0.90f, 1, false, false, Global::debugDisplay); INCR_NEW

	// Input text
	textA = new GUIText("A", 1, fontVip, 0.80f, 0.95f, 1, false, false, Global::debugDisplay); INCR_NEW
	textB = new GUIText("B", 1, fontVip, 0.85f, 0.95f, 1, false, false, Global::debugDisplay); INCR_NEW
	textX = new GUIText("X", 1, fontVip, 0.90f, 0.95f, 1, false, false, Global::debugDisplay); INCR_NEW
	textY = new GUIText("Y", 1, fontVip, 0.95f, 0.95f, 1, false, false, Global::debugDisplay); INCR_NEW

	// Create HUD for all timer values.
	GuiManager::timerColon   = new GUIText(":", fontScale, fontVip,	2*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerPeriod  = new GUIText(".", fontScale, fontVip, 5*w+ safeZone, safeZone, w, true, false, true); INCR_NEW

	GuiManager::timerMin1[0] = new GUIText("0", fontScale, fontVip, 0*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin1[1] = new GUIText("1", fontScale, fontVip, 0*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin1[2] = new GUIText("2", fontScale, fontVip, 0*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin1[3] = new GUIText("3", fontScale, fontVip, 0*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin1[4] = new GUIText("4", fontScale, fontVip, 0*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin1[5] = new GUIText("5", fontScale, fontVip, 0*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin1[6] = new GUIText("6", fontScale, fontVip, 0*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin1[7] = new GUIText("7", fontScale, fontVip, 0*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin1[8] = new GUIText("8", fontScale, fontVip, 0*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin1[9] = new GUIText("9", fontScale, fontVip, 0*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin2[0] = new GUIText("0", fontScale, fontVip, 1*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin2[1] = new GUIText("1", fontScale, fontVip, 1*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin2[2] = new GUIText("2", fontScale, fontVip, 1*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin2[3] = new GUIText("3", fontScale, fontVip, 1*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin2[4] = new GUIText("4", fontScale, fontVip, 1*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin2[5] = new GUIText("5", fontScale, fontVip, 1*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin2[6] = new GUIText("6", fontScale, fontVip, 1*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin2[7] = new GUIText("7", fontScale, fontVip, 1*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin2[8] = new GUIText("8", fontScale, fontVip, 1*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerMin2[9] = new GUIText("9", fontScale, fontVip, 1*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec1[0] = new GUIText("0", fontScale, fontVip, 3*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec1[1] = new GUIText("1", fontScale, fontVip, 3*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec1[2] = new GUIText("2", fontScale, fontVip, 3*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec1[3] = new GUIText("3", fontScale, fontVip, 3*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec1[4] = new GUIText("4", fontScale, fontVip, 3*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec1[5] = new GUIText("5", fontScale, fontVip, 3*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec1[6] = new GUIText("6", fontScale, fontVip, 3*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec1[7] = new GUIText("7", fontScale, fontVip, 3*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec1[8] = new GUIText("8", fontScale, fontVip, 3*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec1[9] = new GUIText("9", fontScale, fontVip, 3*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec2[0] = new GUIText("0", fontScale, fontVip, 4*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec2[1] = new GUIText("1", fontScale, fontVip, 4*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec2[2] = new GUIText("2", fontScale, fontVip, 4*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec2[3] = new GUIText("3", fontScale, fontVip, 4*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec2[4] = new GUIText("4", fontScale, fontVip, 4*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec2[5] = new GUIText("5", fontScale, fontVip, 4*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec2[6] = new GUIText("6", fontScale, fontVip, 4*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec2[7] = new GUIText("7", fontScale, fontVip, 4*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec2[8] = new GUIText("8", fontScale, fontVip, 4*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerSec2[9] = new GUIText("9", fontScale, fontVip, 4*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen1[0] = new GUIText("0", fontScale, fontVip, 6*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen1[1] = new GUIText("1", fontScale, fontVip, 6*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen1[2] = new GUIText("2", fontScale, fontVip, 6*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen1[3] = new GUIText("3", fontScale, fontVip, 6*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen1[4] = new GUIText("4", fontScale, fontVip, 6*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen1[5] = new GUIText("5", fontScale, fontVip, 6*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen1[6] = new GUIText("6", fontScale, fontVip, 6*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen1[7] = new GUIText("7", fontScale, fontVip, 6*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen1[8] = new GUIText("8", fontScale, fontVip, 6*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen1[9] = new GUIText("9", fontScale, fontVip, 6*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen2[0] = new GUIText("0", fontScale, fontVip, 7*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen2[1] = new GUIText("1", fontScale, fontVip, 7*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen2[2] = new GUIText("2", fontScale, fontVip, 7*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen2[3] = new GUIText("3", fontScale, fontVip, 7*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen2[4] = new GUIText("4", fontScale, fontVip, 7*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen2[5] = new GUIText("5", fontScale, fontVip, 7*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen2[6] = new GUIText("6", fontScale, fontVip, 7*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen2[7] = new GUIText("7", fontScale, fontVip, 7*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen2[8] = new GUIText("8", fontScale, fontVip, 7*w+ safeZone, safeZone, w, true, false, true); INCR_NEW
	GuiManager::timerCen2[9] = new GUIText("9", fontScale, fontVip, 7*w+ safeZone, safeZone, w, true, false, true); INCR_NEW

	GuiManager::setTimerInvisible();

	GuiRenderer::init();
}

void GuiManager::refresh()
{
	float w = 0.035f * (float) SCR_HEIGHT / (float) SCR_WIDTH;

	//double start = glfwGetTime();


	//textTimer->deleteMe();
	//delete textTimer; INCR_DEL
	//textTimer = nullptr;
	//
	//std::string partMin = std::to_string(minutes);
	//if (minutes < 10)
	//{
	//	partMin = "0" + std::to_string(minutes);
	//}
	//std::string partSec = std::to_string(seconds);
	//if (seconds < 10)
	//{
	//	partSec = "0" + std::to_string(seconds);
	//}
	//std::string partCen = std::to_string(((centiseconds * 100) / 60));
	//if ((centiseconds * 100) / 60 < 10)
	//{
	//	partCen = "0" + std::to_string(((centiseconds * 100) / 60));
	//}
	//std::string timer = partMin + ":" + partSec + "." + partCen;
	//
	//textTimer = new GUIText(timer, 1.5f, fontVip, 0+16*px, 0+16*py, 1, false, false, true); INCR_NEW

	if (Global::gameRingCount != GuiManager::previousRings)
	{
		textRings->deleteMe();
		delete textRings; INCR_DEL
		textRings = new GUIText(std::to_string(Global::gameRingCount), fontScale, fontVip, safeZone + 2.0f * w, safeZone + 0.12f, 1, false, false, true); INCR_NEW
		GuiManager::previousRings = Global::gameRingCount;
	}

	if (Global::gameScore != GuiManager::previousScore)
	{
		textScore->deleteMe();
		delete textScore; INCR_DEL
		textScore = new GUIText(std::to_string(Global::gameScore), fontScale, fontVip, safeZone, 0.04f + safeZone, 1, false, false, true); INCR_NEW
		GuiManager::previousScore = Global::gameScore;
	}

	if (Global::gameLives != GuiManager::previousLives)
	{
		textLives->deleteMe();
		delete textLives; INCR_DEL
		textLives = new GUIText(std::to_string(Global::gameLives), fontScale, fontVip, safeZone, 1.0f- safeZone -0.04f, 1, false, false, true); INCR_NEW
		GuiManager::previousLives = Global::gameLives;
	}

	if (Global::debugDisplay)
	{
		//Check if player exists before trying to get values.
		if (Global::gamePlayer != nullptr)
		{
			float xVel = Global::gamePlayer->getxVel() + Global::gamePlayer->getXVelAir();
			float zVel = Global::gamePlayer->getzVel() + Global::gamePlayer->getZVelAir();

			horVel = sqrtf(xVel * xVel + zVel * zVel);

			verVel = Global::gamePlayer->getyVel();

			totalVel = sqrtf(xVel * xVel + verVel * verVel + zVel * zVel);

			hoverCount = Global::gamePlayer->getHoverCount();

			storedSpindashSpeed = Global::gamePlayer->getSpindashSpeed();
		}

		//Display debug text is debugDisplay is true.
		textHorVel->deleteMe();
		delete textHorVel;
		INCR_DEL
		textHorVel = nullptr;
		textHorVel = new GUIText("Hor Vel:" + std::to_string(horVel), 1.0f, fontVip, safeZone, 0.6f, 1, false, false, Global::debugDisplay);
		INCR_NEW

		textVerVel->deleteMe();
		delete textVerVel;
		INCR_DEL
		textVerVel = nullptr;
		textVerVel = new GUIText("Ver Vel:" + std::to_string(verVel), 1.0f, fontVip, safeZone, 0.64f, 1, false, false, Global::debugDisplay);
		INCR_NEW

		textTotalVel->deleteMe();
		delete textTotalVel;
		INCR_DEL
		textTotalVel = nullptr;
		textTotalVel = new GUIText("Total Vel:" + std::to_string(totalVel), 1.0f, fontVip, safeZone, 0.68f, 1, false, false, Global::debugDisplay);
		INCR_NEW

		textHoverCount->deleteMe();
		delete textHoverCount;
		INCR_DEL
		textHoverCount = nullptr;
		textHoverCount = new GUIText("Hover Count:" + std::to_string(hoverCount), 1.0f, fontVip, safeZone, 0.72f, 1, false, false, Global::debugDisplay);
		INCR_NEW

		textStoredSpindashSpeed->deleteMe();
		delete textStoredSpindashSpeed;
		INCR_DEL
		textStoredSpindashSpeed = nullptr;
		textStoredSpindashSpeed = new GUIText("SSS:" + std::to_string(storedSpindashSpeed), 1.0f, fontVip, safeZone, 0.76f, 1, false, false, Global::debugDisplay);
		INCR_NEW

		//Input display
		textA->deleteMe();
		delete textA;
		INCR_DEL
		textA = nullptr;
		textA = new GUIText("A", 1, fontVip, 0.80f, 0.95f, 1, false, false, Global::debugDisplay);
		INCR_NEW
		if (!Inputs.INPUT_JUMP)
		{
			textA->setColour(0.2f, 0.2f, 0.2f);
		}

		textB->deleteMe();
		delete textB;
		INCR_DEL
		textB = nullptr;
		textB = new GUIText("B", 1, fontVip, 0.85f, 0.95f, 1, false, false, Global::debugDisplay);
		INCR_NEW
		if (!Inputs.INPUT_ACTION)
		{
			textB->setColour(0.2f, 0.2f, 0.2f);
		}

		textX->deleteMe();
		delete textX;
		INCR_DEL
		textX = nullptr;
		textX = new GUIText("X", 1, fontVip, 0.90f, 0.95f, 1, false, false, Global::debugDisplay);
		INCR_NEW
		if (!Inputs.INPUT_ACTION2)
		{
			textX->setColour(0.2f, 0.2f, 0.2f);
		}

		textY->deleteMe();
		delete textY;
		INCR_DEL
		textY = nullptr;
		textY = new GUIText("Y", 1, fontVip, 0.95f, 0.95f, 1, false, false, Global::debugDisplay);
		INCR_NEW
		if (!Inputs.INPUT_SPECIAL)
		{
			textY->setColour(0.2f, 0.2f, 0.2f);
		}
	}
	else
	{
		textHorVel->setVisibility(false);
		textVerVel->setVisibility(false);
		textTotalVel->setVisibility(false);
		textHoverCount->setVisibility(false);
		textStoredSpindashSpeed->setVisibility(false);

		textA->setVisibility(false);
		textB->setVisibility(false);
		textX->setVisibility(false);
		textY->setVisibility(false);
	}

	if (Global::gameState != STATE_TITLE)
	{
		//textTimer->setVisibility(true);
		textRings->setVisibility(true);
		textScore->setVisibility(true);
		textLives->setVisibility(false);

		if (Global::gameIsArcadeMode)
		{
			textLives->setVisibility(true);
		}

		GuiManager::setTimerInvisible();
		int partCen = (centiseconds * 100) / 60;
		timerColon ->setVisibility(true);
		timerPeriod->setVisibility(true);
		timerMin1[minutes/10]->setVisibility(true);
		timerMin2[minutes%10]->setVisibility(true);
		timerSec1[seconds/10]->setVisibility(true);
		timerSec2[seconds%10]->setVisibility(true);
		timerCen1[partCen/10]->setVisibility(true);
		timerCen2[partCen%10]->setVisibility(true);
	}
	else
	{
		//textTimer->setVisibility(false);
		textRings->setVisibility(false);
		textScore->setVisibility(false);
		textLives->setVisibility(false);

		GuiManager::setTimerInvisible();
	}

	//double end = glfwGetTime();
	//std::fprintf(stdout, "time diff = %.12f\n", end-start);

	//Render images
	GuiRenderer::render(&GuiManager::guisToRender);
}

void GuiManager::setTimerInvisible()
{
	GuiManager::timerColon  ->setVisibility(false);
	GuiManager::timerPeriod ->setVisibility(false);
	GuiManager::timerMin1[0]->setVisibility(false);
	GuiManager::timerMin1[1]->setVisibility(false);
	GuiManager::timerMin1[2]->setVisibility(false);
	GuiManager::timerMin1[3]->setVisibility(false);
	GuiManager::timerMin1[4]->setVisibility(false);
	GuiManager::timerMin1[5]->setVisibility(false);
	GuiManager::timerMin1[6]->setVisibility(false);
	GuiManager::timerMin1[7]->setVisibility(false);
	GuiManager::timerMin1[8]->setVisibility(false);
	GuiManager::timerMin1[9]->setVisibility(false);
	GuiManager::timerMin2[0]->setVisibility(false);
	GuiManager::timerMin2[1]->setVisibility(false);
	GuiManager::timerMin2[2]->setVisibility(false);
	GuiManager::timerMin2[3]->setVisibility(false);
	GuiManager::timerMin2[4]->setVisibility(false);
	GuiManager::timerMin2[5]->setVisibility(false);
	GuiManager::timerMin2[6]->setVisibility(false);
	GuiManager::timerMin2[7]->setVisibility(false);
	GuiManager::timerMin2[8]->setVisibility(false);
	GuiManager::timerMin2[9]->setVisibility(false);
	GuiManager::timerSec1[0]->setVisibility(false);
	GuiManager::timerSec1[1]->setVisibility(false);
	GuiManager::timerSec1[2]->setVisibility(false);
	GuiManager::timerSec1[3]->setVisibility(false);
	GuiManager::timerSec1[4]->setVisibility(false);
	GuiManager::timerSec1[5]->setVisibility(false);
	GuiManager::timerSec1[6]->setVisibility(false);
	GuiManager::timerSec1[7]->setVisibility(false);
	GuiManager::timerSec1[8]->setVisibility(false);
	GuiManager::timerSec1[9]->setVisibility(false);
	GuiManager::timerSec2[0]->setVisibility(false);
	GuiManager::timerSec2[1]->setVisibility(false);
	GuiManager::timerSec2[2]->setVisibility(false);
	GuiManager::timerSec2[3]->setVisibility(false);
	GuiManager::timerSec2[4]->setVisibility(false);
	GuiManager::timerSec2[5]->setVisibility(false);
	GuiManager::timerSec2[6]->setVisibility(false);
	GuiManager::timerSec2[7]->setVisibility(false);
	GuiManager::timerSec2[8]->setVisibility(false);
	GuiManager::timerSec2[9]->setVisibility(false);
	GuiManager::timerCen1[0]->setVisibility(false);
	GuiManager::timerCen1[1]->setVisibility(false);
	GuiManager::timerCen1[2]->setVisibility(false);
	GuiManager::timerCen1[3]->setVisibility(false);
	GuiManager::timerCen1[4]->setVisibility(false);
	GuiManager::timerCen1[5]->setVisibility(false);
	GuiManager::timerCen1[6]->setVisibility(false);
	GuiManager::timerCen1[7]->setVisibility(false);
	GuiManager::timerCen1[8]->setVisibility(false);
	GuiManager::timerCen1[9]->setVisibility(false);
	GuiManager::timerCen2[0]->setVisibility(false);
	GuiManager::timerCen2[1]->setVisibility(false);
	GuiManager::timerCen2[2]->setVisibility(false);
	GuiManager::timerCen2[3]->setVisibility(false);
	GuiManager::timerCen2[4]->setVisibility(false);
	GuiManager::timerCen2[5]->setVisibility(false);
	GuiManager::timerCen2[6]->setVisibility(false);
	GuiManager::timerCen2[7]->setVisibility(false);
	GuiManager::timerCen2[8]->setVisibility(false);
	GuiManager::timerCen2[9]->setVisibility(false);
}

void GuiManager::increaseTimer()
{
	if (timerIsRunning)
	{
		centiseconds++;
		if (centiseconds >= 60)
		{
			centiseconds = 0;
			seconds++;
			if (seconds >= 60)
			{
				seconds = 0;
				minutes++;
				if (minutes >= 99)
				{
					minutes = 99;
				}
			}
		}
	}
}

void GuiManager::setTimer(int newMinutes, int newSeconds, int newCentiseconds)
{
	GuiManager::minutes = newMinutes;
	GuiManager::seconds = newSeconds;
	GuiManager::centiseconds = newCentiseconds;
}

void GuiManager::startTimer()
{
	timerIsRunning = true;
}

void GuiManager::stopTimer()
{
	timerIsRunning = false;
}

int GuiManager::getMinutes()
{
	return minutes;
}

int GuiManager::getSeconds()
{
	return seconds;
}

int GuiManager::getCentiseconds()
{
	return centiseconds;
}

float GuiManager::getTotalTimerInSeconds()
{
	return minutes * 60 + seconds + centiseconds / 60.0f;
}

int GuiManager::getTotalTimerInFrames()
{
	return minutes * 3600 + seconds*60 + centiseconds;
}

void GuiManager::addGuiToRender(GuiTexture* newImage)
{
	GuiManager::guisToRender.push_back(newImage);
}

void GuiManager::removeGui(GuiTexture* imageToRemove)
{
	GuiManager::guisToRender.remove(imageToRemove);
}

void GuiManager::clearGuisToRender()
{
	GuiManager::guisToRender.clear();
}