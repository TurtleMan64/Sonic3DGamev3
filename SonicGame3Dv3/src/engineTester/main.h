#ifndef MAIN_H
#define MAIN_H

class Entity;
class Camera;
class ControllablePlayer;
class Stage;
class SkySphere;
class Light;
class EC_Shark;
class WaterRenderer;
class WaterFrameBuffers;
class WaterTile;
class Spring;
class ShadowMapMasterRenderer;
class Fbo;

#include <string>
#include <random>
#include <list>
#include <unordered_map>
#include "../toolbox/level.h"

void Main_addEntity(Entity* entityToAdd);
void Main_deleteEntity(Entity* entityToDelete);
void Main_deleteAllEntites();

void Main_addEntityPass2(Entity* entityToAdd);
void Main_deleteEntityPass2(Entity* entityToDelete);
void Main_deleteAllEntitesPass2();

void Main_addTransparentEntity(Entity* entityToAdd);
void Main_deleteTransparentEntity(Entity* entityToDelete);
void Main_deleteAllTransparentEntites();

#define STATE_PAUSED 0
#define STATE_RUNNING 1
#define STATE_EXITING 2
#define STATE_CUTSCENE 3
#define STATE_TITLE 4
#define STATE_DEBUG 5

#define LVL_EMERALD_COAST  	    0
#define LVL_DRY_LAGOON		    1
#define LVL_SPEED_HIGHWAY	    2
#define LVL_TWINKLE_PARK	    3
#define LVL_WILD_CANYON		    4
#define LVL_METAL_HARBOR	    5
#define LVL_DELFINO_PLAZA	    6
#define LVL_GREEN_HILL_ZONE	    7
#define LVL_NOKI_BAY		    8
#define LVL_WEAPONS_BED		    9
#define LVL_OUTSET_ISLAND	   10
#define LVL_WUHU_ISLAND		   11
#define LVL_SNOWHEAD		   12
#define LVL_SAND_HILL		   13
#define LVL_RAINBOW_ROAD	   14
#define LVL_PEACHS_CASTLE	   15
#define LVL_KOOPA_BEACH		   16
#define LVL_FIRE_FIELD		   17
#define LVL_BOBOMB_BATTLEFIELD 18
#define LVL_KINGDOM_VALLEY	   19
#define LVL_PUMPKIN_HILL       20
#define LVL_RADICAL_HIGHWAY    21
#define LVL_BOSS               22

#define ENTITY_RENDER_DIST 2000.0f
#define ENTITY_RENDER_DIST_HIGH 5000.0f

#define DEV_MODE

#ifdef DEV_MODE
	#include <thread>
	#define INCR_NEW Global::countNew++;
	#define INCR_DEL Global::countDelete++;
#else
	#define INCR_NEW ;
	#define INCR_DEL ;
#endif

class Global
{
public:
	static Camera* gameCamera;
	static ControllablePlayer* gamePlayer;
	static Stage* gameStage;
	static SkySphere* gameSkySphere;
	static Light* gameLightSun;
	static Light* gameLightMoon;
	static int countNew;
	static int countDelete;
	static int gameState;
	static int levelID;
	static std::string levelName;
	static std::string levelNameDisplay;
	static int bufferTime;
	static bool shouldLoadLevel;
	static bool isNewLevel;
	static bool isAutoCam;
	static int gameRingCount;
	static int gameScore;
	static int gameLives;
	static int gameClock;
	static WaterRenderer* gameWaterRenderer;
	static WaterFrameBuffers* gameWaterFBOs;
	static std::list<WaterTile*>* gameWaterTiles;
	static int finishStageTimer;
	static Fbo* gameMultisampleFbo;
	static Fbo* gameOutputFbo;
	static Fbo* gameOutputFbo2;
	static float deathHeight;
	static int gameMissionNumber;
	static bool gameIsNormalMode;
	static bool gameIsHardMode;
	static bool gameIsChaoMode;
	static bool gameIsRingMode;
	static std::string gameMissionDescription;
	static int gameRingTarget; //How many rings you have to collect to finish the stage in Ring mode
	static bool gameIsArcadeMode;
	static int gameTotalPlaytime;
	static int gameArcadePlaytime;
	static bool stageUsesWater;

	static bool  spawnAtCheckpoint;
	static float checkpointX;
	static float checkpointY;
	static float checkpointZ;
	static float checkpointRotY;
	static float checkpointCamYaw;
	static float checkpointCamPitch;
	static int   checkpointTimeCen;
	static int   checkpointTimeSec;
	static int   checkpointTimeMin;

	static std::vector<Level> gameLevelData;
	static std::unordered_map<std::string, std::string> gameSaveData;

	//Debug display
	static bool debugDisplay;
	static bool frozen;
	static bool step;

	//Graphics settings
	static bool useHighQualityWater;
	static unsigned HQWaterReflectionWidth;
	static unsigned HQWaterReflectionHeight;
	static unsigned HQWaterRefractionWidth;
	static unsigned HQWaterRefractionHeight;

	static bool renderParticles;

	static bool renderBloom;

	static bool renderShadowsFar;
	static bool renderShadowsClose;
	static int shadowsFarQuality;

	//Emerald Coast
	static EC_Shark* ecShark;

	//Test
	//static Spring* gameSpring;

	static bool unlockedSonicDoll;
	static bool unlockedMechaSonic;
	static bool unlockedDage4;
	static bool unlockedManiaSonic;
	static bool unlockedAmy;

	static std::vector<std::string> npcList;

	static void checkErrorAL(const char* description);

	static void loadSaveData();

	static void saveSaveData();

	static int calculateRankAndUpdate();

	static void increaseRingCount(int rings);
};
#endif