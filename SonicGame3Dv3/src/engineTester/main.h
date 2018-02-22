#ifndef MAIN_H
#define MAIN_H

class Entity;
class Camera;
class Player;
class Stage;
class SkySphere;
class Light;
class EC_Shark;
class WaterRenderer;
class WaterFrameBuffers;
class WaterTile;
class Spring;

#include <string>
#include <random>
#include <list>

void Main_addEntity(Entity* entityToAdd);
void Main_deleteEntity(Entity* entityToDelete);
void Main_deleteAllEntites();

void Main_addTransparentEntity(Entity* entityToAdd);
void Main_deleteTransparentEntity(Entity* entityToDelete);
void Main_deleteAllTransparentEntites();

#define STATE_PAUSED 0
#define STATE_RUNNING 1
#define STATE_EXITING 2
#define STATE_CUTSCENE 3
#define STATE_TITLE 4
#define STATE_DEBUG 5

#define LVL_EC 0
#define LVL_SH 1
#define LVL_GHZ 2
#define LVL_WI 3
#define LVL_PC 4
#define LVL_SHL 5
#define LVL_KB 6
#define LVL_OI 7
#define LVL_WB 8
#define LVL_MH 9
#define LVL_BOB 10
#define LVL_RR 11
#define LVL_SHD 12
#define LVL_TP 13

#define ENTITY_RENDER_DIST 2000.0f

class Global
{
public:
	static Camera* gameCamera;
	static Player* gamePlayer;
	static Stage* gameStage;
	static SkySphere* gameSkySphere;
	static Light* gameLightSun;
	static Light* gameLightMoon;
	static int countNew;
	static int countDelete;
	static int gameState;
	static int levelID;
	static std::string levelName;
	static int bufferTime;
	static bool shouldRestartLevel;
	static int gameRingCount;
	static int gameClock;
	static WaterRenderer* gameWaterRenderer;
	static WaterFrameBuffers* gameWaterFBOs;
	static std::list<WaterTile*>* gameWaterTiles;

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

	//Emerald Coast
	static EC_Shark* ecShark;

	//Test
	//static Spring* gameSpring;

	static bool unlockedSonicDoll;
	static bool unlockedMechaSonic;
	static bool unlockedDage4;
	static bool unlockedManiaSonic;
	static bool unlockedAmy;

	static std::default_random_engine* generator;
	static std::normal_distribution<double>* distribution;
};
#endif