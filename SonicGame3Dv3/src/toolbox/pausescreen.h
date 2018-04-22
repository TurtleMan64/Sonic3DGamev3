#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

class FontType;
class GUIText;


class PauseScreen
{
private:
	static int menuSelection;
	static int menuSelectionMAX;
	static int menuDisplayID;
	static const int ROOT = 0;
	static const int LEVEL_SELECT = 1;
	static const int CHAR_SELECT = 2;

	static int moveYPrevious;
	static bool selectInputPrevious;
	static bool backInputPrevious;

	static GUIText* textCursor;
	static GUIText* textResume;
	static GUIText* textRestart;
	static GUIText* textLevelSelect;
	static GUIText* textCharSelect;
	static GUIText* textQuit;

	static GUIText* textEmeraldCoast;
	static GUIText* textGreenHillZone;
	static GUIText* textSpeedHighway;
	static GUIText* textWuhuIsland;
	static GUIText* textPeachCastle;
	static GUIText* textSandHill;
	static GUIText* textKoopaBeach;
	static GUIText* textOutsetIsland;
	static GUIText* textWeaponsBed;
	static GUIText* textMetalHarbor;
	static GUIText* textBOB;
	static GUIText* textRainbowRoad;
	static GUIText* textSnowhead;
	static GUIText* textTwinklePark;
	static GUIText* textFireField;

	static GUIText* textClassicSonic;
	static GUIText* textDollSonic;
	static GUIText* textMechaSonic;
	static GUIText* textDage4Aquatic;
	static GUIText* textManiaSonic;
	static GUIText* textAmy;

	static bool shouldPause;

	static bool pausedSounds[14];

public:
	static FontType* font;

	static void init();

	static void step();

	static void unpause(bool shouldResumeSFX);

	static void pause();
};

#endif