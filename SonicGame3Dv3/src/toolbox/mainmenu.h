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
	static const int MISSION_16   = 24;
	static const int MISSION_17   = 25;
	static const int MISSION_18   = 26;
	static const int MISSION_19   = 27;
	static const int MISSION_20   = 28;

	static const int MISSION_MAX = MISSION_20;

	static int moveXPrevious;
	static int moveYPrevious;
	static bool selectInputPrevious;
	static bool backInputPrevious;

	static GUIText* textMission1; //Emerald Coast;
	static GUIText* textMission2; //Dry Lagoon;
	static GUIText* textMission3; //Speed Highway;
	static GUIText* textMission4; //Twinkle Park;
	static GUIText* textMission5; //Wild Canyon;
	static GUIText* textMission6; //Metal Harbor;
	static GUIText* textMission7; //Delfino Plaza;
	static GUIText* textMission8; //Green Hill Zone;
	static GUIText* textMission9; //Noki Bay;
	static GUIText* textMission10;//Weapons Bed;
	static GUIText* textMission11;//Outset Island;
	static GUIText* textMission12;//Wuhu Island;
	static GUIText* textMission13;//Snowhead;
	static GUIText* textMission14;//Sand Hill;
	static GUIText* textMission15;//Rainbow Road;
	static GUIText* textMission16;//Peach's Castle;
	static GUIText* textMission17;//Koopa Beach;
	static GUIText* textMission18;//Fire Field;
	static GUIText* textMission19;//Bob-omb Battlefield;
	static GUIText* textMission20;//Kingdom Valley;

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
	static GLuint textureRankA;
	static GLuint textureRankB;
	static GLuint textureRankC;
	static GLuint textureRankD;
	static GLuint textureRankE;
	static GLuint textureRankBlank;
	static GLuint textureMissionSelect;

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
	static GuiTexture* itemMission16;
	static GuiTexture* itemMission17;
	static GuiTexture* itemMission18;
	static GuiTexture* itemMission19;
	static GuiTexture* itemMission20;
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
	static GuiTexture* itemMissionBackdrop16;
	static GuiTexture* itemMissionBackdrop17;
	static GuiTexture* itemMissionBackdrop18;
	static GuiTexture* itemMissionBackdrop19;
	static GuiTexture* itemMissionBackdrop20;

	static GuiTexture* itemRankDisplay;
	static GuiTexture* itemRankDisplayBackdrop;

	static GuiTexture* rankM1;
	static GuiTexture* rankM2;
	static GuiTexture* rankM3;
	static GuiTexture* rankM4;

	static GuiTexture* missionSelect;

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