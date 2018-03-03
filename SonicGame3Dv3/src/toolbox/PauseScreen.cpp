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
GUIText* PauseScreen::textTwinklePark = nullptr;
GUIText* PauseScreen::textFireField = nullptr;

GUIText* PauseScreen::textClassicSonic = nullptr;
GUIText* PauseScreen::textDollSonic = nullptr;
GUIText* PauseScreen::textMechaSonic = nullptr;
GUIText* PauseScreen::textDage4Aquatic = nullptr;
GUIText* PauseScreen::textManiaSonic = nullptr;
GUIText* PauseScreen::textAmy = nullptr;

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
	Global::countNew++;
	textCursor = new GUIText(">", 3, font, 0.47f, 0.25f, 1.0f, false, false);
	Global::countNew++;
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
			textAmy->setColour(0.6f, 0.6f, 0.6f);
			break;

		case 1:
			textClassicSonic->setColour(0.6f, 0.6f, 0.6f);
			textDollSonic->setColour(1, 1, 1);
			textMechaSonic->setColour(0.6f, 0.6f, 0.6f);
			textDage4Aquatic->setColour(0.6f, 0.6f, 0.6f);
			textManiaSonic->setColour(0.6f, 0.6f, 0.6f);
			textAmy->setColour(0.6f, 0.6f, 0.6f);
			break;

		case 2:
			textClassicSonic->setColour(0.6f, 0.6f, 0.6f);
			textDollSonic->setColour(0.6f, 0.6f, 0.6f);
			textMechaSonic->setColour(1, 1, 1);
			textDage4Aquatic->setColour(0.6f, 0.6f, 0.6f);
			textManiaSonic->setColour(0.6f, 0.6f, 0.6f);
			textAmy->setColour(0.6f, 0.6f, 0.6f);
			break;

		case 3:
			textClassicSonic->setColour(0.6f, 0.6f, 0.6f);
			textDollSonic->setColour(0.6f, 0.6f, 0.6f);
			textMechaSonic->setColour(0.6f, 0.6f, 0.6f);
			textDage4Aquatic->setColour(1, 1, 1);
			textManiaSonic->setColour(0.6f, 0.6f, 0.6f);
			textAmy->setColour(0.6f, 0.6f, 0.6f);
			break;

		case 4:
			textClassicSonic->setColour(0.6f, 0.6f, 0.6f);
			textDollSonic->setColour(0.6f, 0.6f, 0.6f);
			textMechaSonic->setColour(0.6f, 0.6f, 0.6f);
			textDage4Aquatic->setColour(0.6f, 0.6f, 0.6f);
			textManiaSonic->setColour(1, 1, 1);
			textAmy->setColour(0.6f, 0.6f, 0.6f);
			break;

		case 5:
			textClassicSonic->setColour(0.6f, 0.6f, 0.6f);
			textDollSonic->setColour(0.6f, 0.6f, 0.6f);
			textMechaSonic->setColour(0.6f, 0.6f, 0.6f);
			textDage4Aquatic->setColour(0.6f, 0.6f, 0.6f);
			textManiaSonic->setColour(0.6f, 0.6f, 0.6f);
			textAmy->setColour(1, 1, 1);
			break;

		default:
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
					menuSelectionMAX = 14;
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
					textTwinklePark->setVisibility(true);
					textFireField->setVisibility(true);

					textClassicSonic->setVisibility(false);
					textDollSonic->setVisibility(false);
					textMechaSonic->setVisibility(false);
					textDage4Aquatic->setVisibility(false);
					textManiaSonic->setVisibility(false);
					textAmy->setVisibility(false);
					break;

				case 3:
					menuDisplayID = CHAR_SELECT;
					menuSelectionMAX = 5;
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
					textTwinklePark->setVisibility(false);
					textFireField->setVisibility(false);

					textClassicSonic->setVisibility(true);
					textDollSonic->setVisibility(true);
					textMechaSonic->setVisibility(true);
					textDage4Aquatic->setVisibility(true);
					textManiaSonic->setVisibility(true);
					textAmy->setVisibility(true);
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

				case 13:
					Global::levelID = LVL_TP;
					LevelLoader_loadLevel("TwinklePark.lvl");
					unpause();
					break;

				case 14:
					Global::levelID = LVL_FF;
					LevelLoader_loadLevel("FireField.lvl");
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

				case 5:
					if (Global::unlockedAmy)
					{
						Player::characterID = 5;
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
				textTwinklePark->setVisibility(false);
				textFireField->setVisibility(false);

				textClassicSonic->setVisibility(false);
				textDollSonic->setVisibility(false);
				textMechaSonic->setVisibility(false);
				textDage4Aquatic->setVisibility(false);
				textManiaSonic->setVisibility(false);
				textAmy->setVisibility(false);
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
			float spacing = 1 / 15.0f;
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

				case 13: textCursor->getPosition()->y = spacing * 13; break;

				case 14: textCursor->getPosition()->y = spacing * 14; break;

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

				case 5: textCursor->getPosition()->y = 0.8f; break;

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
		Global::countDelete++;
		textResume = nullptr;
	}
	if (textRestart != nullptr)
	{
		textRestart->deleteMe();
		delete textRestart;
		Global::countDelete++;
		textRestart = nullptr;
	}
	if (textQuit != nullptr)
	{
		textQuit->deleteMe();
		delete textQuit;
		Global::countDelete++;
		textQuit = nullptr;
	}
	if (textLevelSelect != nullptr)
	{
		textLevelSelect->deleteMe();
		delete textLevelSelect;
		Global::countDelete++;
		textLevelSelect = nullptr;
	}
	if (textCharSelect != nullptr)
	{
		textCharSelect->deleteMe();
		delete textCharSelect;
		Global::countDelete++;
		textCharSelect = nullptr;
	}

	if (textEmeraldCoast != nullptr)
	{
		textEmeraldCoast->deleteMe();
		delete textEmeraldCoast;
		Global::countDelete++;
		textEmeraldCoast = nullptr;
	}
	if (textGreenHillZone != nullptr)
	{
		textGreenHillZone->deleteMe();
		delete textGreenHillZone;
		Global::countDelete++;
		textGreenHillZone = nullptr;
	}
	if (textSpeedHighway != nullptr)
	{
		textSpeedHighway->deleteMe();
		delete textSpeedHighway;
		Global::countDelete++;
		textSpeedHighway = nullptr;
	}
	if (textWuhuIsland != nullptr)
	{
		textWuhuIsland->deleteMe();
		delete textWuhuIsland;
		Global::countDelete++;
		textWuhuIsland = nullptr;
	}
	if (textPeachCastle != nullptr)
	{
		textPeachCastle->deleteMe();
		delete textPeachCastle;
		Global::countDelete++;
		textPeachCastle = nullptr;
	}
	if (textSandHill != nullptr)
	{
		textSandHill->deleteMe();
		delete textSandHill;
		Global::countDelete++;
		textSandHill = nullptr;
	}
	if (textKoopaBeach != nullptr)
	{
		textKoopaBeach->deleteMe();
		delete textKoopaBeach;
		Global::countDelete++;
		textKoopaBeach = nullptr;
	}
	if (textOutsetIsland != nullptr)
	{
		textOutsetIsland->deleteMe();
		delete textOutsetIsland;
		Global::countDelete++;
		textOutsetIsland = nullptr;
	}
	if (textWeaponsBed != nullptr)
	{
		textWeaponsBed->deleteMe();
		delete textWeaponsBed;
		Global::countDelete++;
		textWeaponsBed = nullptr;
	}
	if (textMetalHarbor != nullptr)
	{
		textMetalHarbor->deleteMe();
		delete textMetalHarbor;
		Global::countDelete++;
		textMetalHarbor = nullptr;
	}
	if (textBOB != nullptr)
	{
		textBOB->deleteMe();
		delete textBOB;
		Global::countDelete++;
		textBOB = nullptr;
	}
	if (textRainbowRoad != nullptr)
	{
		textRainbowRoad->deleteMe();
		delete textRainbowRoad;
		Global::countDelete++;
		textRainbowRoad = nullptr;
	}
	if (textSnowhead != nullptr)
	{
		textSnowhead->deleteMe();
		delete textSnowhead;
		Global::countDelete++;
		textSnowhead = nullptr;
	}
	if (textTwinklePark != nullptr)
	{
		textTwinklePark->deleteMe();
		delete textTwinklePark;
		Global::countDelete++;
		textTwinklePark = nullptr;
	}
	if (textFireField != nullptr)
	{
		textFireField->deleteMe();
		delete textFireField;
		Global::countDelete++;
		textFireField = nullptr;
	}

	if (textClassicSonic != nullptr)
	{
		textClassicSonic->deleteMe();
		delete textClassicSonic;
		Global::countDelete++;
		textClassicSonic = nullptr;
	}
	if (textDollSonic != nullptr)
	{
		textDollSonic->deleteMe();
		delete textDollSonic;
		Global::countDelete++;
		textDollSonic = nullptr;
	}
	if (textMechaSonic != nullptr)
	{
		textMechaSonic->deleteMe();
		delete textMechaSonic;
		Global::countDelete++;
		textMechaSonic = nullptr;
	}
	if (textDage4Aquatic != nullptr)
	{
		textDage4Aquatic->deleteMe();
		delete textDage4Aquatic;
		Global::countDelete++;
		textDage4Aquatic = nullptr;
	}
	if (textManiaSonic != nullptr)
	{
		textManiaSonic->deleteMe();
		delete textManiaSonic;
		Global::countDelete++;
		textManiaSonic = nullptr;
	}
	if (textAmy != nullptr)
	{
		textAmy->deleteMe();
		delete textAmy;
		Global::countDelete++;
		textAmy = nullptr;
	}
}

void PauseScreen::pause()
{
	if (Global::gamePlayer != nullptr && Global::gamePlayer->isDying() == true)
	{
		return;
	}

	Global::gameState = STATE_PAUSED;
	menuSelection = 0;
	menuDisplayID = 0;
	menuSelectionMAX = 4;
	textCursor->setVisibility(true);
	textResume = new GUIText("Resume", 3, font, 0.5f, 0.3f, 1.0f, false, true); Global::countNew++;
	textRestart = new GUIText("Restart", 3, font, 0.5f, 0.4f, 1.0f, false, true); Global::countNew++;
	textLevelSelect = new GUIText("Level Select", 3, font, 0.5f, 0.5f, 1.0f, false, true); Global::countNew++;
	textCharSelect = new GUIText("Character Select", 3, font, 0.5f, 0.6f, 1.0f, false, true); Global::countNew++;
	textQuit = new GUIText("Quit Game", 3, font, 0.5f, 0.7f, 1.0f, false, true); Global::countNew++;

	float spacing = 1 / 15.0f;

	textEmeraldCoast = new GUIText("Emerald Coast", 3, font, 0.5f, 0.0f, 1.0f, false, false); Global::countNew++;
	textSpeedHighway = new GUIText("Speed Highway", 3, font, 0.5f, spacing, 1.0f, false, false); Global::countNew++;
	textGreenHillZone = new GUIText("Green Hill Zone", 3, font, 0.5f, spacing * 2, 1.0f, false, false); Global::countNew++;
	textWuhuIsland = new GUIText("Wuhu Island", 3, font, 0.5f, spacing * 3, 1.0f, false, false); Global::countNew++;
	textPeachCastle = new GUIText("Peach's Castle", 3, font, 0.5f, spacing * 4, 1.0f, false, false); Global::countNew++;
	textSandHill = new GUIText("Sand Hill", 3, font, 0.5f, spacing * 5, 1.0f, false, false); Global::countNew++;
	textKoopaBeach = new GUIText("Koopa Beach", 3, font, 0.5f, spacing * 6, 1.0f, false, false); Global::countNew++;
	textOutsetIsland = new GUIText("Outset Island", 3, font, 0.5f, spacing * 7, 1.0f, false, false); Global::countNew++;
	textWeaponsBed = new GUIText("Weapons Bed", 3, font, 0.5f, spacing * 8, 1.0f, false, false); Global::countNew++;
	textMetalHarbor = new GUIText("Metal Harbor", 3, font, 0.5f, spacing * 9, 1.0f, false, false); Global::countNew++;
	textBOB = new GUIText("Bob-omb Btlfld", 3, font, 0.5f, spacing * 10, 1.0f, false, false); Global::countNew++;
	textRainbowRoad = new GUIText("Rainbow Road", 3, font, 0.5f, spacing * 11, 1.0f, false, false); Global::countNew++;
	textSnowhead = new GUIText("Snowhead", 3, font, 0.5f, spacing * 12, 1.0f, false, false); Global::countNew++;
	textTwinklePark = new GUIText("Twinkle Park", 3, font, 0.5f, spacing * 13, 1.0f, false, false); Global::countNew++;
	textFireField = new GUIText("Fire Field", 3, font, 0.5f, spacing * 14, 1.0f, false, false); Global::countNew++;

	textClassicSonic = new GUIText("Classic Sonic", 3, font, 0.5f, 0.3f, 1.0f, false, false); Global::countNew++;
	textDollSonic = new GUIText("Sonic Doll", 3, font, 0.5f, 0.4f, 1.0f, false, false); Global::countNew++;
	textMechaSonic = new GUIText("Mecha Sonic", 3, font, 0.5f, 0.5f, 1.0f, false, false); Global::countNew++;
	textDage4Aquatic = new GUIText("Dage4 Aquatic", 3, font, 0.5f, 0.6f, 1.0f, false, false); Global::countNew++;
	textManiaSonic = new GUIText("Mania Sonic", 3, font, 0.5f, 0.7f, 1.0f, false, false); Global::countNew++;
	textAmy = new GUIText("Amy", 3, font, 0.5f, 0.8f, 1.0f, false, false); Global::countNew++;
}