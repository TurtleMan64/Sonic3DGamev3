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
GUIText* MainMenu::textMission22 = nullptr;//Radical Highway

GUIText* MainMenu::textTitleCardLevelName          = nullptr;
GUIText* MainMenu::textTitleCardMission            = nullptr;
GUIText* MainMenu::textTitleCardMissionDescription = nullptr;

GUIText* MainMenu::textItem1 = nullptr;
GUIText* MainMenu::textItem2 = nullptr;
GUIText* MainMenu::textItem3 = nullptr;
GUIText* MainMenu::textItem4 = nullptr;

GUIText* MainMenu::textExtra1Title = nullptr; //Number of A ranks
GUIText* MainMenu::textExtra1Data  = nullptr;
GUIText* MainMenu::textExtra2Title = nullptr; //Number of NPC found
GUIText* MainMenu::textExtra2Data  = nullptr;
GUIText* MainMenu::textExtra3Title = nullptr; //Total playtime
GUIText* MainMenu::textExtra3Data  = nullptr;
GUIText* MainMenu::textExtra4Title = nullptr; //Best Arcade Clear Time
GUIText* MainMenu::textExtra4Data  = nullptr;
GUIText* MainMenu::textExtra5Title = nullptr; //Character selection
GUIText* MainMenu::textExtra5Data  = nullptr;

GUIText* MainMenu::textArcadeResultTitle = nullptr; //Total time during arcade mode
GUIText* MainMenu::textArcadeResultData  = nullptr; //Total time during arcade mode

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

GLuint MainMenu::textureNPCicon                    = (GLuint)-1;

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
GuiTexture* MainMenu::itemMission22 = nullptr;
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
GuiTexture* MainMenu::itemMissionBackdrop22 = nullptr;

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

GuiTexture* MainMenu::npcIcon = nullptr;

std::vector<std::string> MainMenu::unlockedCharacters;
int MainMenu::characterSelectIndex = 0;

int MainMenu::titleCardTextTimer = 0;

int MainMenu::holdUpTimer = 0;
int MainMenu::holdDownTimer = 0;

FontType* MainMenu::font = nullptr;

extern InputStruct Inputs;

void MainMenu::init()
{
	font = new FontType(Loader::loadTexture("res/Fonts/vipnagorgialla.png"), "res/Fonts/vipnagorgialla.fnt"); INCR_NEW

	MainMenu::titleCardTextTimer = 0;
	
	textureParallelogram              = Loader::loadTextureNoInterpolation("res/Images/MainMenu/Parallelogram.png");
	textureParallelogramBackdrop      = Loader::loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramBackdrop.png");
	textureParallelogramHalf          = Loader::loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramHalf.png");
	textureParallelogramHalfBackdrop  = Loader::loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramHalfBackdrop.png");
	textureParallelogramHalf2         = Loader::loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramHalf2.png");
	textureParallelogramHalf2Backdrop = Loader::loadTextureNoInterpolation("res/Images/MainMenu/ParallelogramHalf2Backdrop.png");
	textureRankA					  = Loader::loadTexture               ("res/Images/MainMenu/RankA.png");
	textureRankB					  = Loader::loadTexture               ("res/Images/MainMenu/RankB.png");
	textureRankC					  = Loader::loadTexture               ("res/Images/MainMenu/RankC.png");
	textureRankD					  = Loader::loadTexture               ("res/Images/MainMenu/RankD.png");
	textureRankE					  = Loader::loadTexture               ("res/Images/MainMenu/RankE.png");
	textureRankBlank				  = Loader::loadTextureNoInterpolation("res/Images/MainMenu/NoRank.png");
	textureMissionSelect			  = Loader::loadTextureNoInterpolation("res/Images/MainMenu/MissionSelect.png");
	textureNPCicon                    = Loader::loadTexture               ("res/Images/MainMenu/NPCicon.png");

	Global::npcList.push_back("Emerald Coast_NPC_1");
	Global::npcList.push_back("Emerald Coast_NPC_2");
	Global::npcList.push_back("Emerald Coast_NPC_3");
	Global::npcList.push_back("Speed Highway_NPC_1");
	Global::npcList.push_back("Speed Highway_NPC_2");
	Global::npcList.push_back("Speed Highway_NPC_3");
	Global::npcList.push_back("Twinkle Park_NPC_1");
	Global::npcList.push_back("Twinkle Park_NPC_2");
	Global::npcList.push_back("Metal Harbor_NPC_1");
	Global::npcList.push_back("Metal Harbor_NPC_2");
	Global::npcList.push_back("Delfino Plaza_NPC_1");
	Global::npcList.push_back("Outset Island_NPC_1");
	Global::npcList.push_back("Wuhu Island_NPC_1");
	Global::npcList.push_back("Wuhu Island_NPC_2");
	Global::npcList.push_back("Wuhu Island_NPC_3");
	Global::npcList.push_back("Wuhu Island_NPC_4");
	Global::npcList.push_back("Snowhead_NPC_1");
	Global::npcList.push_back("Snowhead_NPC_2");
	Global::npcList.push_back("Snowhead_NPC_3");
	Global::npcList.push_back("Snowhead_NPC_4");
	Global::npcList.push_back("Snowhead_NPC_5");
	Global::npcList.push_back("Snowhead_NPC_6");
	Global::npcList.push_back("Green Hill Zone_NPC_1");
	Global::npcList.push_back("Radical Highway_NPC_1");
	Global::npcList.push_back("Radical Highway_NPC_2");

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

	float fontScale = 2.85f;
	/*
	if (SCR_HEIGHT > 900)
	{
		fontScale = 2.55f;
	}
	*/

	float parallelogramXScale = 0.43f;
	float parallelogramYScale = 0.071f;
	float menuOffset = (SCR_HEIGHT * (4.0f / 3.0f)) / SCR_WIDTH;

	textItem1 = new GUIText("ARCADE",   fontScale, font, -0.25f*menuOffset,   0.333f-0.04f, 1.0f, true, false, true); INCR_NEW
	textItem2 = new GUIText("MISSIONS", fontScale, font, 0.25f*menuOffset, 0.333f-0.04f, 1.0f, true, false, true); INCR_NEW
	textItem3 = new GUIText("EXTRAS",   fontScale, font, -0.25f*menuOffset,   0.666f-0.04f, 1.0f, true, false, true); INCR_NEW
	textItem4 = new GUIText("EXIT",     fontScale, font, 0.25f*menuOffset, 0.666f-0.04f, 1.0f, true, false, true); INCR_NEW

	item1 = new GuiTexture(textureParallelogram, 0.5f - 0.25f*menuOffset, 0.333f, parallelogramXScale * menuOffset, parallelogramYScale, 0); INCR_NEW
	item2 = new GuiTexture(textureParallelogram, 0.5f + 0.25f*menuOffset, 0.333f, parallelogramXScale * menuOffset, parallelogramYScale, 0); INCR_NEW
	item3 = new GuiTexture(textureParallelogram, 0.5f - 0.25f*menuOffset, 0.666f, parallelogramXScale * menuOffset, parallelogramYScale, 0); INCR_NEW
	item4 = new GuiTexture(textureParallelogram, 0.5f + 0.25f*menuOffset, 0.666f, parallelogramXScale * menuOffset, parallelogramYScale, 0); INCR_NEW
	itemBackdrop1 = new GuiTexture(textureParallelogramBackdrop, 0.5f - 0.245f*menuOffset, 0.340f, parallelogramXScale * menuOffset, parallelogramYScale, 0); INCR_NEW
	itemBackdrop2 = new GuiTexture(textureParallelogramBackdrop, 0.5f + 0.255f*menuOffset, 0.340f, parallelogramXScale * menuOffset, parallelogramYScale, 0); INCR_NEW
	itemBackdrop3 = new GuiTexture(textureParallelogramBackdrop, 0.5f - 0.245f*menuOffset, 0.673f, parallelogramXScale * menuOffset, parallelogramYScale, 0); INCR_NEW
	itemBackdrop4 = new GuiTexture(textureParallelogramBackdrop, 0.5f + 0.255f*menuOffset, 0.673f, parallelogramXScale * menuOffset, parallelogramYScale, 0); INCR_NEW

	itemMission1  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024*px, 64*py, 0); INCR_NEW
	itemMission2  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission3  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission4  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission5  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission6  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission7  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission8  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission9  = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission10 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission11 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission12 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission13 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission14 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission15 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission16 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission17 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission18 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission19 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission20 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission21 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMission22 = new GuiTexture(textureParallelogramHalf, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop1  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop2  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop3  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop4  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop5  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop6  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop7  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop8  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop9  = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop10 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop11 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop12 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop13 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop14 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop15 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop16 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop17 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop18 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop19 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop20 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop21 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW
	itemMissionBackdrop22 = new GuiTexture(textureParallelogramHalfBackdrop, 0.0f, 0.0f, 1024 * px, 64 * py, 0); INCR_NEW

	itemRankDisplay          = new GuiTexture(textureParallelogram,              0.75f,             0.5f,        512*px,  64*py, 0); INCR_NEW
	itemRankDisplayBackdrop  = new GuiTexture(textureParallelogramBackdrop,      0.75f+8*px,        0.5f+6*py,   512*px,  64*py, 0); INCR_NEW
	itemTimeDisplay          = new GuiTexture(textureParallelogramHalf2,         0.75f+256*px,      0.5f+128*py, 1024*px, 64*py, 0); INCR_NEW
	itemTimeDisplayBackdrop  = new GuiTexture(textureParallelogramHalf2Backdrop, 0.75f+256*px+8*px, 0.5f+134*py, 1024*px, 64*py, 0); INCR_NEW
	itemScoreDisplay         = new GuiTexture(textureParallelogramHalf2,         0.75f+256*px,      0.5f+256*py, 1024*px, 64*py, 0); INCR_NEW
	itemScoreDisplayBackdrop = new GuiTexture(textureParallelogramHalf2Backdrop, 0.75f+256*px+8*px, 0.5f+262*py, 1024*px, 64*py, 0); INCR_NEW

	textBestScore = new GUIText("SCORE:",      2.0f, font, 0.75f-192*px, 0.5f+128*py-0.025f, 1-(0.75f-192*px), false, false, true); INCR_NEW
	textBestTime  = new GUIText("TIME:",       2.0f, font, 0.75f-192*px, 0.5f+256*py-0.025f, 1-(0.75f-192*px), false, false, true); INCR_NEW

	rankM1 = new GuiTexture(textureRankA, 0.75f-83*px, 0.5f, 64*px, 64*py, 0); INCR_NEW
	rankM2 = new GuiTexture(textureRankB, 0.75f-28*px, 0.5f, 64*px, 64*py, 0); INCR_NEW
	rankM3 = new GuiTexture(textureRankC, 0.75f+27*px, 0.5f, 64*px, 64*py, 0); INCR_NEW
	rankM4 = new GuiTexture(textureRankD, 0.75f+82*px, 0.5f, 64*px, 64*py, 0); INCR_NEW

	missionSelect = new GuiTexture(textureMissionSelect, 0.75f-83*px, 0.5f, 96*px, 96*py, 0); INCR_NEW

	npcIcon = new GuiTexture(textureNPCicon, 0.75f + 320*px, 0.5f, 128*px, 128*py, 0); INCR_NEW
		//TODO: make these text load from the Global::gameLevelData
	textMission1  = new GUIText("EMERALD COAST",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission2  = new GUIText("DRY LAGOON",          2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission3  = new GUIText("SPEED HIGHWAY",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission4  = new GUIText("TWINKLE PARK",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission5  = new GUIText("WILD CANYON",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission6  = new GUIText("METAL HARBOR",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission7  = new GUIText("DELFINO PLAZA",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission8  = new GUIText("GREEN HILL ZONE",     2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission9  = new GUIText("NOKI BAY",            2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission10 = new GUIText("WEAPONS BED",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission11 = new GUIText("OUTSET ISLAND",       2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission12 = new GUIText("WUHU ISLAND",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission13 = new GUIText("SNOWHEAD",            2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission14 = new GUIText("SAND HILL",           2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission15 = new GUIText("RAINBOW ROAD",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission16 = new GUIText("PEACH'S CASTLE",      2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission17 = new GUIText("KOOPA BEACH",         2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission18 = new GUIText("FIRE FIELD",          2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission19 = new GUIText("BOB-OMB BATTLEFIELD", 2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission20 = new GUIText("KINGDOM VALLEY",      2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission21 = new GUIText("PUMPKIN HILL",        2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW
	textMission22 = new GUIText("RADICAL HIGHWAY",     2.0f, font, 0.0f, 0.0f, 0.5f-128*px, false, true, true); INCR_NEW

	int totalRanks = 0;
	int rankAs = 0;
	for (unsigned int i = 0; i < Global::gameLevelData.size(); i++)
	{
		Level* level = &Global::gameLevelData[i];
		int missionCount = level->numMissions;
		totalRanks += missionCount;

		std::string name = level->displayName;
		auto end = Global::gameSaveData.end();

		switch (missionCount)
		{
			case 4: if (Global::gameSaveData.find(name+"_M4_RANK") != end) if (Global::gameSaveData[name+"_M4_RANK"] == "A") rankAs++;
			case 3: if (Global::gameSaveData.find(name+"_M3_RANK") != end) if (Global::gameSaveData[name+"_M3_RANK"] == "A") rankAs++;
			case 2: if (Global::gameSaveData.find(name+"_M2_RANK") != end) if (Global::gameSaveData[name+"_M2_RANK"] == "A") rankAs++;
			case 1: if (Global::gameSaveData.find(name+"_M1_RANK") != end) if (Global::gameSaveData[name+"_M1_RANK"] == "A") rankAs++;
			default: break;
		}
	}

	unsigned int totalNPC = (unsigned int)Global::npcList.size();
	unsigned int foundNPC = 0;
	for (unsigned int i = 0; i < totalNPC; i++)
	{
		std::string npc = Global::npcList[i];
		auto end = Global::gameSaveData.end();

		if (Global::gameSaveData.find(npc) != end)
		{
			if (Global::gameSaveData[npc] == "true")
			{
				foundNPC++;
			}
		}
	}

	if (Global::gameSaveData.find("BestArcadeClearTime") != Global::gameSaveData.end())
	{
		if (Global::gameSaveData.find("UnlockedAmy") == Global::gameSaveData.end())
		{
			Global::gameSaveData["UnlockedAmy"] = "true";
			Global::saveSaveData();
		}
	}
	if (foundNPC >= totalNPC/2)
	{
		if (Global::gameSaveData.find("UnlockedPacman") == Global::gameSaveData.end())
		{
			Global::gameSaveData["UnlockedPacman"] = "true";
			Global::saveSaveData();
		}
	}
	if (rankAs == totalRanks)
	{
		if (Global::gameSaveData.find("UnlockedMetalSonic") == Global::gameSaveData.end())
		{
			Global::gameSaveData["UnlockedMetalSonic"] = "true";
			Global::saveSaveData();
		}
	}
	if (foundNPC == totalNPC)
	{
		if (Global::gameSaveData.find("UnlockedNPC") == Global::gameSaveData.end())
		{
			Global::gameSaveData["UnlockedNPC"] = "true";
			Global::saveSaveData();
		}
	}



	std::string playtime = "";
	int hrs = (Global::gameTotalPlaytime         )/216000;
	int min = (Global::gameTotalPlaytime % 216000)/3600;
	int sec = (Global::gameTotalPlaytime % 3600  )/60;
	int frm = (Global::gameTotalPlaytime % 60    )/1;
	frm = (frm * 100) / 60;

	playtime += std::to_string(hrs)+" HOURS, ";
	playtime += std::to_string(min)+" MINUTES, ";
	playtime += std::to_string(sec)+"."+std::to_string(frm)+" SECONDS";

	const float yoff = -0.03f;

	float divisor = 5.0f;

	unlockedCharacters.clear();
	unlockedCharacters.push_back("SONIC");

	if (Global::gameSaveData.find("UnlockedAmy")        != Global::gameSaveData.end() ||
		Global::gameSaveData.find("UnlockedMetalSonic") != Global::gameSaveData.end() ||
		Global::gameSaveData.find("UnlockedPacman")     != Global::gameSaveData.end() ||
		Global::gameSaveData.find("UnlockedNPC")        != Global::gameSaveData.end())
	{
		divisor = 6.0f;

		if (Global::gameSaveData.find("UnlockedAmy")        != Global::gameSaveData.end()) unlockedCharacters.push_back("AMY");
		if (Global::gameSaveData.find("UnlockedMetalSonic") != Global::gameSaveData.end()) unlockedCharacters.push_back("METAL SONIC");
		if (Global::gameSaveData.find("UnlockedPacman")     != Global::gameSaveData.end()) unlockedCharacters.push_back("PAC-MAN");
		if (Global::gameSaveData.find("UnlockedNPC")        != Global::gameSaveData.end()) unlockedCharacters.push_back("NPC");
	}

	characterSelectIndex = std::max(0, characterSelectIndex);
	characterSelectIndex = std::min(characterSelectIndex, (int)unlockedCharacters.size()-1);

	textExtra1Title = new GUIText("A RANK:",         2, font, 0, (1/divisor)+yoff, 1, true, false, false); INCR_NEW
	textExtra2Title = new GUIText("HIDDEN NPC:",     2, font, 0, (2/divisor)+yoff, 1, true, false, false); INCR_NEW
	textExtra3Title = new GUIText("TOTAL PLAYTIME:", 2, font, 0, (3/divisor)+yoff, 1, true, false, false); INCR_NEW

	textExtra1Data = new GUIText(std::to_string(rankAs)  +"/"+std::to_string(totalRanks), 2, font, 0, (1/divisor)-yoff, 1, true, false, false); INCR_NEW //Number of A ranks
	textExtra2Data = new GUIText(std::to_string(foundNPC)+"/"+std::to_string(totalNPC),   2, font, 0, (2/divisor)-yoff, 1, true, false, false); INCR_NEW //Number of NPC found
	textExtra3Data = new GUIText(playtime, 2, font, 0, (3/divisor)-yoff, 1, true, false, false); INCR_NEW //Total playtime

	if (Global::gameSaveData.find("BestArcadeClearTime") == Global::gameSaveData.end())
	{
		textExtra4Title = new GUIText("BEST ARCADE CLEAR TIME:", 2, font, 0, (4/divisor)+yoff, 1, true, false, false); INCR_NEW
		textExtra4Data  = new GUIText("NONE", 2, font, 0, (4/divisor)-yoff, 1, true, false, false); INCR_NEW
	}
	else
	{
		textExtra4Title = new GUIText("BEST ARCADE CLEAR TIME:", 2, font, 0, (4/divisor)+yoff, 1, true, false, false); INCR_NEW
		textExtra4Data  = new GUIText(MainMenu::convertFramesToTime(stoi(Global::gameSaveData["BestArcadeClearTime"])), 2, font, 0, (4/divisor)-yoff, 1, true, false, false); INCR_NEW
	}

	if (divisor > 5.5f)
	{
		textExtra5Title = new GUIText("PLAY AS:", 2, font, 0, (5/divisor)+yoff, 1, true, false, false); INCR_NEW
		textExtra5Data  = new GUIText(unlockedCharacters[characterSelectIndex], 2, font, 0, (5/divisor)-yoff, 1, true, false, false); INCR_NEW
	}
	else
	{
		textExtra5Title = new GUIText("", 2, font, 0, (5/divisor)+yoff, 1, true, false, false); INCR_NEW
		textExtra5Data  = new GUIText("", 2, font, 0, (5/divisor)-yoff, 1, true, false, false); INCR_NEW
	}

	textArcadeResultTitle = new GUIText("ARCADE CLEAR TIME:", 3, font, 0, 0.5f-0.09f, 1, true, false, false); INCR_NEW
	textArcadeResultData  = new GUIText(MainMenu::convertFramesToTime(Global::gameArcadePlaytime), 3, font, 0, 0.5f, 1, true, false, false); INCR_NEW

	if (menuSelectionID <= MISSION_MAX)
	{
		MainMenu::selectMenuMission(menuSelectionID);
		missionSelect->setX(0.75f-83*px+(Global::gameMissionNumber*55)*px);
		MainMenu::updateBestDisplay(menuSelectionID);
	}
	else if (menuSelectionID <= ROOT_EXIT)
	{
		MainMenu::selectMenuRoot(menuSelectionID);
	}
	else if (menuSelectionID == EXTRAS)
	{
		MainMenu::selectMenuExtra();
	}
	else if (menuSelectionID == ARCADE_CLEAR)
	{
		MainMenu::selectMenuArcadeClear();
	}
}

void MainMenu::unloadResources()
{
	if (textItem1 == nullptr)
	{
		std::fprintf(stdout, "Main Menu trying to unload resources when they are already unloaded!\n");
		return;
	}

	textItem1->deleteMe(); delete textItem1; INCR_DEL textItem1 = nullptr;
	textItem2->deleteMe(); delete textItem2; INCR_DEL textItem2 = nullptr;
	textItem3->deleteMe(); delete textItem3; INCR_DEL textItem3 = nullptr;
	textItem4->deleteMe(); delete textItem4; INCR_DEL textItem4 = nullptr;

	textMission1 ->deleteMe(); delete textMission1;  INCR_DEL textMission1  = nullptr;
	textMission2 ->deleteMe(); delete textMission2;  INCR_DEL textMission2  = nullptr;
	textMission3 ->deleteMe(); delete textMission3;  INCR_DEL textMission3  = nullptr;
	textMission4 ->deleteMe(); delete textMission4;  INCR_DEL textMission4  = nullptr;
	textMission5 ->deleteMe(); delete textMission5;  INCR_DEL textMission5  = nullptr;
	textMission6 ->deleteMe(); delete textMission6;  INCR_DEL textMission6  = nullptr;
	textMission7 ->deleteMe(); delete textMission7;  INCR_DEL textMission7  = nullptr;
	textMission8 ->deleteMe(); delete textMission8;  INCR_DEL textMission8  = nullptr;
	textMission9 ->deleteMe(); delete textMission9;  INCR_DEL textMission9  = nullptr;
	textMission10->deleteMe(); delete textMission10; INCR_DEL textMission10 = nullptr;
	textMission11->deleteMe(); delete textMission11; INCR_DEL textMission11 = nullptr;
	textMission12->deleteMe(); delete textMission12; INCR_DEL textMission12 = nullptr;
	textMission13->deleteMe(); delete textMission13; INCR_DEL textMission13 = nullptr;
	textMission14->deleteMe(); delete textMission14; INCR_DEL textMission14 = nullptr;
	textMission15->deleteMe(); delete textMission15; INCR_DEL textMission15 = nullptr;
	textMission16->deleteMe(); delete textMission16; INCR_DEL textMission16 = nullptr;
	textMission17->deleteMe(); delete textMission17; INCR_DEL textMission17 = nullptr;
	textMission18->deleteMe(); delete textMission18; INCR_DEL textMission18 = nullptr;
	textMission19->deleteMe(); delete textMission19; INCR_DEL textMission19 = nullptr;
	textMission20->deleteMe(); delete textMission20; INCR_DEL textMission20 = nullptr;
	textMission21->deleteMe(); delete textMission21; INCR_DEL textMission21 = nullptr;
	textMission22->deleteMe(); delete textMission22; INCR_DEL textMission22 = nullptr;

	textExtra1Title->deleteMe(); delete textExtra1Title; INCR_DEL textExtra1Title = nullptr;
	textExtra1Data ->deleteMe(); delete textExtra1Data;  INCR_DEL textExtra1Data  = nullptr;
	textExtra2Title->deleteMe(); delete textExtra2Title; INCR_DEL textExtra2Title = nullptr;
	textExtra2Data ->deleteMe(); delete textExtra2Data;  INCR_DEL textExtra2Data  = nullptr;
	textExtra3Title->deleteMe(); delete textExtra3Title; INCR_DEL textExtra3Title = nullptr;
	textExtra3Data ->deleteMe(); delete textExtra3Data;  INCR_DEL textExtra3Data  = nullptr;
	textExtra4Title->deleteMe(); delete textExtra4Title; INCR_DEL textExtra4Title = nullptr;
	textExtra4Data ->deleteMe(); delete textExtra4Data;  INCR_DEL textExtra4Data  = nullptr;
	textExtra5Title->deleteMe(); delete textExtra5Title; INCR_DEL textExtra5Title = nullptr;
	textExtra5Data ->deleteMe(); delete textExtra5Data;  INCR_DEL textExtra5Data  = nullptr;

	textArcadeResultTitle->deleteMe(); delete textArcadeResultTitle; INCR_DEL textArcadeResultTitle  = nullptr;
	textArcadeResultData ->deleteMe(); delete textArcadeResultData;  INCR_DEL textArcadeResultData   = nullptr;

	GuiManager::clearGuisToRender();

	delete item1; INCR_DEL item1 = nullptr;
	delete item2; INCR_DEL item2 = nullptr;
	delete item3; INCR_DEL item3 = nullptr;
	delete item4; INCR_DEL item4 = nullptr;
	delete itemBackdrop1; INCR_DEL itemBackdrop1 = nullptr;
	delete itemBackdrop2; INCR_DEL itemBackdrop2 = nullptr;
	delete itemBackdrop3; INCR_DEL itemBackdrop3 = nullptr;
	delete itemBackdrop4; INCR_DEL itemBackdrop4 = nullptr;

	delete itemMission1;  INCR_DEL itemMission1  = nullptr;
	delete itemMission2;  INCR_DEL itemMission2  = nullptr;
	delete itemMission3;  INCR_DEL itemMission3  = nullptr;
	delete itemMission4;  INCR_DEL itemMission4  = nullptr;
	delete itemMission5;  INCR_DEL itemMission5  = nullptr;
	delete itemMission6;  INCR_DEL itemMission6  = nullptr;
	delete itemMission7;  INCR_DEL itemMission7  = nullptr;
	delete itemMission8;  INCR_DEL itemMission8  = nullptr;
	delete itemMission9;  INCR_DEL itemMission9  = nullptr;
	delete itemMission10; INCR_DEL itemMission10 = nullptr;
	delete itemMission11; INCR_DEL itemMission11 = nullptr;
	delete itemMission12; INCR_DEL itemMission12 = nullptr;
	delete itemMission13; INCR_DEL itemMission13 = nullptr;
	delete itemMission14; INCR_DEL itemMission14 = nullptr;
	delete itemMission15; INCR_DEL itemMission15 = nullptr;
	delete itemMission16; INCR_DEL itemMission16 = nullptr;
	delete itemMission17; INCR_DEL itemMission17 = nullptr;
	delete itemMission18; INCR_DEL itemMission18 = nullptr;
	delete itemMission19; INCR_DEL itemMission19 = nullptr;
	delete itemMission20; INCR_DEL itemMission20 = nullptr;
	delete itemMission21; INCR_DEL itemMission21 = nullptr;
	delete itemMission22; INCR_DEL itemMission22 = nullptr;
	delete itemMissionBackdrop1;  INCR_DEL itemMissionBackdrop1  = nullptr; 
	delete itemMissionBackdrop2;  INCR_DEL itemMissionBackdrop2  = nullptr; 
	delete itemMissionBackdrop3;  INCR_DEL itemMissionBackdrop3  = nullptr; 
	delete itemMissionBackdrop4;  INCR_DEL itemMissionBackdrop4  = nullptr; 
	delete itemMissionBackdrop5;  INCR_DEL itemMissionBackdrop5  = nullptr; 
	delete itemMissionBackdrop6;  INCR_DEL itemMissionBackdrop6  = nullptr; 
	delete itemMissionBackdrop7;  INCR_DEL itemMissionBackdrop7  = nullptr; 
	delete itemMissionBackdrop8;  INCR_DEL itemMissionBackdrop8  = nullptr; 
	delete itemMissionBackdrop9;  INCR_DEL itemMissionBackdrop9  = nullptr; 
	delete itemMissionBackdrop10; INCR_DEL itemMissionBackdrop10 = nullptr;
	delete itemMissionBackdrop11; INCR_DEL itemMissionBackdrop11 = nullptr;
	delete itemMissionBackdrop12; INCR_DEL itemMissionBackdrop12 = nullptr;
	delete itemMissionBackdrop13; INCR_DEL itemMissionBackdrop13 = nullptr;
	delete itemMissionBackdrop14; INCR_DEL itemMissionBackdrop14 = nullptr;
	delete itemMissionBackdrop15; INCR_DEL itemMissionBackdrop15 = nullptr;
	delete itemMissionBackdrop16; INCR_DEL itemMissionBackdrop16 = nullptr;
	delete itemMissionBackdrop17; INCR_DEL itemMissionBackdrop17 = nullptr;
	delete itemMissionBackdrop18; INCR_DEL itemMissionBackdrop18 = nullptr;
	delete itemMissionBackdrop19; INCR_DEL itemMissionBackdrop19 = nullptr;
	delete itemMissionBackdrop20; INCR_DEL itemMissionBackdrop20 = nullptr;
	delete itemMissionBackdrop21; INCR_DEL itemMissionBackdrop21 = nullptr;
	delete itemMissionBackdrop22; INCR_DEL itemMissionBackdrop22 = nullptr;

	delete itemRankDisplay;          INCR_DEL itemRankDisplay          = nullptr;
	delete itemRankDisplayBackdrop;  INCR_DEL itemRankDisplayBackdrop  = nullptr;
	delete itemTimeDisplay;          INCR_DEL itemTimeDisplay          = nullptr;
	delete itemTimeDisplayBackdrop;  INCR_DEL itemTimeDisplayBackdrop  = nullptr;
	delete itemScoreDisplay;         INCR_DEL itemScoreDisplay         = nullptr;
	delete itemScoreDisplayBackdrop; INCR_DEL itemScoreDisplayBackdrop = nullptr;

	textBestScore->deleteMe(); delete textBestScore; INCR_DEL textBestScore = nullptr;
	textBestTime ->deleteMe(); delete textBestTime;  INCR_DEL textBestTime  = nullptr;

	delete rankM1; INCR_DEL rankM1 = nullptr;
	delete rankM2; INCR_DEL rankM2 = nullptr;
	delete rankM3; INCR_DEL rankM3 = nullptr;
	delete rankM4; INCR_DEL rankM4 = nullptr;

	delete missionSelect; INCR_DEL missionSelect = nullptr;

	delete npcIcon; INCR_DEL npcIcon = nullptr;
}

void MainMenu::selectMenuArcadeClear()
{
	GuiManager::clearGuisToRender();

	menuSelectionID = ARCADE_CLEAR;

	textItem1->setVisibility(false);
	textItem2->setVisibility(false);
	textItem3->setVisibility(false);
	textItem4->setVisibility(false);

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
	textMission22->setVisibility(false);

	textBestScore->setVisibility(false);
	textBestTime ->setVisibility(false);

	textExtra1Title->setVisibility(false);
	textExtra1Data ->setVisibility(false);
	textExtra2Title->setVisibility(false);
	textExtra2Data ->setVisibility(false);
	textExtra3Title->setVisibility(false);
	textExtra3Data ->setVisibility(false);
	textExtra4Title->setVisibility(false);
	textExtra4Data ->setVisibility(false);
	textExtra5Title->setVisibility(false);
	textExtra5Data ->setVisibility(false);

	textArcadeResultTitle->setVisibility(true);
	textArcadeResultData ->setVisibility(true);
}

void MainMenu::selectMenuMission(int newSelection)
{
	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;
	float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension
	float py = 1.0f/(SCR_HEIGHT); //1 pixel in y dimension

	float menuOffset = (SCR_HEIGHT * (4.0f / 3.0f)) / SCR_WIDTH;

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
	itemMission21->setY(yPos+offsetY); yPos+=128*py;
	itemMission22->setY(yPos+offsetY);
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
	itemMissionBackdrop21->setY(yPos+offsetY); yPos+=128*py;
	itemMissionBackdrop22->setY(yPos+offsetY);

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
	itemMission22->setX(0.5f-512*px-64*px);
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
	itemMissionBackdrop22->setX(0.5f-512*px-64*px+8*px);

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
	textMission21->getPosition()->y = yPos+offsetY; yPos+=128*py;
	textMission22->getPosition()->y = yPos+offsetY;
	
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
	textMission22->getPosition()->x = 0.0f;

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
	GuiManager::addGuiToRender(itemMission22);

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
		case MISSION_1 : textMission1->getPosition()->x += 64 * px; itemMission1->setX(0.5f-512*px); itemMissionBackdrop1 ->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop1);  break;
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
		case MISSION_22: textMission22->getPosition()->x += 64*px; itemMission22->setX(0.5f-512*px); itemMissionBackdrop22->setX(0.5f-512*px+8*px); GuiManager::addGuiToRender(itemMissionBackdrop22); break;
		default: break;
	}

	menuSelectionID = newSelection;

	unsigned int totalNPC = (unsigned int)Global::npcList.size();
	auto end = Global::gameSaveData.end();
	std::string base = Global::gameLevelData[newSelection].displayName+"_NPC_";
	int npcInThisStageCount = 0;

	for (unsigned int i = 0; i < totalNPC; i++)
	{
		std::string baseCheck = Global::npcList[i];
		baseCheck.erase(baseCheck.length()-1, std::string::npos);
		if (baseCheck == base)
		{
			npcInThisStageCount++;
		}
	}

	int totalNPCWeFound = 0;

	for (int i = 1; i <= npcInThisStageCount; i++)
	{
		std::string check = base + std::to_string(i);

		if (Global::gameSaveData.find(check) != end)
		{
			if (Global::gameSaveData[check] == "true")
			{
				totalNPCWeFound++;
			}
		}
	}

	if (totalNPCWeFound != npcInThisStageCount)
	{
		GuiManager::addGuiToRender(npcIcon);
	}

	missionSelect->setX(0.75f-83*px+(Global::gameMissionNumber*55)*px);
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
	textMission22->setVisibility(true);

	textBestScore->setVisibility(true);
	textBestTime ->setVisibility(true);

	textExtra1Title->setVisibility(false);
	textExtra1Data ->setVisibility(false);
	textExtra2Title->setVisibility(false);
	textExtra2Data ->setVisibility(false);
	textExtra3Title->setVisibility(false);
	textExtra3Data ->setVisibility(false);
	textExtra4Title->setVisibility(false);
	textExtra4Data ->setVisibility(false);
	textExtra5Title->setVisibility(false);
	textExtra5Data ->setVisibility(false);

	textArcadeResultTitle->setVisibility(false);
	textArcadeResultData ->setVisibility(false);

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
	textMission22->setVisibility(false);

	textBestScore->setVisibility(false);
	textBestTime ->setVisibility(false);

	textExtra1Title->setVisibility(false);
	textExtra1Data ->setVisibility(false);
	textExtra2Title->setVisibility(false);
	textExtra2Data ->setVisibility(false);
	textExtra3Title->setVisibility(false);
	textExtra3Data ->setVisibility(false);
	textExtra4Title->setVisibility(false);
	textExtra4Data ->setVisibility(false);
	textExtra5Title->setVisibility(false);
	textExtra5Data ->setVisibility(false);

	textArcadeResultTitle->setVisibility(false);
	textArcadeResultData ->setVisibility(false);

	Global::gameMissionNumber = 0;

	AudioPlayer::play(36, Global::gameCamera->getFadePosition1());
}

void MainMenu::selectMenuExtra()
{
	GuiManager::clearGuisToRender();

	menuSelectionID = EXTRAS;

	textItem1->setVisibility(false);
	textItem2->setVisibility(false);
	textItem3->setVisibility(false);
	textItem4->setVisibility(false);

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
	textMission22->setVisibility(false);

	textBestScore->setVisibility(false);
	textBestTime ->setVisibility(false);

	textExtra1Title->setVisibility(true);
	textExtra1Data ->setVisibility(true);
	textExtra2Title->setVisibility(true);
	textExtra2Data ->setVisibility(true);
	textExtra3Title->setVisibility(true);
	textExtra3Data ->setVisibility(true);
	textExtra4Title->setVisibility(true);
	textExtra4Data ->setVisibility(true);
	textExtra5Title->setVisibility(true);
	textExtra5Data ->setVisibility(true);

	textArcadeResultTitle->setVisibility(false);
	textArcadeResultData ->setVisibility(false);

	AudioPlayer::play(36, Global::gameCamera->getFadePosition1());
}

void MainMenu::step()
{
	bool shouldGoUp    = false;
	bool shouldGoDown  = false;
	bool shouldGoLeft  = false;
	bool shouldGoRight = false;
	bool pressedSelect = (Inputs.INPUT_JUMP && !Inputs.INPUT_PREVIOUS_JUMP) || (Inputs.INPUT_START && !Inputs.INPUT_PREVIOUS_START);
	bool pressedBack   = (Inputs.INPUT_ACTION && !Inputs.INPUT_PREVIOUS_ACTION);

	int moveX = (int)round(Inputs.INPUT_X);
	int moveY = (int)round(Inputs.INPUT_Y);

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

	if (moveY == -1)
	{
		holdUpTimer++;
	}
	else
	{
		holdUpTimer = 0;
	}

	if (moveY == 1)
	{
		holdDownTimer++;
	}
	else
	{
		holdDownTimer = 0;
	}

	if (holdUpTimer >= 20)
	{
		if (holdUpTimer % 5 == 0)
		{
			shouldGoUp = true;
		}
	}

	if (holdDownTimer >= 20)
	{
		if (holdDownTimer % 5 == 0)
		{
			shouldGoDown = true;
		}
	}

	if (MainMenu::titleCardTextTimer != 0)
	{
		if (MainMenu::titleCardTextTimer == 1)
		{
			if (textTitleCardLevelName != nullptr)
			{
				textTitleCardLevelName->deleteMe();
				delete textTitleCardLevelName; INCR_DEL
				textTitleCardLevelName = nullptr;
			}
			if (textTitleCardMission != nullptr)
			{
				textTitleCardMission->deleteMe();
				delete textTitleCardMission; INCR_DEL
				textTitleCardMission = nullptr;
			}
			if (textTitleCardMissionDescription != nullptr)
			{
				textTitleCardMissionDescription->deleteMe();
				delete textTitleCardMissionDescription; INCR_DEL
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
						Global::gameIsArcadeMode = true;
						Global::gameArcadePlaytime = 0;

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
						Global::gameIsArcadeMode = false;
						break;
					}

					case ROOT_EXTRAS:
					{
						MainMenu::selectMenuExtra();
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
					case MISSION_22: Global::levelID = LVL_RADICAL_HIGHWAY;    break;
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
		if (menuSelectionID == EXTRAS)
		{
			if (unlockedCharacters.size() > 1)
			{
				if (shouldGoLeft || shouldGoRight)
				{
					if (shouldGoLeft)
					{
						characterSelectIndex--;
						if (characterSelectIndex < 0)
						{
							characterSelectIndex = ((int)unlockedCharacters.size())-1;
						}
					}
					if (shouldGoRight)
					{
						characterSelectIndex++;
						if (characterSelectIndex > ((int)unlockedCharacters.size())-1)
						{
							characterSelectIndex = 0;
						}
					}


					characterSelectIndex = std::max(0, characterSelectIndex);
					characterSelectIndex = std::min(characterSelectIndex, (int)unlockedCharacters.size()-1);

					textExtra5Title->deleteMe(); delete textExtra5Title; INCR_DEL textExtra5Title = nullptr;
					textExtra5Data ->deleteMe(); delete textExtra5Data;  INCR_DEL textExtra5Data  = nullptr;

					const float yoff = -0.03f;
					const float divisor = 6.0f;

					textExtra5Title = new GUIText("PLAY AS:", 2, font, 0, (5/divisor)+yoff, 1, true, false, true); INCR_NEW
					textExtra5Data  = new GUIText(unlockedCharacters[characterSelectIndex], 2, font, 0, (5/divisor)-yoff, 1, true, false, true); INCR_NEW
				}
			}
			if (pressedBack)
			{
				MainMenu::selectMenuRoot(ROOT_EXTRAS);
			}
		}
		else if (menuSelectionID == ARCADE_CLEAR)
		{
			if (pressedBack)
			{
				MainMenu::selectMenuRoot(ROOT_STORY);
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
		INCR_DEL
		textTitleCardLevelName = nullptr;
	}
	if (textTitleCardMission != nullptr)
	{
		textTitleCardMission->deleteMe();
		delete textTitleCardMission;
		INCR_DEL
		textTitleCardMission = nullptr;
	}
	if (textTitleCardMissionDescription != nullptr)
	{
		textTitleCardMissionDescription->deleteMe();
		delete textTitleCardMissionDescription;
		INCR_DEL
		textTitleCardMissionDescription = nullptr;
	}

	textTitleCardLevelName          = new GUIText(Global::levelNameDisplay, 3.0f, font, 0.0f, 0.6f, 1.0f, true, false, true); INCR_NEW
	textTitleCardMission            = new GUIText("Mission "+std::to_string(Global::gameMissionNumber+1)+":", 2.5f, font, 0.0f, 0.7f, 1.0f, true, false, true); INCR_NEW
	textTitleCardMissionDescription = new GUIText(Global::gameMissionDescription, 2.0f, font, 0.0f, 0.8f, 1.0f, true, false, true); INCR_NEW

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
		textBestTime->deleteMe(); delete textBestTime; INCR_DEL
		textBestTime  = new GUIText("TIME: "+time, 2.0f, font, 0.75f-192*px, 0.5f+256*py-0.025f, 1-(0.75f-192*px), false, false, true); INCR_NEW
	}
	else
	{
		textBestTime->deleteMe(); delete textBestTime; INCR_DEL
		textBestTime  = new GUIText("TIME: ", 2.0f, font, 0.75f-192*px, 0.5f+256*py-0.025f, 1-(0.75f-192*px), false, false, true); INCR_NEW
	}

	if (Global::gameSaveData.find(Global::gameLevelData[levelID].displayName+missionScoreString) != Global::gameSaveData.end())
	{
		std::string score = Global::gameSaveData[Global::gameLevelData[levelID].displayName+missionScoreString];
		textBestScore->deleteMe(); delete textBestScore; INCR_DEL
		textBestScore = new GUIText("SCORE: "+score, 2.0f, font, 0.75f-192*px, 0.5f+128*py-0.025f, 1-(0.75f-192*px), false, false, true); INCR_NEW
	}
	else
	{
		textBestScore->deleteMe(); delete textBestScore; INCR_DEL
		textBestScore = new GUIText("SCORE: ", 2.0f, font, 0.75f-192*px, 0.5f+128*py-0.025f, 1-(0.75f-192*px), false, false, true); INCR_NEW
	}
}