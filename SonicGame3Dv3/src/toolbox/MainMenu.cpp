#include "mainmenu.h"
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
#include "../guis/guitexture.h"

int MainMenu::menuSelectionID = 0;

int MainMenu::moveXPrevious = 0;
int MainMenu::moveYPrevious = 0;
bool MainMenu::selectInputPrevious = false;
bool MainMenu::backInputPrevious = false;

GUIText* MainMenu::textMission1  = nullptr;//textEmeraldCoast;
GUIText* MainMenu::textMission2  = nullptr;//textGreenHillZone;
GUIText* MainMenu::textMission3  = nullptr;//textSpeedHighway;
GUIText* MainMenu::textMission4  = nullptr;//textWuhuIsland;
GUIText* MainMenu::textMission5  = nullptr;//textPeachCastle;
GUIText* MainMenu::textMission6  = nullptr;//textSandHill;
GUIText* MainMenu::textMission7  = nullptr;//textKoopaBeach;
GUIText* MainMenu::textMission8  = nullptr;//textOutsetIsland;
GUIText* MainMenu::textMission9  = nullptr;//textWeaponsBed;
GUIText* MainMenu::textMission10 = nullptr;//textMetalHarbor;
GUIText* MainMenu::textMission11 = nullptr;//textBOB;
GUIText* MainMenu::textMission12 = nullptr;//textRainbowRoad;
GUIText* MainMenu::textMission13 = nullptr;//textSnowhead;
GUIText* MainMenu::textMission14 = nullptr;//textTwinklePark;
GUIText* MainMenu::textMission15 = nullptr;//textFireField;

GUIText* MainMenu::textTitleCardLevelName          = nullptr;
GUIText* MainMenu::textTitleCardMission            = nullptr;
GUIText* MainMenu::textTitleCardMissionDescription = nullptr;

GUIText* MainMenu::textItem1 = nullptr;
GUIText* MainMenu::textItem2 = nullptr;
GUIText* MainMenu::textItem3 = nullptr;
GUIText* MainMenu::textItem4 = nullptr;

GLuint MainMenu::textureParallelogram             = (GLuint)-1;
GLuint MainMenu::textureParallelogramBackdrop     = (GLuint)-1;
GLuint MainMenu::textureParallelogramHalf         = (GLuint)-1;
GLuint MainMenu::textureParallelogramHalfBackdrop = (GLuint)-1;
GLuint MainMenu::textureRankA					  = (GLuint)-1;
GLuint MainMenu::textureRankB					  = (GLuint)-1;
GLuint MainMenu::textureRankC					  = (GLuint)-1;
GLuint MainMenu::textureRankD					  = (GLuint)-1;
GLuint MainMenu::textureRankE					  = (GLuint)-1;
GLuint MainMenu::textureRankBlank				  = (GLuint)-1;
GLuint MainMenu::textureMissionSelect			  = (GLuint)-1;

GuiTexture* MainMenu::item1 = nullptr;
GuiTexture* MainMenu::item2 = nullptr;
GuiTexture* MainMenu::item3 = nullptr;
GuiTexture* MainMenu::item4 = nullptr;
GuiTexture* MainMenu::itemBackdrop1 = nullptr;
GuiTexture* MainMenu::itemBackdrop2 = nullptr;
GuiTexture* MainMenu::itemBackdrop3 = nullptr;
GuiTexture* MainMenu::itemBackdrop4 = nullptr;

GuiTexture* MainMenu::itemMission1  = nullptr;
GuiTexture* MainMenu::itemMission2  = nullptr;
GuiTexture* MainMenu::itemMission3  = nullptr;
GuiTexture* MainMenu::itemMission4  = nullptr;
GuiTexture* MainMenu::itemMission5  = nullptr;
GuiTexture* MainMenu::itemMission6  = nullptr;
GuiTexture* MainMenu::itemMission7  = nullptr;
GuiTexture* MainMenu::itemMission8  = nullptr;
GuiTexture* MainMenu::itemMission9  = nullptr;
GuiTexture* MainMenu::itemMission10 = nullptr;
GuiTexture* MainMenu::itemMission11 = nullptr;
GuiTexture* MainMenu::itemMission12 = nullptr;
GuiTexture* MainMenu::itemMission13 = nullptr;
GuiTexture* MainMenu::itemMission14 = nullptr;
GuiTexture* MainMenu::itemMission15 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop1  = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop2  = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop3  = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop4  = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop5  = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop6  = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop7  = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop8  = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop9  = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop10 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop11 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop12 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop13 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop14 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop15 = nullptr;

GuiTexture* MainMenu::itemRankDisplay = nullptr;
GuiTexture* MainMenu::itemRankDisplayBackdrop = nullptr;

GuiTexture* MainMenu::rankM1 = nullptr;
GuiTexture* MainMenu::rankM2 = nullptr;
GuiTexture* MainMenu::rankM3 = nullptr;
GuiTexture* MainMenu::rankM4 = nullptr;

GuiTexture* MainMenu::missionSelect = nullptr;

int MainMenu::titleCardTextTimer = 0;

FontType* MainMenu::font = nullptr;

extern bool INPUT_JUMP;
extern bool INPUT_ACTION;
extern bool INPUT_START;

extern bool INPUT_PREVIOUS_JUMP;
extern bool INPUT_PREVIOUS_ACTION;
extern bool INPUT_PREVIOUS_START;

extern int MENU_X;
extern int MENU_Y;

void MainMenu::init()
{
	font = new FontType(Loader_loadTexture("res/Fonts/vipnagorgialla.png"), "res/Fonts/vipnagorgialla.fnt"); Global::countNew++;

	MainMenu::titleCardTextTimer = 0;

	textureParallelogram             = Loader_loadTextureNoInterpolation("res/Images/MainMenu/Parallelogram.png");
	textureParallelogramBackdrop     = Loader_loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramBackdrop.png");
	textureParallelogramHalf         = Loader_loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramHalf.png");
	textureParallelogramHalfBackdrop = Loader_loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramHalfBackdrop.png");
	textureRankA					  = Loader_loadTextureNoInterpolation("res/Images/MainMenu/RankA.png");
	textureRankB					  = Loader_loadTextureNoInterpolation("res/Images/MainMenu/RankB.png");
	textureRankC					  = Loader_loadTextureNoInterpolation("res/Images/MainMenu/RankC.png");
	textureRankD					  = Loader_loadTextureNoInterpolation("res/Images/MainMenu/RankD.png");
	textureRankE					  = Loader_loadTextureNoInterpolation("res/Images/MainMenu/RankE.png");
	textureRankBlank				  = Loader_loadTextureNoInterpolation("res/Images/MainMenu/NoRank.png");
	textureMissionSelect			  = Loader_loadTextureNoInterpolation("res/Images/MainMenu/MissionSelect.png");

	MainMenu::loadResources();

	MainMenu::selectMenuRoot(ROOT_STORY);
}

void MainMenu::loadResources()
{
	if (textItem1 != nullptr)
	{
		std::fprintf(stdout, "Main Menu trying to load resources when they are already loaded!\n");
		return;
	}

	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;
	float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension
	float py = 1.0f/(SCR_HEIGHT); //1 pixel in y dimension

	textItem1 = new GUIText("STORY",    2.85f, font, 0.0f,   0.333f-0.04f, 0.666f, true, false, true); Global::countNew++;
	textItem2 = new GUIText("MISSIONS", 2.85f, font, 0.333f, 0.333f-0.04f, 0.666f, true, false, true); Global::countNew++;
	textItem3 = new GUIText("EXTRAS",   2.85f, font, 0.0f,   0.666f-0.04f, 0.666f, true, false, true); Global::countNew++;
	textItem4 = new GUIText("EXIT",     2.85f, font, 0.333f, 0.666f-0.04f, 0.666f, true, false, true); Global::countNew++;

	item1 = new GuiTexture(textureParallelogram, 0.333f, 0.333f, 512*px, 64*py, 0); Global::countNew++;
	item2 = new GuiTexture(textureParallelogram, 0.666f, 0.333f, 512*px, 64*py, 0); Global::countNew++;
	item3 = new GuiTexture(textureParallelogram, 0.333f, 0.666f, 512*px, 64*py, 0); Global::countNew++;
	item4 = new GuiTexture(textureParallelogram, 0.666f, 0.666f, 512*px, 64*py, 0); Global::countNew++;
	itemBackdrop1 = new GuiTexture(textureParallelogramBackdrop, 0.333f+8*px, 0.333f+6*py, 512*px, 64*py, 0); Global::countNew++;
	itemBackdrop2 = new GuiTexture(textureParallelogramBackdrop, 0.666f+8*px, 0.333f+6*py, 512*px, 64*py, 0); Global::countNew++;
	itemBackdrop3 = new GuiTexture(textureParallelogramBackdrop, 0.333f+8*px, 0.666f+6*py, 512*px, 64*py, 0); Global::countNew++;
	itemBackdrop4 = new GuiTexture(textureParallelogramBackdrop, 0.666f+8*px, 0.666f+6*py, 512*px, 64*py, 0); Global::countNew++;

	itemMission1  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission2  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission3  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission4  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission5  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission6  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission7  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission8  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission9  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission10 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission11 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission12 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission13 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission14 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission15 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop1  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop2  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop3  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop4  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop5  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop6  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop7  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop8  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop9  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop10 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop11 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop12 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop13 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop14 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop15 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;

	itemRankDisplay = new GuiTexture(textureParallelogram, 0.75f, 0.5f, 512*px, 64*py, 0); Global::countNew++;
	itemRankDisplayBackdrop = new GuiTexture(textureParallelogramBackdrop, 0.75f+8*px, 0.5f+6*py, 512*px, 64*py, 0); Global::countNew++;

	rankM1 = new GuiTexture(textureRankA, 0.75f-83*px, 0.5f, 64*px, 64*py, 0); Global::countNew++;
	rankM2 = new GuiTexture(textureRankB, 0.75f-28*px, 0.5f, 64*px, 64*py, 0); Global::countNew++;
	rankM3 = new GuiTexture(textureRankC, 0.75f+27*px, 0.5f, 64*px, 64*py, 0); Global::countNew++;
	rankM4 = new GuiTexture(textureRankD, 0.75f+82*px, 0.5f, 64*px, 64*py, 0); Global::countNew++;

	missionSelect = new GuiTexture(textureMissionSelect, 0.75f-83*px, 0.5f, 96*px, 96*py, 0); Global::countNew++; //change scale probably

	textMission1  = new GUIText("EMERALD COAST",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission2  = new GUIText("GREEN HILL ZONE",     2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission3  = new GUIText("SPEED HIGHWAY",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission4  = new GUIText("WUHU ISLAND",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission5  = new GUIText("PEACH'S CASTLE",      2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission6  = new GUIText("SAND HILL",           2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission7  = new GUIText("KOOPA BEACH",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission8  = new GUIText("OUTSET ISLAND",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission9  = new GUIText("WEAPONS BED",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission10 = new GUIText("METAL HARBOR",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission11 = new GUIText("BOB-OMB BATTLEFIELD", 2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission12 = new GUIText("RAINBOW ROAD",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission13 = new GUIText("SNOWHEAD",            2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission14 = new GUIText("TWINKLE PARK",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission15 = new GUIText("FIRE FIELD",          2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;

	MainMenu::selectMenuRoot(ROOT_STORY);
}

void MainMenu::unloadResources()
{
	if (textItem1 == nullptr)
	{
		std::fprintf(stdout, "Main Menu trying to unload resources when they are already unloaded!\n");
		return;
	}

	textItem1->deleteMe(); delete textItem1; Global::countDelete++; textItem1 = nullptr;
	textItem2->deleteMe(); delete textItem2; Global::countDelete++; textItem2 = nullptr;
	textItem3->deleteMe(); delete textItem3; Global::countDelete++; textItem3 = nullptr;
	textItem4->deleteMe(); delete textItem4; Global::countDelete++; textItem4 = nullptr;

	textMission1 ->deleteMe(); delete textMission1;  Global::countDelete++; textMission1  = nullptr;
	textMission2 ->deleteMe(); delete textMission2;  Global::countDelete++; textMission2  = nullptr;
	textMission3 ->deleteMe(); delete textMission3;  Global::countDelete++; textMission3  = nullptr;
	textMission4 ->deleteMe(); delete textMission4;  Global::countDelete++; textMission4  = nullptr;
	textMission5 ->deleteMe(); delete textMission5;  Global::countDelete++; textMission5  = nullptr;
	textMission6 ->deleteMe(); delete textMission6;  Global::countDelete++; textMission6  = nullptr;
	textMission7 ->deleteMe(); delete textMission7;  Global::countDelete++; textMission7  = nullptr;
	textMission8 ->deleteMe(); delete textMission8;  Global::countDelete++; textMission8  = nullptr;
	textMission9 ->deleteMe(); delete textMission9;  Global::countDelete++; textMission9  = nullptr;
	textMission10->deleteMe(); delete textMission10; Global::countDelete++; textMission10 = nullptr;
	textMission11->deleteMe(); delete textMission11; Global::countDelete++; textMission11 = nullptr;
	textMission12->deleteMe(); delete textMission12; Global::countDelete++; textMission12 = nullptr;
	textMission13->deleteMe(); delete textMission13; Global::countDelete++; textMission13 = nullptr;
	textMission14->deleteMe(); delete textMission14; Global::countDelete++; textMission14 = nullptr;
	textMission15->deleteMe(); delete textMission15; Global::countDelete++; textMission15 = nullptr;

	GuiManager::clearGuisToRender();

	delete item1; Global::countDelete++; item1 = nullptr;
	delete item2; Global::countDelete++; item2 = nullptr;
	delete item3; Global::countDelete++; item3 = nullptr;
	delete item4; Global::countDelete++; item4 = nullptr;
	delete itemBackdrop1; Global::countDelete++; itemBackdrop1 = nullptr;
	delete itemBackdrop2; Global::countDelete++; itemBackdrop2 = nullptr;
	delete itemBackdrop3; Global::countDelete++; itemBackdrop3 = nullptr;
	delete itemBackdrop4; Global::countDelete++; itemBackdrop4 = nullptr;

	delete itemMission1;  Global::countDelete++; itemMission1  = nullptr;
	delete itemMission2;  Global::countDelete++; itemMission2  = nullptr;
	delete itemMission3;  Global::countDelete++; itemMission3  = nullptr;
	delete itemMission4;  Global::countDelete++; itemMission4  = nullptr;
	delete itemMission5;  Global::countDelete++; itemMission5  = nullptr;
	delete itemMission6;  Global::countDelete++; itemMission6  = nullptr;
	delete itemMission7;  Global::countDelete++; itemMission7  = nullptr;
	delete itemMission8;  Global::countDelete++; itemMission8  = nullptr;
	delete itemMission9;  Global::countDelete++; itemMission9  = nullptr;
	delete itemMission10; Global::countDelete++; itemMission10 = nullptr;
	delete itemMission11; Global::countDelete++; itemMission11 = nullptr;
	delete itemMission12; Global::countDelete++; itemMission12 = nullptr;
	delete itemMission13; Global::countDelete++; itemMission13 = nullptr;
	delete itemMission14; Global::countDelete++; itemMission14 = nullptr;
	delete itemMission15; Global::countDelete++; itemMission15 = nullptr;
	delete itemMissionBackdrop1;  Global::countDelete++; itemMissionBackdrop1  = nullptr; 
	delete itemMissionBackdrop2;  Global::countDelete++; itemMissionBackdrop2  = nullptr; 
	delete itemMissionBackdrop3;  Global::countDelete++; itemMissionBackdrop3  = nullptr; 
	delete itemMissionBackdrop4;  Global::countDelete++; itemMissionBackdrop4  = nullptr; 
	delete itemMissionBackdrop5;  Global::countDelete++; itemMissionBackdrop5  = nullptr; 
	delete itemMissionBackdrop6;  Global::countDelete++; itemMissionBackdrop6  = nullptr; 
	delete itemMissionBackdrop7;  Global::countDelete++; itemMissionBackdrop7  = nullptr; 
	delete itemMissionBackdrop8;  Global::countDelete++; itemMissionBackdrop8  = nullptr; 
	delete itemMissionBackdrop9;  Global::countDelete++; itemMissionBackdrop9  = nullptr; 
	delete itemMissionBackdrop10; Global::countDelete++; itemMissionBackdrop10 = nullptr;
	delete itemMissionBackdrop11; Global::countDelete++; itemMissionBackdrop11 = nullptr;
	delete itemMissionBackdrop12; Global::countDelete++; itemMissionBackdrop12 = nullptr;
	delete itemMissionBackdrop13; Global::countDelete++; itemMissionBackdrop13 = nullptr;
	delete itemMissionBackdrop14; Global::countDelete++; itemMissionBackdrop14 = nullptr;
	delete itemMissionBackdrop15; Global::countDelete++; itemMissionBackdrop15 = nullptr;

	delete itemRankDisplay; Global::countDelete++; itemRankDisplay = nullptr;
	delete itemRankDisplayBackdrop; Global::countDelete++; itemRankDisplayBackdrop = nullptr;

	delete rankM1; Global::countDelete++; rankM1 = nullptr;
	delete rankM2; Global::countDelete++; rankM2 = nullptr;
	delete rankM3; Global::countDelete++; rankM3 = nullptr;
	delete rankM4; Global::countDelete++; rankM4 = nullptr;

	delete missionSelect; Global::countDelete++; missionSelect = nullptr;
}

void MainMenu::selectMenuMission(int newSelection)
{
	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;
	float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension
	float py = 1.0f/(SCR_HEIGHT); //1 pixel in y dimension

	GuiManager::clearGuisToRender();

	float offsetY = (MISSION_1 - newSelection)*128*py;

	float yPos = 0.5f;
	itemMission1 ->setY(yPos+offsetY); yPos+=128*py;
	itemMission2 ->setY(yPos+offsetY); yPos+=128*py;
	itemMission3 ->setY(yPos+offsetY); yPos+=128*py;
	itemMission4 ->setY(yPos+offsetY); yPos+=128*py;
	itemMission5 ->setY(yPos+offsetY); yPos+=128*py;
	itemMission6 ->setY(yPos+offsetY); yPos+=128*py;
	itemMission7 ->setY(yPos+offsetY); yPos+=128*py;
	itemMission8 ->setY(yPos+offsetY); yPos+=128*py;
	itemMission9 ->setY(yPos+offsetY); yPos+=128*py;
	itemMission10->setY(yPos+offsetY); yPos+=128*py;
	itemMission11->setY(yPos+offsetY); yPos+=128*py;
	itemMission12->setY(yPos+offsetY); yPos+=128*py;
	itemMission13->setY(yPos+offsetY); yPos+=128*py;
	itemMission14->setY(yPos+offsetY); yPos+=128*py;
	itemMission15->setY(yPos+offsetY);
	yPos = 0.5f+6.0f*py;
	itemMissionBackdrop1 ->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop2 ->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop3 ->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop4 ->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop5 ->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop6 ->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop7 ->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop8 ->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop9 ->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop10->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop11->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop12->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop13->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop14->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop15->setY(yPos+offsetY);

	itemMission1 ->setX(0.5f-512*px-64*px);
	itemMission2 ->setX(0.5f-512*px-64*px);
	itemMission3 ->setX(0.5f-512*px-64*px);
	itemMission4 ->setX(0.5f-512*px-64*px);
	itemMission5 ->setX(0.5f-512*px-64*px);
	itemMission6 ->setX(0.5f-512*px-64*px);
	itemMission7 ->setX(0.5f-512*px-64*px);
	itemMission8 ->setX(0.5f-512*px-64*px);
	itemMission9 ->setX(0.5f-512*px-64*px);
	itemMission10->setX(0.5f-512*px-64*px);
	itemMission11->setX(0.5f-512*px-64*px);
	itemMission12->setX(0.5f-512*px-64*px);
	itemMission13->setX(0.5f-512*px-64*px);
	itemMission14->setX(0.5f-512*px-64*px);
	itemMission15->setX(0.5f-512*px-64*px);
	itemMissionBackdrop1 ->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop2 ->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop3 ->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop4 ->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop5 ->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop6 ->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop7 ->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop8 ->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop9 ->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop10->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop11->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop12->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop13->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop14->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop15->setX(0.5f-512*px-64*px+8*px);

	yPos = 0.5f-0.025f;
	textMission1 ->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission2 ->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission3 ->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission4 ->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission5 ->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission6 ->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission7 ->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission8 ->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission9 ->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission10->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission11->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission12->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission13->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission14->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission15->getPosition()->y = yPos+offsetY;
	
	textMission1 ->getPosition()->x = 0.0f;
	textMission2 ->getPosition()->x = 0.0f;
	textMission3 ->getPosition()->x = 0.0f;
	textMission4 ->getPosition()->x = 0.0f;
	textMission5 ->getPosition()->x = 0.0f;
	textMission6 ->getPosition()->x = 0.0f;
	textMission7 ->getPosition()->x = 0.0f;
	textMission8 ->getPosition()->x = 0.0f;
	textMission9 ->getPosition()->x = 0.0f;
	textMission10->getPosition()->x = 0.0f;
	textMission11->getPosition()->x = 0.0f;
	textMission12->getPosition()->x = 0.0f;
	textMission13->getPosition()->x = 0.0f;
	textMission14->getPosition()->x = 0.0f;
	textMission15->getPosition()->x = 0.0f;

	GuiManager::addGuiToRender(itemMission1);
	GuiManager::addGuiToRender(itemMission2);
	GuiManager::addGuiToRender(itemMission3);
	GuiManager::addGuiToRender(itemMission4);
	GuiManager::addGuiToRender(itemMission5);
	GuiManager::addGuiToRender(itemMission6);
	GuiManager::addGuiToRender(itemMission7);
	GuiManager::addGuiToRender(itemMission8);
	GuiManager::addGuiToRender(itemMission9);
	GuiManager::addGuiToRender(itemMission10);
	GuiManager::addGuiToRender(itemMission11);
	GuiManager::addGuiToRender(itemMission12);
	GuiManager::addGuiToRender(itemMission13);
	GuiManager::addGuiToRender(itemMission14);
	GuiManager::addGuiToRender(itemMission15);

	GuiManager::addGuiToRender(itemRankDisplay);
	GuiManager::addGuiToRender(itemRankDisplayBackdrop);

	GuiManager::addGuiToRender(rankM1);
	GuiManager::addGuiToRender(rankM2);
	GuiManager::addGuiToRender(rankM3);
	GuiManager::addGuiToRender(rankM4);

	GuiManager::addGuiToRender(missionSelect);

	switch (newSelection)
	{
		case MISSION_1 : textMission1 ->getPosition()->x += 64*px; itemMission1 ->setX(0.5f-512*px); itemMissionBackdrop1 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop1); break;
		case MISSION_2 : textMission2 ->getPosition()->x += 64*px; itemMission2 ->setX(0.5f-512*px); itemMissionBackdrop2 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop2); break;
		case MISSION_3 : textMission3 ->getPosition()->x += 64*px; itemMission3 ->setX(0.5f-512*px); itemMissionBackdrop3 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop3); break;
		case MISSION_4 : textMission4 ->getPosition()->x += 64*px; itemMission4 ->setX(0.5f-512*px); itemMissionBackdrop4 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop4); break;
		case MISSION_5 : textMission5 ->getPosition()->x += 64*px; itemMission5 ->setX(0.5f-512*px); itemMissionBackdrop5 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop5); break;
		case MISSION_6 : textMission6 ->getPosition()->x += 64*px; itemMission6 ->setX(0.5f-512*px); itemMissionBackdrop6 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop6); break;
		case MISSION_7 : textMission7 ->getPosition()->x += 64*px; itemMission7 ->setX(0.5f-512*px); itemMissionBackdrop7 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop7); break;
		case MISSION_8 : textMission8 ->getPosition()->x += 64*px; itemMission8 ->setX(0.5f-512*px); itemMissionBackdrop8 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop8); break;
		case MISSION_9 : textMission9 ->getPosition()->x += 64*px; itemMission9 ->setX(0.5f-512*px); itemMissionBackdrop9 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop9); break;
		case MISSION_10: textMission10->getPosition()->x += 64*px; itemMission10->setX(0.5f-512*px); itemMissionBackdrop10->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop10); break;
		case MISSION_11: textMission11->getPosition()->x += 64*px; itemMission11->setX(0.5f-512*px); itemMissionBackdrop11->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop11); break;
		case MISSION_12: textMission12->getPosition()->x += 64*px; itemMission12->setX(0.5f-512*px); itemMissionBackdrop12->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop12); break;
		case MISSION_13: textMission13->getPosition()->x += 64*px; itemMission13->setX(0.5f-512*px); itemMissionBackdrop13->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop13); break;
		case MISSION_14: textMission14->getPosition()->x += 64*px; itemMission14->setX(0.5f-512*px); itemMissionBackdrop14->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop14); break;
		case MISSION_15: textMission15->getPosition()->x += 64*px; itemMission15->setX(0.5f-512*px); itemMissionBackdrop15->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop15); break;
		default: break;
	}

	menuSelectionID = newSelection;

	textItem1->setVisibility(false);
	textItem2->setVisibility(false);
	textItem3->setVisibility(false);
	textItem4->setVisibility(false);

	textMission1 ->setVisibility(true);
	textMission2 ->setVisibility(true);
	textMission3 ->setVisibility(true);
	textMission4 ->setVisibility(true);
	textMission5 ->setVisibility(true);
	textMission6 ->setVisibility(true);
	textMission7 ->setVisibility(true);
	textMission8 ->setVisibility(true);
	textMission9 ->setVisibility(true);
	textMission10->setVisibility(true);
	textMission11->setVisibility(true);
	textMission12->setVisibility(true);
	textMission13->setVisibility(true);
	textMission14->setVisibility(true);
	textMission15->setVisibility(true);

	AudioPlayer::play(36, Global::gameCamera->getFadePosition1());
}

void MainMenu::selectMenuRoot(int newSelection)
{
	GuiManager::clearGuisToRender();
	GuiManager::addGuiToRender(item1); textItem1->getPosition()->y = 0.333f-0.04f;
	GuiManager::addGuiToRender(item2); textItem2->getPosition()->y = 0.333f-0.04f;
	GuiManager::addGuiToRender(item3); textItem3->getPosition()->y = 0.666f-0.04f;
	GuiManager::addGuiToRender(item4); textItem4->getPosition()->y = 0.666f-0.04f;

	switch (newSelection)
	{
		case ROOT_STORY:   GuiManager::addGuiToRender(itemBackdrop1); textItem1->getPosition()->y = 0.333f-0.06f; break;
		case ROOT_MISSION: GuiManager::addGuiToRender(itemBackdrop2); textItem2->getPosition()->y = 0.333f-0.06f; break;
		case ROOT_EXTRAS:  GuiManager::addGuiToRender(itemBackdrop3); textItem3->getPosition()->y = 0.666f-0.06f; break;
		case ROOT_EXIT:    GuiManager::addGuiToRender(itemBackdrop4); textItem4->getPosition()->y = 0.666f-0.06f; break;
		default: break;
	}

	menuSelectionID = newSelection;

	textItem1->setVisibility(true);
	textItem2->setVisibility(true);
	textItem3->setVisibility(true);
	textItem4->setVisibility(true);

	textMission1 ->setVisibility(false);
	textMission2 ->setVisibility(false);
	textMission3 ->setVisibility(false);
	textMission4 ->setVisibility(false);
	textMission5 ->setVisibility(false);
	textMission6 ->setVisibility(false);
	textMission7 ->setVisibility(false);
	textMission8 ->setVisibility(false);
	textMission9 ->setVisibility(false);
	textMission10->setVisibility(false);
	textMission11->setVisibility(false);
	textMission12->setVisibility(false);
	textMission13->setVisibility(false);
	textMission14->setVisibility(false);
	textMission15->setVisibility(false);

	AudioPlayer::play(36, Global::gameCamera->getFadePosition1());
}

void MainMenu::step()
{
	bool shouldGoUp    = false;
	bool shouldGoDown  = false;
	bool shouldGoLeft  = false;
	bool shouldGoRight = false;
	bool pressedSelect = (INPUT_JUMP && !INPUT_PREVIOUS_JUMP) || (INPUT_START && !INPUT_PREVIOUS_START);
	bool pressedBack   = (INPUT_ACTION && !INPUT_PREVIOUS_ACTION);

	int moveX = MENU_X;
	int moveY = MENU_Y;

	if (moveX != moveXPrevious)
	{
		if (moveX == 1)
		{
			shouldGoRight = true;
		}
		else if (moveX == -1)
		{
			shouldGoLeft = true;
		}
	}

	if (moveY != moveYPrevious)
	{
		if (moveY == -1)
		{
			shouldGoUp = true;
		}
		else if (moveY == 1)
		{
			shouldGoDown = true;
		}
	}

	moveXPrevious = moveX;
	moveYPrevious = moveY;

	if (MainMenu::titleCardTextTimer != 0)
	{
		if (MainMenu::titleCardTextTimer == 1)
		{
			if (textTitleCardLevelName != nullptr)
			{
				textTitleCardLevelName->deleteMe();
				delete textTitleCardLevelName; Global::countDelete++;
				textTitleCardLevelName = nullptr;
			}
			if (textTitleCardMission != nullptr)
			{
				textTitleCardMission->deleteMe();
				delete textTitleCardMission; Global::countDelete++;
				textTitleCardMission = nullptr;
			}
			if (textTitleCardMissionDescription != nullptr)
			{
				textTitleCardMissionDescription->deleteMe();
				delete textTitleCardMissionDescription; Global::countDelete++;
				textTitleCardMissionDescription = nullptr;
			}

			GuiManager::removeGui(GuiTextureResources::textureBlueLine);
		}

		MainMenu::titleCardTextTimer--;
	}


	if (Global::gameState == STATE_TITLE)
	{
		extern unsigned int SCR_WIDTH;
		float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension

		if (menuSelectionID >= ROOT_STORY && menuSelectionID <= ROOT_EXIT)
		{
			if (shouldGoUp)
			{
				switch (menuSelectionID)
				{
					case ROOT_EXTRAS: MainMenu::selectMenuRoot(ROOT_STORY);   break;
					case ROOT_EXIT:   MainMenu::selectMenuRoot(ROOT_MISSION); break;
					default: break;
				}
			}
			else if (shouldGoDown)
			{
				switch (menuSelectionID)
				{
					case ROOT_STORY:   MainMenu::selectMenuRoot(ROOT_EXTRAS); break;
					case ROOT_MISSION: MainMenu::selectMenuRoot(ROOT_EXIT);   break;
					default: break;
				}
			}
			else if (shouldGoLeft)
			{
				switch (menuSelectionID)
				{
					case ROOT_MISSION: MainMenu::selectMenuRoot(ROOT_STORY);  break;
					case ROOT_EXIT:    MainMenu::selectMenuRoot(ROOT_EXTRAS); break;
					default: break;
				}
			}
			else if (shouldGoRight)
			{
				switch (menuSelectionID)
				{
					case ROOT_STORY:  MainMenu::selectMenuRoot(ROOT_MISSION); break;
					case ROOT_EXTRAS: MainMenu::selectMenuRoot(ROOT_EXIT);    break;
					default: break;
				}
			}
			else if (pressedSelect)
			{
				switch (menuSelectionID)
				{
					case ROOT_STORY:
						Global::levelID = LVL_EC;
						Global::levelName = "EmeraldCoast.lvl";
						Global::levelNameDisplay = "Emerald Coast";
						Global::gameMissionNumber = 0;
						Global::gameMissionDescription = "Destroy the capsule and rescue the animals!";
						Global::isNewLevel = true;
						Global::shouldLoadLevel = true;
						MainMenu::unloadResources();
						MainMenu::createTitleCard();
						Global::gameState = STATE_RUNNING;
						break;

					case ROOT_MISSION:
						MainMenu::selectMenuMission(MISSION_1);
						break;

					case ROOT_EXTRAS:
						break;

					case ROOT_EXIT: 
						Global::gameState = STATE_EXITING;
						break;

					default: break;
				}
			}
		}
		else if (menuSelectionID >= MISSION_1 && menuSelectionID <= MISSION_15)
		{
			if (shouldGoUp)
			{
				if (menuSelectionID > MISSION_1)
				{
					MainMenu::selectMenuMission(menuSelectionID-1);
					Global::gameMissionNumber = 0;
					missionSelect->setX(0.75f-83*px);
				}
			}
			else if (shouldGoDown)
			{
				if (menuSelectionID < MISSION_15)
				{
					MainMenu::selectMenuMission(menuSelectionID+1);
					Global::gameMissionNumber = 0;
					missionSelect->setX(0.75f-83*px);
				}
			}
			else if (shouldGoLeft)
			{
				if (Global::gameMissionNumber > 0)
				{
					Global::gameMissionNumber--;
					missionSelect->setX(0.75f-83*px+(Global::gameMissionNumber*55)*px);
					AudioPlayer::play(37, Global::gameCamera->getFadePosition1());
				}
			}
			else if (shouldGoRight)
			{
				if (Global::gameMissionNumber < 3)
				{
					Global::gameMissionNumber++;
					missionSelect->setX(0.75f-83*px+(Global::gameMissionNumber*55)*px);
					AudioPlayer::play(37, Global::gameCamera->getFadePosition1());
				}
			}
			else if (pressedSelect)
			{
				switch (menuSelectionID)
				{
					case MISSION_1:
						Global::levelID = LVL_EC;
						Global::levelName = "EmeraldCoast.lvl";
						Global::levelNameDisplay = "Emerald Coast";

						Global::gameMissionDescription = "Destroy the capsule and rescue the animals!";
						break;

					case MISSION_2:
						Global::levelID = LVL_SH;
						Global::levelName = "NokiBay.lvl";
						Global::levelNameDisplay = "Speed Highway";
						Global::gameMissionDescription = "Destroy the capsule and rescue the animals!";
						break;

					case MISSION_3:
						Global::levelID = LVL_GHZ;
						Global::levelName = "DryLagoon.lvl";
						Global::levelNameDisplay = "Green Hill Zone";
						Global::gameMissionDescription = "Placeholder";
						break;

					case MISSION_4:
						Global::levelID = LVL_WI;
						Global::levelName = "KingdomValley.lvl";
						Global::levelNameDisplay = "Wuhu Island";
						Global::gameMissionDescription = "Do a lap around the island";
						break;

					case MISSION_5:
						Global::levelID = LVL_PC;
						Global::levelName = "DelfinoPlaza.lvl";
						Global::levelNameDisplay = "Peach's Castle";
						Global::gameMissionDescription = "Reach the tip top of the castle";
						break;

					case MISSION_6:
						Global::levelID = LVL_SHL;
						Global::levelName = "SunsetIsles.lvl";
						Global::levelNameDisplay = "Sand Hill";
						Global::gameMissionDescription = "Go fast";
						break;

					case MISSION_7:
						Global::levelID = LVL_KB;
						Global::levelName = "WildCanyon.lvl";
						Global::levelNameDisplay = "Koopa Beach";
						Global::gameMissionDescription = "Do a lap around the island";
						break;

					case MISSION_8:
						Global::levelID = LVL_OI;
						Global::levelName = "OutsetIsland.lvl";
						Global::levelNameDisplay = "Outset Island";
						Global::gameMissionDescription = "Find all the pieces of the Master Emerald!";
						break;

					case MISSION_9:
						Global::levelID = LVL_WB;
						Global::levelName = "WeaponsBed.lvl";
						Global::levelNameDisplay = "Weapons Bed";
						Global::gameMissionDescription = "Placeholder";
						break;

					case MISSION_10:
						Global::levelID = LVL_MH;
						Global::levelName = "MetalHarbor.lvl";
						Global::levelNameDisplay = "Metal Harbor";
						Global::gameMissionDescription = "Escape from the military base!";
						break;

					case MISSION_11:
						Global::levelID = LVL_BOB;
						Global::levelName = "BobOmbBattlefield.lvl";
						Global::levelNameDisplay = "Bob-omb Battlefield";
						Global::gameMissionDescription = "Find all the pieces";
						break;

					case MISSION_12:
						Global::levelID = LVL_RR;
						Global::levelName = "RainbowRoad.lvl";
						Global::levelNameDisplay = "Rainbow Road";
						Global::gameMissionDescription = "Go fast and don't hit walls";
						break;

					case MISSION_13:
						Global::levelID = LVL_SHD;
						Global::levelName = "Snowhead.lvl";
						Global::levelNameDisplay = "Snowhead";
						Global::gameMissionDescription = "Help the old goron dude find his son or something";
						break;

					case MISSION_14:
						Global::levelID = LVL_TP;
						Global::levelName = "TwinklePark.lvl";
						Global::levelNameDisplay = "Twinkle Park";
						Global::gameMissionDescription = "Destroy the capsule and rescue the animals!";
						break;

					case MISSION_15:
						Global::levelID = LVL_FF;
						Global::levelName = "FireField.lvl";
						Global::levelNameDisplay = "Fire Field";
						Global::gameMissionDescription = "Placeholder";
						break;

					default: break;
				}

				AudioPlayer::play(38, Global::gameCamera->getFadePosition1());

				if (Global::gameMissionNumber == 1)
				{
					Global::gameMissionDescription = "Collect 100 rings!";
				}
				else if (Global::gameMissionNumber == 2)
				{
					Global::gameMissionDescription = "Placeholder";
				}
				else if (Global::gameMissionNumber == 3)
				{
					Global::gameMissionDescription = "Placeholder";
				}

				Global::isNewLevel = true;
				Global::shouldLoadLevel = true;
				MainMenu::unloadResources();
				MainMenu::createTitleCard();
				Global::gameState = STATE_RUNNING;
			}
			else if (pressedBack)
			{
				MainMenu::selectMenuRoot(ROOT_MISSION);
			}
		}
	}
}

void MainMenu::createTitleCard()
{
	ParticleMaster::deleteAllParticles();

	Vector3f vel(0,0,0);
	new Particle(ParticleResources::textureBlackFade, Global::gameCamera->getFadePosition1(), &vel, 0, 60, 0.0f,  5.0f, 0, true);
	GuiManager::addGuiToRender(GuiTextureResources::textureBlueLine);


	if (textTitleCardLevelName != nullptr)
	{
		textTitleCardLevelName->deleteMe();
		delete textTitleCardLevelName;
		Global::countDelete++;
		textTitleCardLevelName = nullptr;
	}
	if (textTitleCardMission != nullptr)
	{
		textTitleCardMission->deleteMe();
		delete textTitleCardMission;
		Global::countDelete++;
		textTitleCardMission = nullptr;
	}
	if (textTitleCardMissionDescription != nullptr)
	{
		textTitleCardMissionDescription->deleteMe();
		delete textTitleCardMissionDescription;
		Global::countDelete++;
		textTitleCardMissionDescription = nullptr;
	}

	textTitleCardLevelName          = new GUIText(Global::levelNameDisplay, 3.0f, font, 0.0f, 0.6f, 1.0f, true, false, true); Global::countNew++;
	textTitleCardMission            = new GUIText("Mission "+std::to_string(Global::gameMissionNumber+1)+":", 2.5f, font, 0.0f, 0.7f, 1.0f, true, false, true); Global::countNew++;
	textTitleCardMissionDescription = new GUIText(Global::gameMissionDescription, 2.0f, font, 0.0f, 0.8f, 1.0f, true, false, true); Global::countNew++;

	MainMenu::titleCardTextTimer = 3;
}