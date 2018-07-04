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

GUIText* MainMenu::textMission1  = nullptr;//Emerald Coast;
GUIText* MainMenu::textMission2  = nullptr;//Dry Lagoon;
GUIText* MainMenu::textMission3  = nullptr;//Speed Highway;
GUIText* MainMenu::textMission4  = nullptr;//Twinkle Park;
GUIText* MainMenu::textMission5  = nullptr;//Wild Canyon;
GUIText* MainMenu::textMission6  = nullptr;//Metal Harbor;
GUIText* MainMenu::textMission7  = nullptr;//Delfino Plaza;
GUIText* MainMenu::textMission8  = nullptr;//Green Hill Zone;
GUIText* MainMenu::textMission9  = nullptr;//Noki Bay;
GUIText* MainMenu::textMission10 = nullptr;//Weapons Bed;
GUIText* MainMenu::textMission11 = nullptr;//Outset Island;
GUIText* MainMenu::textMission12 = nullptr;//Wuhu Island;
GUIText* MainMenu::textMission13 = nullptr;//Snowhead;
GUIText* MainMenu::textMission14 = nullptr;//Sand Hill;
GUIText* MainMenu::textMission15 = nullptr;//Rainbow Road;
GUIText* MainMenu::textMission16 = nullptr;//Peach's Castle;
GUIText* MainMenu::textMission17 = nullptr;//Koopa Beach;
GUIText* MainMenu::textMission18 = nullptr;//Fire Field;
GUIText* MainMenu::textMission19 = nullptr;//Bob-omb Battlefield;
GUIText* MainMenu::textMission20 = nullptr;//Kingdom Valley;
GUIText* MainMenu::textMission21 = nullptr;//Pumpkin Hill

GUIText* MainMenu::textTitleCardLevelName          = nullptr;
GUIText* MainMenu::textTitleCardMission            = nullptr;
GUIText* MainMenu::textTitleCardMissionDescription = nullptr;

GUIText* MainMenu::textItem1 = nullptr;
GUIText* MainMenu::textItem2 = nullptr;
GUIText* MainMenu::textItem3 = nullptr;
GUIText* MainMenu::textItem4 = nullptr;

GLuint MainMenu::textureParallelogram              = (GLuint)-1;
GLuint MainMenu::textureParallelogramBackdrop      = (GLuint)-1;
GLuint MainMenu::textureParallelogramHalf          = (GLuint)-1;
GLuint MainMenu::textureParallelogramHalfBackdrop  = (GLuint)-1;
GLuint MainMenu::textureParallelogramHalf2         = (GLuint)-1;
GLuint MainMenu::textureParallelogramHalf2Backdrop = (GLuint)-1;
GLuint MainMenu::textureRankA					   = (GLuint)-1;
GLuint MainMenu::textureRankB					   = (GLuint)-1;
GLuint MainMenu::textureRankC					   = (GLuint)-1;
GLuint MainMenu::textureRankD					   = (GLuint)-1;
GLuint MainMenu::textureRankE					   = (GLuint)-1;
GLuint MainMenu::textureRankBlank				   = (GLuint)-1;
GLuint MainMenu::textureMissionSelect			   = (GLuint)-1;

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
GuiTexture* MainMenu::itemMission16 = nullptr;
GuiTexture* MainMenu::itemMission17 = nullptr;
GuiTexture* MainMenu::itemMission18 = nullptr;
GuiTexture* MainMenu::itemMission19 = nullptr;
GuiTexture* MainMenu::itemMission20 = nullptr;
GuiTexture* MainMenu::itemMission21 = nullptr;
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
GuiTexture* MainMenu::itemMissionBackdrop16 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop17 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop18 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop19 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop20 = nullptr;
GuiTexture* MainMenu::itemMissionBackdrop21 = nullptr;

GuiTexture* MainMenu::itemRankDisplay          = nullptr;
GuiTexture* MainMenu::itemRankDisplayBackdrop  = nullptr;
GuiTexture* MainMenu::itemTimeDisplay          = nullptr;
GuiTexture* MainMenu::itemTimeDisplayBackdrop  = nullptr;
GuiTexture* MainMenu::itemScoreDisplay         = nullptr;
GuiTexture* MainMenu::itemScoreDisplayBackdrop = nullptr;

GUIText* MainMenu::textBestScore = nullptr;
GUIText* MainMenu::textBestTime  = nullptr;

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

	textureParallelogram              = Loader_loadTextureNoInterpolation("res/Images/MainMenu/Parallelogram.png");
	textureParallelogramBackdrop      = Loader_loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramBackdrop.png");
	textureParallelogramHalf          = Loader_loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramHalf.png");
	textureParallelogramHalfBackdrop  = Loader_loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramHalfBackdrop.png");
	textureParallelogramHalf2         = Loader_loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramHalf2.png");
	textureParallelogramHalf2Backdrop = Loader_loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramHalf2Backdrop.png");
	textureRankA					  = Loader_loadTexture               ("res/Images/MainMenu/RankA.png");
	textureRankB					  = Loader_loadTexture               ("res/Images/MainMenu/RankB.png");
	textureRankC					  = Loader_loadTexture               ("res/Images/MainMenu/RankC.png");
	textureRankD					  = Loader_loadTexture               ("res/Images/MainMenu/RankD.png");
	textureRankE					  = Loader_loadTexture               ("res/Images/MainMenu/RankE.png");
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

	textItem1 = new GUIText("ARCADE",   2.85f, font, 0.0f,   0.333f-0.04f, 0.666f, true, false, true); Global::countNew++;
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
	itemMission16 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission17 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission18 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission19 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission20 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMission21 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
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
	itemMissionBackdrop16 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop17 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop18 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop19 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop20 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;
	itemMissionBackdrop21 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024*px, 64*py, 0); Global::countNew++;

	itemRankDisplay          = new GuiTexture(textureParallelogram,              0.75f,             0.5f,        512*px,  64*py, 0); Global::countNew++;
	itemRankDisplayBackdrop  = new GuiTexture(textureParallelogramBackdrop,      0.75f+8*px,        0.5f+6*py,   512*px,  64*py, 0); Global::countNew++;
	itemTimeDisplay          = new GuiTexture(textureParallelogramHalf2,         0.75f+256*px,      0.5f+128*py, 1024*px, 64*py, 0); Global::countNew++;
	itemTimeDisplayBackdrop  = new GuiTexture(textureParallelogramHalf2Backdrop, 0.75f+256*px+8*px, 0.5f+134*py, 1024*px, 64*py, 0); Global::countNew++;
	itemScoreDisplay         = new GuiTexture(textureParallelogramHalf2,         0.75f+256*px,      0.5f+256*py, 1024*px, 64*py, 0); Global::countNew++;
	itemScoreDisplayBackdrop = new GuiTexture(textureParallelogramHalf2Backdrop, 0.75f+256*px+8*px, 0.5f+262*py, 1024*px, 64*py, 0); Global::countNew++;

	textBestScore = new GUIText("SCORE:",      2.0f, font, 0.75f-192*px, 0.5f+128*py-0.025f, 1-(0.75f-192*px), false, false, true); Global::countNew++;
	textBestTime  = new GUIText("TIME:",       2.0f, font, 0.75f-192*px, 0.5f+256*py-0.025f, 1-(0.75f-192*px), false, false, true); Global::countNew++;

	rankM1 = new GuiTexture(textureRankA, 0.75f-83*px, 0.5f, 64*px, 64*py, 0); Global::countNew++;
	rankM2 = new GuiTexture(textureRankB, 0.75f-28*px, 0.5f, 64*px, 64*py, 0); Global::countNew++;
	rankM3 = new GuiTexture(textureRankC, 0.75f+27*px, 0.5f, 64*px, 64*py, 0); Global::countNew++;
	rankM4 = new GuiTexture(textureRankD, 0.75f+82*px, 0.5f, 64*px, 64*py, 0); Global::countNew++;

	missionSelect = new GuiTexture(textureMissionSelect, 0.75f-83*px, 0.5f, 96*px, 96*py, 0); Global::countNew++;

	textMission1  = new GUIText("EMERALD COAST",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission2  = new GUIText("DRY LAGOON",          2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission3  = new GUIText("SPEED HIGHWAY",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission4  = new GUIText("TWINKLE PARK",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission5  = new GUIText("WILD CANYON",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission6  = new GUIText("METAL HARBOR",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission7  = new GUIText("DELFINO PLAZA",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission8  = new GUIText("GREEN HILL ZONE",     2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission9  = new GUIText("NOKI BAY",            2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission10 = new GUIText("WEAPONS BED",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission11 = new GUIText("OUTSET ISLAND",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission12 = new GUIText("WUHU ISLAND",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission13 = new GUIText("SNOWHEAD",            2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission14 = new GUIText("SAND HILL",           2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission15 = new GUIText("RAINBOW ROAD",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission16 = new GUIText("PEACH'S CASTLE",      2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission17 = new GUIText("KOOPA BEACH",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission18 = new GUIText("FIRE FIELD",          2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission19 = new GUIText("BOB-OMB BATTLEFIELD", 2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission20 = new GUIText("KINGDOM VALLEY",      2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;
	textMission21 = new GUIText("PUMPKIN HILL",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); Global::countNew++;

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
	textMission16->deleteMe(); delete textMission16; Global::countDelete++; textMission16 = nullptr;
	textMission17->deleteMe(); delete textMission17; Global::countDelete++; textMission17 = nullptr;
	textMission18->deleteMe(); delete textMission18; Global::countDelete++; textMission18 = nullptr;
	textMission19->deleteMe(); delete textMission19; Global::countDelete++; textMission19 = nullptr;
	textMission20->deleteMe(); delete textMission20; Global::countDelete++; textMission20 = nullptr;
	textMission21->deleteMe(); delete textMission21; Global::countDelete++; textMission21 = nullptr;

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
	delete itemMission16; Global::countDelete++; itemMission16 = nullptr;
	delete itemMission17; Global::countDelete++; itemMission17 = nullptr;
	delete itemMission18; Global::countDelete++; itemMission18 = nullptr;
	delete itemMission19; Global::countDelete++; itemMission19 = nullptr;
	delete itemMission20; Global::countDelete++; itemMission20 = nullptr;
	delete itemMission21; Global::countDelete++; itemMission21 = nullptr;
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
	delete itemMissionBackdrop16; Global::countDelete++; itemMissionBackdrop16 = nullptr;
	delete itemMissionBackdrop17; Global::countDelete++; itemMissionBackdrop17 = nullptr;
	delete itemMissionBackdrop18; Global::countDelete++; itemMissionBackdrop18 = nullptr;
	delete itemMissionBackdrop19; Global::countDelete++; itemMissionBackdrop19 = nullptr;
	delete itemMissionBackdrop20; Global::countDelete++; itemMissionBackdrop20 = nullptr;
	delete itemMissionBackdrop21; Global::countDelete++; itemMissionBackdrop21 = nullptr;

	delete itemRankDisplay;          Global::countDelete++; itemRankDisplay          = nullptr;
	delete itemRankDisplayBackdrop;  Global::countDelete++; itemRankDisplayBackdrop  = nullptr;
	delete itemTimeDisplay;          Global::countDelete++; itemTimeDisplay          = nullptr;
	delete itemTimeDisplayBackdrop;  Global::countDelete++; itemTimeDisplayBackdrop  = nullptr;
	delete itemScoreDisplay;         Global::countDelete++; itemScoreDisplay         = nullptr;
	delete itemScoreDisplayBackdrop; Global::countDelete++; itemScoreDisplayBackdrop = nullptr;

	textBestScore->deleteMe(); delete textBestScore; Global::countDelete++; textBestScore = nullptr;
	textBestTime ->deleteMe(); delete textBestTime;  Global::countDelete++; textBestTime  = nullptr;

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
	itemMission15->setY(yPos+offsetY); yPos+=128*py;
	itemMission16->setY(yPos+offsetY); yPos+=128*py;
	itemMission17->setY(yPos+offsetY); yPos+=128*py;
	itemMission18->setY(yPos+offsetY); yPos+=128*py;
	itemMission19->setY(yPos+offsetY); yPos+=128*py;
	itemMission20->setY(yPos+offsetY); yPos+=128*py;
	itemMission21->setY(yPos+offsetY);
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
	itemMissionBackdrop15->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop16->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop17->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop18->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop19->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop20->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop21->setY(yPos+offsetY);

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
	itemMission16->setX(0.5f-512*px-64*px);
	itemMission17->setX(0.5f-512*px-64*px);
	itemMission18->setX(0.5f-512*px-64*px);
	itemMission19->setX(0.5f-512*px-64*px);
	itemMission20->setX(0.5f-512*px-64*px);
	itemMission21->setX(0.5f-512*px-64*px);
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
	itemMissionBackdrop16->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop17->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop18->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop19->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop20->setX(0.5f-512*px-64*px+8*px);
	itemMissionBackdrop21->setX(0.5f-512*px-64*px+8*px);

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
	textMission15->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission16->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission17->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission18->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission19->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission20->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission21->getPosition()->y = yPos+offsetY;
	
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
	textMission16->getPosition()->x = 0.0f;
	textMission17->getPosition()->x = 0.0f;
	textMission18->getPosition()->x = 0.0f;
	textMission19->getPosition()->x = 0.0f;
	textMission20->getPosition()->x = 0.0f;
	textMission21->getPosition()->x = 0.0f;

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
	GuiManager::addGuiToRender(itemMission16);
	GuiManager::addGuiToRender(itemMission17);
	GuiManager::addGuiToRender(itemMission18);
	GuiManager::addGuiToRender(itemMission19);
	GuiManager::addGuiToRender(itemMission20);
	GuiManager::addGuiToRender(itemMission21);

	GuiManager::addGuiToRender(itemRankDisplay);
	GuiManager::addGuiToRender(itemRankDisplayBackdrop);
	GuiManager::addGuiToRender(itemTimeDisplay);
	GuiManager::addGuiToRender(itemTimeDisplayBackdrop);
	GuiManager::addGuiToRender(itemScoreDisplay);
	GuiManager::addGuiToRender(itemScoreDisplayBackdrop);

	int numMissions = Global::gameLevelData[newSelection].numMissions;
	switch (numMissions)
	{
		case 4: GuiManager::addGuiToRender(rankM4);
		case 3: GuiManager::addGuiToRender(rankM3);
		case 2: GuiManager::addGuiToRender(rankM2);
		case 1: GuiManager::addGuiToRender(rankM1);
		default: break;
	}

	if (numMissions >= 4)
	{
		std::string rank = "";
		rankM4->setTexture(textureRankBlank);
		if (Global::gameSaveData.find(Global::gameLevelData[newSelection].displayName+"_M4_RANK") != Global::gameSaveData.end())
		{
			rank = Global::gameSaveData[Global::gameLevelData[newSelection].displayName+"_M4_RANK"];
			if (rank == "A") rankM4->setTexture(textureRankA);
			if (rank == "B") rankM4->setTexture(textureRankB);
			if (rank == "C") rankM4->setTexture(textureRankC);
			if (rank == "D") rankM4->setTexture(textureRankD);
			if (rank == "E") rankM4->setTexture(textureRankE);
		}
	}
	if (numMissions >= 3)
	{
		std::string rank = "";
		rankM3->setTexture(textureRankBlank);
		if (Global::gameSaveData.find(Global::gameLevelData[newSelection].displayName+"_M3_RANK") != Global::gameSaveData.end())
		{
			rank = Global::gameSaveData[Global::gameLevelData[newSelection].displayName+"_M3_RANK"];
			if (rank == "A") rankM3->setTexture(textureRankA);
			if (rank == "B") rankM3->setTexture(textureRankB);
			if (rank == "C") rankM3->setTexture(textureRankC);
			if (rank == "D") rankM3->setTexture(textureRankD);
			if (rank == "E") rankM3->setTexture(textureRankE);
		}
	}
	if (numMissions >= 2)
	{
		std::string rank = "";
		rankM2->setTexture(textureRankBlank);
		if (Global::gameSaveData.find(Global::gameLevelData[newSelection].displayName+"_M2_RANK") != Global::gameSaveData.end())
		{
			rank = Global::gameSaveData[Global::gameLevelData[newSelection].displayName+"_M2_RANK"];
			if (rank == "A") rankM2->setTexture(textureRankA);
			if (rank == "B") rankM2->setTexture(textureRankB);
			if (rank == "C") rankM2->setTexture(textureRankC);
			if (rank == "D") rankM2->setTexture(textureRankD);
			if (rank == "E") rankM2->setTexture(textureRankE);
		}
	}
	if (numMissions >= 1)
	{
		std::string rank = "";
		rankM1->setTexture(textureRankBlank);
		if (Global::gameSaveData.find(Global::gameLevelData[newSelection].displayName+"_M1_RANK") != Global::gameSaveData.end())
		{
			rank = Global::gameSaveData[Global::gameLevelData[newSelection].displayName+"_M1_RANK"];
			if (rank == "A") rankM1->setTexture(textureRankA);
			if (rank == "B") rankM1->setTexture(textureRankB);
			if (rank == "C") rankM1->setTexture(textureRankC);
			if (rank == "D") rankM1->setTexture(textureRankD);
			if (rank == "E") rankM1->setTexture(textureRankE);
		}
	}

	GuiManager::addGuiToRender(missionSelect);

	switch (newSelection)
	{
		case MISSION_1 : textMission1 ->getPosition()->x += 64*px; itemMission1 ->setX(0.5f-512*px); itemMissionBackdrop1 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop1);  break;
		case MISSION_2 : textMission2 ->getPosition()->x += 64*px; itemMission2 ->setX(0.5f-512*px); itemMissionBackdrop2 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop2);  break;
		case MISSION_3 : textMission3 ->getPosition()->x += 64*px; itemMission3 ->setX(0.5f-512*px); itemMissionBackdrop3 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop3);  break;
		case MISSION_4 : textMission4 ->getPosition()->x += 64*px; itemMission4 ->setX(0.5f-512*px); itemMissionBackdrop4 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop4);  break;
		case MISSION_5 : textMission5 ->getPosition()->x += 64*px; itemMission5 ->setX(0.5f-512*px); itemMissionBackdrop5 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop5);  break;
		case MISSION_6 : textMission6 ->getPosition()->x += 64*px; itemMission6 ->setX(0.5f-512*px); itemMissionBackdrop6 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop6);  break;
		case MISSION_7 : textMission7 ->getPosition()->x += 64*px; itemMission7 ->setX(0.5f-512*px); itemMissionBackdrop7 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop7);  break;
		case MISSION_8 : textMission8 ->getPosition()->x += 64*px; itemMission8 ->setX(0.5f-512*px); itemMissionBackdrop8 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop8);  break;
		case MISSION_9 : textMission9 ->getPosition()->x += 64*px; itemMission9 ->setX(0.5f-512*px); itemMissionBackdrop9 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop9);  break;
		case MISSION_10: textMission10->getPosition()->x += 64*px; itemMission10->setX(0.5f-512*px); itemMissionBackdrop10->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop10); break;
		case MISSION_11: textMission11->getPosition()->x += 64*px; itemMission11->setX(0.5f-512*px); itemMissionBackdrop11->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop11); break;
		case MISSION_12: textMission12->getPosition()->x += 64*px; itemMission12->setX(0.5f-512*px); itemMissionBackdrop12->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop12); break;
		case MISSION_13: textMission13->getPosition()->x += 64*px; itemMission13->setX(0.5f-512*px); itemMissionBackdrop13->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop13); break;
		case MISSION_14: textMission14->getPosition()->x += 64*px; itemMission14->setX(0.5f-512*px); itemMissionBackdrop14->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop14); break;
		case MISSION_15: textMission15->getPosition()->x += 64*px; itemMission15->setX(0.5f-512*px); itemMissionBackdrop15->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop15); break;
		case MISSION_16: textMission16->getPosition()->x += 64*px; itemMission16->setX(0.5f-512*px); itemMissionBackdrop16->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop16); break;
		case MISSION_17: textMission17->getPosition()->x += 64*px; itemMission17->setX(0.5f-512*px); itemMissionBackdrop17->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop17); break;
		case MISSION_18: textMission18->getPosition()->x += 64*px; itemMission18->setX(0.5f-512*px); itemMissionBackdrop18->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop18); break;
		case MISSION_19: textMission19->getPosition()->x += 64*px; itemMission19->setX(0.5f-512*px); itemMissionBackdrop19->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop19); break;
		case MISSION_20: textMission20->getPosition()->x += 64*px; itemMission20->setX(0.5f-512*px); itemMissionBackdrop20->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop20); break;
		case MISSION_21: textMission21->getPosition()->x += 64*px; itemMission21->setX(0.5f-512*px); itemMissionBackdrop21->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop21); break;
		default: break;
	}

	menuSelectionID = newSelection;

	MainMenu::updateBestDisplay(newSelection);

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
	textMission16->setVisibility(true);
	textMission17->setVisibility(true);
	textMission18->setVisibility(true);
	textMission19->setVisibility(true);
	textMission20->setVisibility(true);
	textMission21->setVisibility(true);

	textBestScore->setVisibility(true);
	textBestTime ->setVisibility(true);

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
	textMission16->setVisibility(false);
	textMission17->setVisibility(false);
	textMission18->setVisibility(false);
	textMission19->setVisibility(false);
	textMission20->setVisibility(false);
	textMission21->setVisibility(false);

	textBestScore->setVisibility(false);
	textBestTime ->setVisibility(false);

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
					{
						Global::levelID = LVL_EMERALD_COAST;
						Global::gameMissionNumber = 0;

						AudioPlayer::play(38, Global::gameCamera->getFadePosition1());

						Level* currentLevel = &Global::gameLevelData[Global::levelID];
						Global::levelName = currentLevel->fileName;
						Global::levelNameDisplay = currentLevel->displayName;
						Global::gameMissionDescription = (currentLevel->missionData[Global::gameMissionNumber])[(currentLevel->missionData[Global::gameMissionNumber]).size()-1];

						Global::isNewLevel = true;
						Global::shouldLoadLevel = true;
						MainMenu::unloadResources();
						MainMenu::createTitleCard();
						Global::gameState = STATE_RUNNING;
						break;
					}

					case ROOT_MISSION:
					{
						MainMenu::selectMenuMission(MISSION_1);
						break;
					}

					case ROOT_EXTRAS:
					{
						break;
					}

					case ROOT_EXIT: 
					{
						Global::gameState = STATE_EXITING;
						break;
					}

					default: break;
				}
			}
		}
		else if (menuSelectionID >= MISSION_1 && menuSelectionID <= MISSION_MAX)
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
				if (menuSelectionID < MISSION_MAX)
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
					MainMenu::updateBestDisplay(menuSelectionID);
					AudioPlayer::play(37, Global::gameCamera->getFadePosition1());
				}
			}
			else if (shouldGoRight)
			{
				int maxMissionCount = Global::gameLevelData[menuSelectionID].numMissions;
				if (Global::gameMissionNumber < maxMissionCount-1)
				{
					Global::gameMissionNumber++;
					missionSelect->setX(0.75f-83*px+(Global::gameMissionNumber*55)*px);
					MainMenu::updateBestDisplay(menuSelectionID);
					AudioPlayer::play(37, Global::gameCamera->getFadePosition1());
				}
			}
			else if (pressedSelect)
			{
				switch (menuSelectionID)
				{
					case MISSION_1:  Global::levelID = LVL_EMERALD_COAST;      break;
					case MISSION_2:  Global::levelID = LVL_DRY_LAGOON;         break;
					case MISSION_3:  Global::levelID = LVL_SPEED_HIGHWAY;      break;
					case MISSION_4:  Global::levelID = LVL_TWINKLE_PARK;       break;
					case MISSION_5:  Global::levelID = LVL_WILD_CANYON;        break;
					case MISSION_6:  Global::levelID = LVL_METAL_HARBOR;       break;
					case MISSION_7:  Global::levelID = LVL_DELFINO_PLAZA;      break;
					case MISSION_8:  Global::levelID = LVL_GREEN_HILL_ZONE;    break;
					case MISSION_9:  Global::levelID = LVL_NOKI_BAY;           break;
					case MISSION_10: Global::levelID = LVL_WEAPONS_BED;        break;
					case MISSION_11: Global::levelID = LVL_OUTSET_ISLAND;      break;
					case MISSION_12: Global::levelID = LVL_WUHU_ISLAND;        break;
					case MISSION_13: Global::levelID = LVL_SNOWHEAD;           break;
					case MISSION_14: Global::levelID = LVL_SAND_HILL;          break;
					case MISSION_15: Global::levelID = LVL_RAINBOW_ROAD;       break;
					case MISSION_16: Global::levelID = LVL_PEACHS_CASTLE;      break;
					case MISSION_17: Global::levelID = LVL_KOOPA_BEACH;        break;
					case MISSION_18: Global::levelID = LVL_FIRE_FIELD;         break;
					case MISSION_19: Global::levelID = LVL_BOBOMB_BATTLEFIELD; break;
					case MISSION_20: Global::levelID = LVL_KINGDOM_VALLEY;     break;
					case MISSION_21: Global::levelID = LVL_PUMPKIN_HILL;       break;
					default:                                                   break;
				}

				AudioPlayer::play(38, Global::gameCamera->getFadePosition1());

				Level* currentLevel = &Global::gameLevelData[Global::levelID];
				Global::levelName = currentLevel->fileName;
				Global::levelNameDisplay = currentLevel->displayName;
				Global::gameMissionDescription = (currentLevel->missionData[Global::gameMissionNumber])[(currentLevel->missionData[Global::gameMissionNumber]).size()-1];

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

std::string MainMenu::convertFramesToTime(int frames)
{
	int min = frames/3600;
	int sec = (frames/60) % 60;
	int cen = frames % 60;

	std::string partMin = std::to_string(min);
	if (min < 10)
	{
		partMin = "0" + std::to_string(min);
	}
	std::string partSec = std::to_string(sec);
	if (sec < 10)
	{
		partSec = "0" + std::to_string(sec);
	}
	std::string partCen = std::to_string(((cen * 100) / 60));
	if ((cen * 100) / 60 < 10)
	{
		partCen = "0" + std::to_string(((cen * 100) / 60));
	}
	std::string timer = partMin + ":" + partSec + "." + partCen;

	return timer;
}

void MainMenu::updateBestDisplay(int levelID)
{
	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;
	float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension
	float py = 1.0f/(SCR_HEIGHT); //1 pixel in y dimension

	std::string missionTimeString  = "ERROR";
	std::string missionScoreString = "ERROR";
	switch (Global::gameMissionNumber)
	{
		case 0: missionTimeString = "_M1_TIME"; missionScoreString = "_M1_SCORE"; break;
		case 1: missionTimeString = "_M2_TIME"; missionScoreString = "_M2_SCORE"; break;
		case 2: missionTimeString = "_M3_TIME"; missionScoreString = "_M3_SCORE"; break;
		case 3: missionTimeString = "_M4_TIME"; missionScoreString = "_M4_SCORE"; break;
		default: break;
	}

	if (Global::gameSaveData.find(Global::gameLevelData[levelID].displayName+missionTimeString) != Global::gameSaveData.end())
	{
		std::string time = Global::gameSaveData[Global::gameLevelData[levelID].displayName+missionTimeString];
		time = MainMenu::convertFramesToTime(std::stoi(time));
		textBestTime->deleteMe(); delete textBestTime; Global::countDelete++;
		textBestTime  = new GUIText("TIME: "+time, 2.0f, font, 0.75f-192*px, 0.5f+256*py-0.025f, 1-(0.75f-192*px), false, false, true); Global::countNew++;
	}
	else
	{
		textBestTime->deleteMe(); delete textBestTime; Global::countDelete++;
		textBestTime  = new GUIText("TIME: ", 2.0f, font, 0.75f-192*px, 0.5f+256*py-0.025f, 1-(0.75f-192*px), false, false, true); Global::countNew++;
	}

	if (Global::gameSaveData.find(Global::gameLevelData[levelID].displayName+missionScoreString) != Global::gameSaveData.end())
	{
		std::string score = Global::gameSaveData[Global::gameLevelData[levelID].displayName+missionScoreString];
		textBestScore->deleteMe(); delete textBestScore; Global::countDelete++;
		textBestScore = new GUIText("SCORE: "+score, 2.0f, font, 0.75f-192*px, 0.5f+128*py-0.025f, 1-(0.75f-192*px), false, false, true); Global::countNew++;
	}
	else
	{
		textBestScore->deleteMe(); delete textBestScore; Global::countDelete++;
		textBestScore = new GUIText("SCORE: ", 2.0f, font, 0.75f-192*px, 0.5f+128*py-0.025f, 1-(0.75f-192*px), false, false, true); Global::countNew++;
	}
}