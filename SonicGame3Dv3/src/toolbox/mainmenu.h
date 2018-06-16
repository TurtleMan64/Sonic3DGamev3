#ifndef MAINMENU_H
#define MAINMENU_H

#include <glad/glad.h>

class FontType;
class GUIText;
class GuiTexture;

class MainMenu
{
private:
	static int menuSelectionID;
	static const int ROOT_STORY   = 1;
	static const int ROOT_MISSION = 2;
	static const int ROOT_EXTRAS  = 3;
	static const int ROOT_EXIT    = 4;
	static const int MISSION_1    = 9;
	static const int MISSION_2    = 10;
	static const int MISSION_3    = 11;
	static const int MISSION_4    = 12;
	static const int MISSION_5    = 13;
	static const int MISSION_6    = 14;
	static const int MISSION_7    = 15;
	static const int MISSION_8    = 16;
	static const int MISSION_9    = 17;
	static const int MISSION_10   = 18;
	static const int MISSION_11   = 19;
	static const int MISSION_12   = 20;
	static const int MISSION_13   = 21;
	static const int MISSION_14   = 22;
	static const int MISSION_15   = 23;

	static int moveXPrevious;
	static int moveYPrevious;
	static bool selectInputPrevious;
	static bool backInputPrevious;

	//static GUIText* textCursor;

	static GUIText* textMission1;//textEmeraldCoast;
	static GUIText* textMission2;//textGreenHillZone;
	static GUIText* textMission3;//textSpeedHighway;
	static GUIText* textMission4;//textWuhuIsland;
	static GUIText* textMission5;//textPeachCastle;
	static GUIText* textMission6;//textSandHill;
	static GUIText* textMission7;//textKoopaBeach;
	static GUIText* textMission8;//textOutsetIsland;
	static GUIText* textMission9;//textWeaponsBed;
	static GUIText* textMission10;//textMetalHarbor;
	static GUIText* textMission11;//textBOB;
	static GUIText* textMission12;//textRainbowRoad;
	static GUIText* textMission13;//textSnowhead;
	static GUIText* textMission14;//textTwinklePark;
	static GUIText* textMission15;//textFireField;

	//static GUIText* textClassicSonic;
	//static GUIText* textDollSonic;
	//static GUIText* textMechaSonic;
	//static GUIText* textDage4Aquatic;
	//static GUIText* textManiaSonic;
	//static GUIText* textAmy;

	static GUIText* textTitleCardLevelName;
	static GUIText* textTitleCardMission;
	static GUIText* textTitleCardMissionDescription;

	static GUIText* textItem1; //STORY MODE
	static GUIText* textItem2; //MISSION MODE
	static GUIText* textItem3; //EXTRAS
	static GUIText* textItem4; //QUIT

	static GLuint textureParallelogram;
	static GLuint textureParallelogramBackdrop;
	static GLuint textureParallelogramHalf;
	static GLuint textureParallelogramHalfBackdrop;

	//Parallelograms for ROOT
	static GuiTexture* item1;
	static GuiTexture* item2;
	static GuiTexture* item3;
	static GuiTexture* item4;
	static GuiTexture* itemBackdrop1;
	static GuiTexture* itemBackdrop2;
	static GuiTexture* itemBackdrop3;
	static GuiTexture* itemBackdrop4;

	//Parallelograms for MISSION
	static GuiTexture* itemMission1;
	static GuiTexture* itemMission2;
	static GuiTexture* itemMission3;
	static GuiTexture* itemMission4;
	static GuiTexture* itemMission5;
	static GuiTexture* itemMission6;
	static GuiTexture* itemMission7;
	static GuiTexture* itemMission8;
	static GuiTexture* itemMission9;
	static GuiTexture* itemMission10;
	static GuiTexture* itemMission11;
	static GuiTexture* itemMission12;
	static GuiTexture* itemMission13;
	static GuiTexture* itemMission14;
	static GuiTexture* itemMission15;
	static GuiTexture* itemMissionBackdrop1;
	static GuiTexture* itemMissionBackdrop2;
	static GuiTexture* itemMissionBackdrop3;
	static GuiTexture* itemMissionBackdrop4;
	static GuiTexture* itemMissionBackdrop5;
	static GuiTexture* itemMissionBackdrop6;
	static GuiTexture* itemMissionBackdrop7;
	static GuiTexture* itemMissionBackdrop8;
	static GuiTexture* itemMissionBackdrop9;
	static GuiTexture* itemMissionBackdrop10;
	static GuiTexture* itemMissionBackdrop11;
	static GuiTexture* itemMissionBackdrop12;
	static GuiTexture* itemMissionBackdrop13;
	static GuiTexture* itemMissionBackdrop14;
	static GuiTexture* itemMissionBackdrop15;

	static int titleCardTextTimer;

	static void createTitleCard();

	static void selectMenuRoot(int newSelection);

	static void selectMenuMission(int newSelection);

	static void unloadResources();

public:
	static FontType* font;

	static void init();

	static void step();

	static void loadResources();
};

#endif