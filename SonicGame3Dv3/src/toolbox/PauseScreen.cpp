#include "pausescreen.h"

#include <cmath>
#include <algorithm>

#include "../fontMeshCreator/guitext.h"
#include "../fontMeshCreator/fonttype.h"
#include "../renderEngine/renderEngine.h"
#include "../engineTester/main.h"
#include "../toolbox/input.h"
#include "../entities/player.h"
#include "../toolbox/levelloader.h"
#include "../fontMeshCreator/guitext.h"

int PauseScreen::menuSelection = 0;
int PauseScreen::menuSelectionMAX = 4;
int PauseScreen::menuDisplayID = 0;

int PauseScreen::moveYPrevious = 0;
bool PauseScreen::selectInputPrevious = false;
bool PauseScreen::backInputPrevious = false;

FontType* PauseScreen::font = nullptr;

GUIText* PauseScreen::textCursor = nullptr;
GUIText* PauseScreen::textResume = nullptr;
GUIText* PauseScreen::textRestart = nullptr;
GUIText* PauseScreen::textLevelSelect = nullptr;
GUIText* PauseScreen::textCharSelect = nullptr;
GUIText* PauseScreen::textQuit = nullptr;

GUIText* PauseScreen::textEmeraldCoast = nullptr;
GUIText* PauseScreen::textGreenHillZone = nullptr;
GUIText* PauseScreen::textSpeedHighway = nullptr;
GUIText* PauseScreen::textWuhuIsland = nullptr;
GUIText* PauseScreen::textPeachCastle = nullptr;
GUIText* PauseScreen::textSandHill = nullptr;
GUIText* PauseScreen::textKoopaBeach = nullptr;
GUIText* PauseScreen::textOutsetIsland = nullptr;
GUIText* PauseScreen::textWeaponsBed = nullptr;
GUIText* PauseScreen::textMetalHarbor = nullptr;
GUIText* PauseScreen::textBOB = nullptr;
GUIText* PauseScreen::textRainbowRoad = nullptr;
GUIText* PauseScreen::textSnowhead = nullptr;

GUIText* PauseScreen::textClassicSonic = nullptr;
GUIText* PauseScreen::textDollSonic = nullptr;
GUIText* PauseScreen::textMechaSonic = nullptr;
GUIText* PauseScreen::textDage4Aquatic = nullptr;
GUIText* PauseScreen::textManiaSonic = nullptr;

bool PauseScreen::shouldPause = nullptr;

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
	font = new FontType(Loader_loadTexture("res/Fonts/vipnagorgialla.png"), "res/Fonts/vipnagorgialla.fnt");
	textCursor = new GUIText(">", 3, font, 0.47f, 0.25f, 1.0f, false, false);
}

void PauseScreen::step()
{
	if (shouldPause == true)
	{
		shouldPause = false;
		if (Global::gameState == STATE_PAUSED)
		{
			unpause();
		}
		else if (Global::gameState == STATE_RUNNING)
		{
			pause();
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

		switch (Player::characterID)
		{
		case 0:
			textClassicSonic->setColour(1, 1, 1);
			textDollSonic->setColour(0.6f, 0.6f, 0.6f);
			textMechaSonic->setColour(0.6f, 0.6f, 0.6f);
			textDage4Aquatic->setColour(0.6f, 0.6f, 0.6f);
			textManiaSonic->setColour(0.6f, 0.6f, 0.6f);
			break;

		case 1:
			textClassicSonic->setColour(0.6f, 0.6f, 0.6f);
			textDollSonic->setColour(1, 1, 1);
			textMechaSonic->setColour(0.6f, 0.6f, 0.6f);
			textDage4Aquatic->setColour(0.6f, 0.6f, 0.6f);
			textManiaSonic->setColour(0.6f, 0.6f, 0.6f);
			break;

		case 2:
			textClassicSonic->setColour(0.6f, 0.6f, 0.6f);
			textDollSonic->setColour(0.6f, 0.6f, 0.6f);
			textMechaSonic->setColour(1, 1, 1);
			textDage4Aquatic->setColour(0.6f, 0.6f, 0.6f);
			textManiaSonic->setColour(0.6f, 0.6f, 0.6f);
			break;

		case 3:
			textClassicSonic->setColour(0.6f, 0.6f, 0.6f);
			textDollSonic->setColour(0.6f, 0.6f, 0.6f);
			textMechaSonic->setColour(0.6f, 0.6f, 0.6f);
			textDage4Aquatic->setColour(1, 1, 1);
			textManiaSonic->setColour(0.6f, 0.6f, 0.6f);
			break;

		case 4:
			textClassicSonic->setColour(0.6f, 0.6f, 0.6f);
			textDollSonic->setColour(0.6f, 0.6f, 0.6f);
			textMechaSonic->setColour(0.6f, 0.6f, 0.6f);
			textDage4Aquatic->setColour(0.6f, 0.6f, 0.6f);
			textManiaSonic->setColour(1, 1, 1);
			break;
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
					LevelLoader_loadLevel(Global::levelName);
					unpause();
					break;

				case 2:
					menuDisplayID = LEVEL_SELECT;
					menuSelectionMAX = 12;
					menuSelection = 0;
					textResume->setVisibility(false);
					textRestart->setVisibility(false);
					textQuit->setVisibility(false);
					textLevelSelect->setVisibility(false);
					textCharSelect->setVisibility(false);

					textEmeraldCoast->setVisibility(true);
					textGreenHillZone->setVisibility(true);
					textSpeedHighway->setVisibility(true);
					textWuhuIsland->setVisibility(true);
					textPeachCastle->setVisibility(true);
					textSandHill->setVisibility(true);
					textKoopaBeach->setVisibility(true);
					textOutsetIsland->setVisibility(true);
					textWeaponsBed->setVisibility(true);
					textMetalHarbor->setVisibility(true);
					textBOB->setVisibility(true);
					textRainbowRoad->setVisibility(true);
					textSnowhead->setVisibility(true);

					textClassicSonic->setVisibility(false);
					textDollSonic->setVisibility(false);
					textMechaSonic->setVisibility(false);
					textDage4Aquatic->setVisibility(false);
					textManiaSonic->setVisibility(false);
					break;

				case 3:
					menuDisplayID = CHAR_SELECT;
					menuSelectionMAX = 4;
					menuSelection = 0;
					textResume->setVisibility(false);
					textRestart->setVisibility(false);
					textQuit->setVisibility(false);
					textLevelSelect->setVisibility(false);
					textCharSelect->setVisibility(false);

					textEmeraldCoast->setVisibility(false);
					textGreenHillZone->setVisibility(false);
					textSpeedHighway->setVisibility(false);
					textWuhuIsland->setVisibility(false);
					textPeachCastle->setVisibility(false);
					textSandHill->setVisibility(false);
					textKoopaBeach->setVisibility(false);
					textOutsetIsland->setVisibility(false);
					textWeaponsBed->setVisibility(false);
					textMetalHarbor->setVisibility(false);
					textBOB->setVisibility(false);
					textRainbowRoad->setVisibility(false);
					textSnowhead->setVisibility(false);

					textClassicSonic->setVisibility(true);
					textDollSonic->setVisibility(true);
					textMechaSonic->setVisibility(true);
					textDage4Aquatic->setVisibility(true);
					textManiaSonic->setVisibility(true);
					break;

				case 4:
					Global::gameState = STATE_EXITING;
					break;

				default:
					break;
				}
				break;

			case LEVEL_SELECT:
				switch (menuSelection)
				{
				case 0:
					Global::levelID = LVL_EC;
					LevelLoader_loadLevel("EmeraldCoast.lvl");
					unpause();
					break;

				case 1:
					Global::levelID = LVL_SH;
					LevelLoader_loadLevel("SpeedHighway.lvl");
					unpause();
					break;

				case 2:
					Global::levelID = LVL_GHZ;
					LevelLoader_loadLevel("GreenHillZone.lvl");
					unpause();
					break;

				case 3:
					Global::levelID = LVL_WI;
					LevelLoader_loadLevel("WuhuIsland.lvl");
					unpause();
					break;

				case 4:
					Global::levelID = LVL_PC;
					LevelLoader_loadLevel("PeachCastle.lvl");
					unpause();
					break;

				case 5:
					Global::levelID = LVL_SHL;
					LevelLoader_loadLevel("SandHill.lvl");
					unpause();
					break;

				case 6:
					Global::levelID = LVL_KB;
					LevelLoader_loadLevel("KoopaTroopaBeach.lvl");
					unpause();
					break;

				case 7:
					Global::levelID = LVL_OI;
					LevelLoader_loadLevel("OutsetIsland.lvl");
					unpause();
					break;

				case 8:
					Global::levelID = LVL_WB;
					LevelLoader_loadLevel("WeaponsBed.lvl");
					unpause();
					break;

				case 9:
					Global::levelID = LVL_MH;
					LevelLoader_loadLevel("MetalHarbor.lvl");
					unpause();
					break;

				case 10:
					Global::levelID = LVL_BOB;
					LevelLoader_loadLevel("BobOmbBattlefield.lvl");
					unpause();
					break;

				case 11:
					Global::levelID = LVL_RR;
					LevelLoader_loadLevel("RainbowRoad.lvl");
					unpause();
					break;

				case 12:
					Global::levelID = LVL_SHD;
					LevelLoader_loadLevel("Snowhead.lvl");
					unpause();
					break;

				}
				break;

			case CHAR_SELECT:
				switch (menuSelection)
				{
				case 0:
					Player::characterID = 0;
					break;

				case 1:
					if (Global::unlockedSonicDoll)
					{
						Player::characterID = 1;
					}
					break;

				case 2:
					if (Global::unlockedMechaSonic)
					{
						Player::characterID = 2;
					}
					break;

				case 3:
					if (Global::unlockedDage4)
					{
						Player::characterID = 3;
					}
					break;

				case 4:
					if (Global::unlockedManiaSonic)
					{
						Player::characterID = 4;
					}
					break;
				}
				break;

			default:
				break;
			}
		}

		if (INPUT_ACTION && !INPUT_PREVIOUS_ACTION)
		{
			if (menuDisplayID == ROOT)
			{
				shouldPause = true;
				//unpause();
			}
			else if (menuDisplayID != ROOT)
			{
				menuDisplayID = ROOT;
				menuSelection = 0;
				menuSelectionMAX = 4;
				textResume->setVisibility(true);
				textRestart->setVisibility(true);
				textQuit->setVisibility(true);
				textLevelSelect->setVisibility(true);
				textCharSelect->setVisibility(true);

				textEmeraldCoast->setVisibility(false);
				textGreenHillZone->setVisibility(false);
				textSpeedHighway->setVisibility(false);
				textWuhuIsland->setVisibility(false);
				textPeachCastle->setVisibility(false);
				textSandHill->setVisibility(false);
				textKoopaBeach->setVisibility(false);
				textOutsetIsland->setVisibility(false);
				textWeaponsBed->setVisibility(false);
				textMetalHarbor->setVisibility(false);
				textBOB->setVisibility(false);
				textRainbowRoad->setVisibility(false);
				textSnowhead->setVisibility(false);

				textClassicSonic->setVisibility(false);
				textDollSonic->setVisibility(false);
				textMechaSonic->setVisibility(false);
				textDage4Aquatic->setVisibility(false);
				textManiaSonic->setVisibility(false);
			}
		}

		switch (menuDisplayID)
		{
		case ROOT:
			switch (menuSelection)
			{
				case 0: textCursor->getPosition()->y = 0.3f; break;

				case 1: textCursor->getPosition()->y = 0.4f; break;

				case 2: textCursor->getPosition()->y = 0.5f; break;

				case 3: textCursor->getPosition()->y = 0.6f; break;

				case 4: textCursor->getPosition()->y = 0.7f; break;

				default: break;
			}
			break;

		case LEVEL_SELECT:
		{
			float spacing = 1 / 13.0f;
			switch (menuSelection)
			{
				case 0: textCursor->getPosition()->y = 0.0f; break;

				case 1: textCursor->getPosition()->y = spacing; break;

				case 2: textCursor->getPosition()->y = spacing * 2; break;

				case 3: textCursor->getPosition()->y = spacing * 3; break;

				case 4: textCursor->getPosition()->y = spacing * 4; break;

				case 5: textCursor->getPosition()->y = spacing * 5; break;

				case 6: textCursor->getPosition()->y = spacing * 6; break;

				case 7: textCursor->getPosition()->y = spacing * 7; break;

				case 8: textCursor->getPosition()->y = spacing * 8; break;

				case 9: textCursor->getPosition()->y = spacing * 9; break;

				case 10: textCursor->getPosition()->y = spacing * 10; break;

				case 11: textCursor->getPosition()->y = spacing * 11; break;

				case 12: textCursor->getPosition()->y = spacing * 12; break;

				default: break;
			}
			break;
		}
		case CHAR_SELECT:
			switch (menuSelection)
			{
				case 0: textCursor->getPosition()->y = 0.3f; break;

				case 1: textCursor->getPosition()->y = 0.4f; break;

				case 2: textCursor->getPosition()->y = 0.5f; break;

				case 3: textCursor->getPosition()->y = 0.6f; break;

				case 4: textCursor->getPosition()->y = 0.7f; break;

				default: break;
			}
			break;

		default:
			break;
		}

		moveYPrevious = moveY;
	}
}

void PauseScreen::unpause()
{
	Global::gameState = STATE_RUNNING;

	if (textCursor != nullptr)
	{
		textCursor->setVisibility(false);
	}
	if (textResume != nullptr)
	{
		textResume->deleteMe();
		delete textResume;
		textResume = nullptr;
	}
	if (textRestart != nullptr)
	{
		textRestart->deleteMe();
		delete textRestart;
		textRestart = nullptr;
	}
	if (textQuit != nullptr)
	{
		textQuit->deleteMe();
		delete textQuit;
		textQuit = nullptr;
	}
	if (textLevelSelect != nullptr)
	{
		textLevelSelect->deleteMe();
		delete textLevelSelect;
		textLevelSelect = nullptr;
	}
	if (textCharSelect != nullptr)
	{
		textCharSelect->deleteMe();
		delete textCharSelect;
		textCharSelect = nullptr;
	}

	if (textEmeraldCoast != nullptr)
	{
		textEmeraldCoast->deleteMe();
		delete textEmeraldCoast;
		textEmeraldCoast = nullptr;
	}
	if (textGreenHillZone != nullptr)
	{
		textGreenHillZone->deleteMe();
		delete textGreenHillZone;
		textGreenHillZone = nullptr;
	}
	if (textSpeedHighway != nullptr)
	{
		textSpeedHighway->deleteMe();
		delete textSpeedHighway;
		textSpeedHighway = nullptr;
	}
	if (textWuhuIsland != nullptr)
	{
		textWuhuIsland->deleteMe();
		delete textWuhuIsland;
		textWuhuIsland = nullptr;
	}
	if (textPeachCastle != nullptr)
	{
		textPeachCastle->deleteMe();
		delete textPeachCastle;
		textPeachCastle = nullptr;
	}
	if (textSandHill != nullptr)
	{
		textSandHill->deleteMe();
		delete textSandHill;
		textSandHill = nullptr;
	}
	if (textKoopaBeach != nullptr)
	{
		textKoopaBeach->deleteMe();
		delete textKoopaBeach;
		textKoopaBeach = nullptr;
	}
	if (textOutsetIsland != nullptr)
	{
		textOutsetIsland->deleteMe();
		delete textOutsetIsland;
		textOutsetIsland = nullptr;
	}
	if (textWeaponsBed != nullptr)
	{
		textWeaponsBed->deleteMe();
		delete textWeaponsBed;
		textWeaponsBed = nullptr;
	}
	if (textMetalHarbor != nullptr)
	{
		textMetalHarbor->deleteMe();
		delete textMetalHarbor;
		textMetalHarbor = nullptr;
	}
	if (textBOB != nullptr)
	{
		textBOB->deleteMe();
		delete textBOB;
		textBOB = nullptr;
	}
	if (textRainbowRoad != nullptr)
	{
		textRainbowRoad->deleteMe();
		delete textRainbowRoad;
		textRainbowRoad = nullptr;
	}
	if (textSnowhead != nullptr)
	{
		textSnowhead->deleteMe();
		delete textSnowhead;
		textSnowhead = nullptr;
	}

	if (textClassicSonic != nullptr)
	{
		textClassicSonic->deleteMe();
		delete textClassicSonic;
		textClassicSonic = nullptr;
	}
	if (textDollSonic != nullptr)
	{
		textDollSonic->deleteMe();
		delete textDollSonic;
		textDollSonic = nullptr;
	}
	if (textMechaSonic != nullptr)
	{
		textMechaSonic->deleteMe();
		delete textMechaSonic;
		textMechaSonic = nullptr;
	}
	if (textDage4Aquatic != nullptr)
	{
		textDage4Aquatic->deleteMe();
		delete textDage4Aquatic;
		textDage4Aquatic = nullptr;
	}
	if (textManiaSonic != nullptr)
	{
		textManiaSonic->deleteMe();
		delete textManiaSonic;
		textManiaSonic = nullptr;
	}
}

void PauseScreen::pause()
{
	Global::gameState = STATE_PAUSED;
	menuSelection = 0;
	menuDisplayID = 0;
	menuSelectionMAX = 4;
	textCursor->setVisibility(true);
	textResume = new GUIText("Resume", 3, font, 0.5f, 0.3f, 1.0f, false, true);
	textRestart = new GUIText("Restart", 3, font, 0.5f, 0.4f, 1.0f, false, true);
	textLevelSelect = new GUIText("Level Select", 3, font, 0.5f, 0.5f, 1.0f, false, true);
	textCharSelect = new GUIText("Character Select", 3, font, 0.5f, 0.6f, 1.0f, false, true);
	textQuit = new GUIText("Quit Game", 3, font, 0.5f, 0.7f, 1.0f, false, true);

	float spacing = 1 / 13.0f;

	textEmeraldCoast = new GUIText("Emerald Coast", 3, font, 0.5f, 0.0f, 1.0f, false, false);
	textSpeedHighway = new GUIText("Speed Highway", 3, font, 0.5f, spacing, 1.0f, false, false);
	textGreenHillZone = new GUIText("Green Hill Zone", 3, font, 0.5f, spacing * 2, 1.0f, false, false);
	textWuhuIsland = new GUIText("Wuhu Island", 3, font, 0.5f, spacing * 3, 1.0f, false, false);
	textPeachCastle = new GUIText("Peach's Castle", 3, font, 0.5f, spacing * 4, 1.0f, false, false);
	textSandHill = new GUIText("Sand Hill", 3, font, 0.5f, spacing * 5, 1.0f, false, false);
	textKoopaBeach = new GUIText("Koopa Beach", 3, font, 0.5f, spacing * 6, 1.0f, false, false);
	textOutsetIsland = new GUIText("Outset Island", 3, font, 0.5f, spacing * 7, 1.0f, false, false);
	textWeaponsBed = new GUIText("Weapons Bed", 3, font, 0.5f, spacing * 8, 1.0f, false, false);
	textMetalHarbor = new GUIText("Metal Harbor", 3, font, 0.5f, spacing * 9, 1.0f, false, false);
	textBOB = new GUIText("Bob-omb Btlfld", 3, font, 0.5f, spacing * 10, 1.0f, false, false);
	textRainbowRoad = new GUIText("Rainbow Road", 3, font, 0.5f, spacing * 11, 1.0f, false, false);
	textSnowhead = new GUIText("Snowhead", 3, font, 0.5f, spacing * 12, 1.0f, false, false);

	textClassicSonic = new GUIText("Classic Sonic", 3, font, 0.5f, 0.3f, 1.0f, false, false);
	textDollSonic = new GUIText("Sonic Doll", 3, font, 0.5f, 0.4f, 1.0f, false, false);
	textMechaSonic = new GUIText("Mecha Sonic", 3, font, 0.5f, 0.5f, 1.0f, false, false);
	textDage4Aquatic = new GUIText("Dage4 Aquatic", 3, font, 0.5f, 0.6f, 1.0f, false, false);
	textManiaSonic = new GUIText("Mania Sonic", 3, font, 0.5f, 0.7f, 1.0f, false, false);
}