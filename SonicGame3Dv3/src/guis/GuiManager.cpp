#include "guimanager.h"

#include "../engineTester/main.h"
#include "../entities/player.h"
#include "../fontMeshCreator/guitext.h"
#include "../fontMeshCreator/fonttype.h"
#include "../engineTester/main.h"
#include "../toolbox/pausescreen.h"

#include <cmath>
#include <string>

GUIText* GuiManager::textTimer = nullptr;

bool GuiManager::timerIsRunning = false;
int GuiManager::centiseconds = 0;
int GuiManager::seconds = 0;
int GuiManager::minutes = 0;

GUIText* GuiManager::textRings = nullptr;

GUIText* GuiManager::textHorVel = nullptr;
GUIText* GuiManager::textVerVel = nullptr;
GUIText* GuiManager::textTotalVel = nullptr;

FontType* GuiManager::fontVip = nullptr;

float GuiManager::horVel = 0;
float GuiManager::verVel = 0;
float GuiManager::totalVel = 0;

void GuiManager::init()
{
	fontVip = PauseScreen::font;
	textTimer = new GUIText("0", 1, fontVip, 0.01f, 0.01f, 1, false, false);
	Global::countNew++;
	textRings = new GUIText("0", 1, fontVip, 0.01f, 0.01f, 1, false, false);
	Global::countNew++;

	// Player debug text
	textHorVel = new GUIText("Hor Vel:" + std::to_string(horVel), 1, fontVip, 0.01f, 0.70f, 1, false, false);
	Global::countNew++;

	textVerVel = new GUIText("Ver Vel:" + std::to_string(verVel), 1, fontVip, 0.01f, 0.75f, 1, false, false);
	Global::countNew++;

	textTotalVel = new GUIText("Total Vel:" + std::to_string(horVel), 1, fontVip, 0.01f, 0.80f, 1, false, false);
	Global::countNew++;
}

void GuiManager::refresh()
{
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

	textTimer = new GUIText(timer, 1.5f, fontVip, 0.01f, 0.01f, 1, false, true);
	Global::countNew++;

	textRings->deleteMe();
	delete textRings;
	Global::countDelete++;
	textRings = nullptr;
	textRings = new GUIText(std::to_string(Global::gameRingCount), 1.5f, fontVip, 0.01f, 0.06f, 1, false, true);
	Global::countNew++;

	// Check if player exists before trying to get values.
	if (Global::gamePlayer != nullptr)
	{
		float xVel = Global::gamePlayer->getxVel() + Global::gamePlayer->getXVelAir();
		float zVel = Global::gamePlayer->getzVel() + Global::gamePlayer->getZVelAir();

		horVel = sqrtf(xVel * xVel + zVel * zVel);

		verVel = Global::gamePlayer->getyVel();

		totalVel = sqrtf(xVel * xVel + verVel * verVel + zVel * zVel);
	}

	// Debug text following
	textHorVel->deleteMe();
	delete textHorVel;
	Global::countDelete++;
	textHorVel = nullptr;
	textHorVel = new GUIText("Hor Vel:" + std::to_string(horVel), 1.0f, fontVip, 0.01f, 0.70f, 1, false, true);
	Global::countNew++;

	textVerVel->deleteMe();
	delete textVerVel;
	Global::countDelete++;
	textVerVel = nullptr;
	textVerVel = new GUIText("Ver Vel:" + std::to_string(verVel), 1.0f, fontVip, 0.01f, 0.75f, 1, false, true);
	Global::countNew++;

	textTotalVel->deleteMe();
	delete textTotalVel;
	Global::countDelete++;
	textTotalVel = nullptr;
	textTotalVel = new GUIText("Total Vel:" + std::to_string(totalVel), 1.0f, fontVip, 0.01f, 0.80f, 1, false, true);
	Global::countNew++;
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

