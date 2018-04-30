#include "guimanager.h"

#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../fontMeshCreator/guitext.h"
#include "../fontMeshCreator/fonttype.h"
#include "../toolbox/pausescreen.h"
#include "guirenderer.h"

#include <cmath>
#include <string>

extern bool INPUT_JUMP;
extern bool INPUT_ACTION;
extern bool INPUT_ACTION2;
extern bool INPUT_SPECIAL;

GUIText* GuiManager::textTimer = nullptr;

bool GuiManager::timerIsRunning = false;
int GuiManager::centiseconds = 0;
int GuiManager::seconds = 0;
int GuiManager::minutes = 0;

GUIText* GuiManager::textRings = nullptr;

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

void GuiManager::init()
{
	fontVip = PauseScreen::font;
	textTimer = new GUIText("0", 1, fontVip, 0.01f, 0.01f, 1, false, false);
	Global::countNew++;
	textRings = new GUIText("0", 1, fontVip, 0.01f, 0.01f, 1, false, false);
	Global::countNew++;

	//Player debug text
	textHorVel = new GUIText("Hor Vel:" + std::to_string(horVel), 1, fontVip, 0.01f, 0.70f, 1, false, Global::debugDisplay);
	Global::countNew++;
	textVerVel = new GUIText("Ver Vel:" + std::to_string(verVel), 1, fontVip, 0.01f, 0.75f, 1, false, Global::debugDisplay);
	Global::countNew++;
	textTotalVel = new GUIText("Total Vel:" + std::to_string(horVel), 1, fontVip, 0.01f, 0.80f, 1, false, Global::debugDisplay);
	Global::countNew++;
	textHoverCount = new GUIText("Hover Count:" + std::to_string(hoverCount), 1, fontVip, 0.01f, 0.85f, 1, false, Global::debugDisplay);
	Global::countNew++;
	textStoredSpindashSpeed = new GUIText("SSS:" + std::to_string(storedSpindashSpeed), 1, fontVip, 0.01f, 0.90f, 1, false, Global::debugDisplay);
	Global::countNew++;

	//Input text
	textA = new GUIText("A", 1, fontVip, 0.80f, 0.95f, 1, false, Global::debugDisplay);
	Global::countNew++;
	textB = new GUIText("B", 1, fontVip, 0.85f, 0.95f, 1, false, Global::debugDisplay);
	Global::countNew++;
	textX = new GUIText("X", 1, fontVip, 0.90f, 0.95f, 1, false, Global::debugDisplay);
	Global::countNew++;
	textY = new GUIText("Y", 1, fontVip, 0.95f, 0.95f, 1, false, Global::debugDisplay);
	Global::countNew++;

	GuiRenderer::init();
}

void GuiManager::refresh()
{
	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;

	float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension
	float py = 1.0f/(SCR_HEIGHT); //1 pixel in y dimension


	textTimer->deleteMe();
	delete textTimer;
	Global::countDelete++;
	textTimer = nullptr;

	std::string partMin = std::to_string(minutes);
	if (minutes < 10)
	{
		partMin = "0" + std::to_string(minutes);
	}
	std::string partSec = std::to_string(seconds);
	if (seconds < 10)
	{
		partSec = "0" + std::to_string(seconds);
	}
	std::string partCen = std::to_string(((centiseconds * 100) / 60));
	if ((centiseconds * 100) / 60 < 10)
	{
		partCen = "0" + std::to_string(((centiseconds * 100) / 60));
	}
	std::string timer = partMin + ":" + partSec + "." + partCen;

	textTimer = new GUIText(timer, 1.5f, fontVip, 0+16*px, 0+16*py, 1, false, true);
	Global::countNew++;

	textRings->deleteMe();
	delete textRings;
	Global::countDelete++;
	textRings = nullptr;
	textRings = new GUIText(std::to_string(Global::gameRingCount), 1.5f, fontVip, 0+48*px, 0+48*py, 1, false, true);
	Global::countNew++;

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
		Global::countDelete++;
		textHorVel = nullptr;
		textHorVel = new GUIText("Hor Vel:" + std::to_string(horVel), 1.0f, fontVip, 0.01f, 0.70f, 1, false, Global::debugDisplay);
		Global::countNew++;

		textVerVel->deleteMe();
		delete textVerVel;
		Global::countDelete++;
		textVerVel = nullptr;
		textVerVel = new GUIText("Ver Vel:" + std::to_string(verVel), 1.0f, fontVip, 0.01f, 0.75f, 1, false, Global::debugDisplay);
		Global::countNew++;

		textTotalVel->deleteMe();
		delete textTotalVel;
		Global::countDelete++;
		textTotalVel = nullptr;
		textTotalVel = new GUIText("Total Vel:" + std::to_string(totalVel), 1.0f, fontVip, 0.01f, 0.80f, 1, false, Global::debugDisplay);
		Global::countNew++;

		textHoverCount->deleteMe();
		delete textHoverCount;
		Global::countDelete++;
		textHoverCount = nullptr;
		textHoverCount = new GUIText("Hover Count:" + std::to_string(hoverCount), 1.0f, fontVip, 0.01f, 0.85f, 1, false, Global::debugDisplay);
		Global::countNew++;

		textStoredSpindashSpeed->deleteMe();
		delete textStoredSpindashSpeed;
		Global::countDelete++;
		textStoredSpindashSpeed = nullptr;
		textStoredSpindashSpeed = new GUIText("SSS:" + std::to_string(storedSpindashSpeed), 1.0f, fontVip, 0.01f, 0.90f, 1, false, Global::debugDisplay);
		Global::countNew++;

		//Input display
		textA->deleteMe();
		delete textA;
		Global::countDelete++;
		textA = nullptr;
		textA = new GUIText("A", 1, fontVip, 0.80f, 0.95f, 1, false, Global::debugDisplay);
		Global::countNew++;
		if (!INPUT_JUMP)
		{
			textA->setColour(0.2f, 0.2f, 0.2f);
		}

		textB->deleteMe();
		delete textB;
		Global::countDelete++;
		textB = nullptr;
		textB = new GUIText("B", 1, fontVip, 0.85f, 0.95f, 1, false, Global::debugDisplay);
		Global::countNew++;
		if (!INPUT_ACTION)
		{
			textB->setColour(0.2f, 0.2f, 0.2f);
		}

		textX->deleteMe();
		delete textX;
		Global::countDelete++;
		textX = nullptr;
		textX = new GUIText("X", 1, fontVip, 0.90f, 0.95f, 1, false, Global::debugDisplay);
		Global::countNew++;
		if (!INPUT_ACTION2)
		{
			textX->setColour(0.2f, 0.2f, 0.2f);
		}

		textY->deleteMe();
		delete textY;
		Global::countDelete++;
		textY = nullptr;
		textY = new GUIText("Y", 1, fontVip, 0.95f, 0.95f, 1, false, Global::debugDisplay);
		Global::countNew++;
		if (!INPUT_SPECIAL)
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

	//Render images
	GuiRenderer::render(&GuiManager::guisToRender);
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

float GuiManager::getTotalTimer()
{
	return minutes * 60 + seconds + centiseconds / 60.0f;
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