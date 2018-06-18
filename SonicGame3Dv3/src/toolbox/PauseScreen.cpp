#include "pausescreen.h"
#include "../engineTester/main.h"

#include <cmath>
#include <algorithm>

#include "../fontMeshCreator/guitext.h"
#include "../fontMeshCreator/fonttype.h"
#include "../renderEngine/renderEngine.h"
#include "../toolbox/input.h"
#include "../entities/playersonic.h"
#include "../toolbox/levelloader.h"
#include "../fontMeshCreator/guitext.h"
#include "../audio/audioplayer.h"
#include "../audio/source.h"
#include "../particles/particle.h"
#include "../particles/particleresources.h"
#include "../particles/particletexture.h"
#include "../entities/camera.h"
#include "../particles/particlemaster.h"
#include "../guis/guitextureresources.h"
#include "../guis/guimanager.h"

int PauseScreen::menuSelection = 0;
int PauseScreen::menuSelectionMAX = 2;
int PauseScreen::menuDisplayID = 0;

int PauseScreen::moveYPrevious = 0;
bool PauseScreen::selectInputPrevious = false;
bool PauseScreen::backInputPrevious = false;

FontType* PauseScreen::font = nullptr;

GUIText* PauseScreen::textCursor  = nullptr;
GUIText* PauseScreen::textResume  = nullptr;
GUIText* PauseScreen::textRestart = nullptr;
GUIText* PauseScreen::textQuit    = nullptr;

bool PauseScreen::shouldPause = false;
bool PauseScreen::pausedSounds[14];

extern bool INPUT_START;
extern bool INPUT_PREVIOUS_START;

extern bool INPUT_JUMP;
extern bool INPUT_ACTION;

extern bool INPUT_PREVIOUS_JUMP;
extern bool INPUT_PREVIOUS_ACTION;

extern int MENU_X;
extern int MENU_Y;

void PauseScreen::init()
{
	font = new FontType(Loader_loadTexture("res/Fonts/vipnagorgialla.png"), "res/Fonts/vipnagorgialla.fnt"); Global::countNew++;
	textCursor = new GUIText(">", 2.5f, font, 0.47f, 0.25f, 1.0f, false, false, false); Global::countNew++;
}

void PauseScreen::step()
{
	if (shouldPause == true)
	{
		shouldPause = false;
		if (Global::gameState == STATE_PAUSED)
		{
			unpause(true);
		}
		else if (Global::gameState == STATE_RUNNING)
		{
			if (Global::finishStageTimer == -1)
			{
				pause();
			}
		}
	}

	if (INPUT_START && !INPUT_PREVIOUS_START)
	{
		shouldPause = true;
	}

	if (Global::gameState == STATE_PAUSED)
	{
		int moveY = MENU_Y;

		if (moveYPrevious != moveY)
		{
			menuSelection += moveY;
			menuSelection = std::max(0, std::min(menuSelectionMAX, menuSelection));
		}

		if (INPUT_JUMP && !INPUT_PREVIOUS_JUMP)
		{
			switch (menuDisplayID)
			{
			case ROOT:
				switch (menuSelection)
				{
				case 0:
					//unpause();
					shouldPause = true;
					break;

				case 1:
				{
					Global::shouldLoadLevel = true;
					Vector3f vel(0,0,0);
					new Particle(ParticleResources::textureBlackFade, Global::gameCamera->getFadePosition1(), &vel, 0, 60, 0.0f,  10.0f, 0, 1.0f, 0, true);
					unpause(false);
					Global::gameState = STATE_CUTSCENE;
					break;
				}

				case 2:
				{
					Vector3f vel(0,0,0);
					new Particle(ParticleResources::textureBlackFade, Global::gameCamera->getFadePosition1(), &vel, 0, 60, 0.0f,  10.0f, 0, 1.0f, 0, true);
					unpause(false);
					LevelLoader_loadTitle();
					break;
				}

				default:
					break;
				}
				break;

			default:
				break;
			}
		}

		if (INPUT_ACTION && !INPUT_PREVIOUS_ACTION)
		{
			shouldPause = true;
			//unpause();
		}

		switch (menuDisplayID)
		{
		case ROOT:
			switch (menuSelection)
			{
				case 0: textCursor->getPosition()->y = 0.4f; break;

				case 1: textCursor->getPosition()->y = 0.5f; break;

				case 2: textCursor->getPosition()->y = 0.6f; break;

				default: break;
			}
			break;

		default:
			break;
		}

		moveYPrevious = moveY;
	}
}

void PauseScreen::unpause(bool shouldResumeSFX)
{
	Global::gameState = STATE_RUNNING;

	if (textCursor != nullptr)
	{
		textCursor->setVisibility(false);
	}
	if (textResume != nullptr)
	{
		textResume->deleteMe(); delete textResume; Global::countDelete++; textResume = nullptr;
	}
	if (textRestart != nullptr)
	{
		textRestart->deleteMe(); delete textRestart; Global::countDelete++; textRestart = nullptr;
	}
	if (textQuit != nullptr)
	{
		textQuit->deleteMe(); delete textQuit; Global::countDelete++; textQuit = nullptr;
	}

	//Resume all sound effects that were paused
	if (shouldResumeSFX)
	{
		for (int i = 0; i < 14; i++)
		{
			if (PauseScreen::pausedSounds[i])
			{
				AudioPlayer::getSource(i)->continuePlaying();
			}
		}
	}
	else
	{
		AudioPlayer::stopAllSFX();
	}
}

void PauseScreen::pause()
{
	if (Global::gamePlayer != nullptr && Global::gamePlayer->isDying() == true)
	{
		return;
	}

	const float size = 2.5f;

	Global::gameState = STATE_PAUSED;
	menuSelection = 0;
	menuDisplayID = 0;
	menuSelectionMAX = 2;
	textCursor->setVisibility(true);
	textResume        = new GUIText("Resume",  size, font, 0.5f, 0.4f, 1.0f, false, false, true); Global::countNew++;
	textRestart       = new GUIText("Restart", size, font, 0.5f, 0.5f, 1.0f, false, false, true); Global::countNew++;
	textQuit          = new GUIText("Quit",    size, font, 0.5f, 0.6f, 1.0f, false, false, true); Global::countNew++;

	//Pause all sound effects
	for (int i = 0; i < 14; i++)
	{
		if (AudioPlayer::getSource(i)->isPlaying())
		{
			PauseScreen::pausedSounds[i] = true;
			AudioPlayer::getSource(i)->pause();
		}
		else
		{
			PauseScreen::pausedSounds[i] = false;
		}
	}
}
