#ifndef PLAYERSONIC_H
#define PLAYERSONIC_H

class TexturedModel;
class Triangle3D;
class Limb;
class Body;
class ManiaSonicModel;
class Source;
class ShieldMagnet;
class ShieldGreen;

#include <list>

#include "entities.h"
#include "controllableplayer.h"
#include "../toolbox/vector.h"


class PlayerSonic : public ControllablePlayer
{
private:
	static std::list<TexturedModel*> modelBody;
	static std::list<TexturedModel*> modelHead;
	static std::list<TexturedModel*> modelLeftHumerus;
	static std::list<TexturedModel*> modelLeftForearm;
	static std::list<TexturedModel*> modelLeftHand;
	static std::list<TexturedModel*> modelLeftThigh;
	static std::list<TexturedModel*> modelLeftShin;
	static std::list<TexturedModel*> modelLeftFoot;
	static std::list<TexturedModel*> modelRightHumerus;
	static std::list<TexturedModel*> modelRightForearm;
	static std::list<TexturedModel*> modelRightHand;
	static std::list<TexturedModel*> modelRightThigh;
	static std::list<TexturedModel*> modelRightShin;
	static std::list<TexturedModel*> modelRightFoot;

	Body* myBody;
	Limb* myHead;
	Limb* myLeftHumerus;
	Limb* myLeftForearm;
	Limb* myLeftHand;
	Limb* myLeftThigh;
	Limb* myLeftShin;
	Limb* myLeftFoot;
	Limb* myRightHumerus;
	Limb* myRightForearm;
	Limb* myRightHand;
	Limb* myRightThigh;
	Limb* myRightShin;
	Limb* myRightFoot;

	static ManiaSonicModel* maniaSonic;

public:
	static int characterID;

private:
	float xVel = 0;
	float yVel = 0;
	float zVel = 0;

	float xVelGround = 0;
	float zVelGround = 0;

	float xVelAir = 0;
	float zVelAir = 0;

	Vector3f currNorm;

	Vector3f previousPos;

	int airTimer = 0;
	bool onPlane = false;
	bool onPlanePrevious = false;
	float gravity = 0.08f;
	const float hoverAccel = 0.04f; //How much yVel you gain each frame from hovering
	const float jumpPower = 1.7f;

	const int hoverLimit = 60;
	int hoverCount = 0;

	const float moveAcceleration = 0.07f;
	float moveSpeedCurrent = 0;
	const float moveAccelerationAir = 0.035f;
	float moveSpeedAirCurrent = 0;

	const float frictionGround = 0.03f;
	const float frictionAir = 0.01f;

	const float normalSpeedLimit = 4.2f; //4.0f
	const float airSpeedLimit = 2.5f;

	const float slowDownRate = 0.06f; //How fast you slowdown every frame when youre going faster than max speed 
	const float slowDownAirRate = 0.025f;

	const float spindashPower = 0.17f;    //0.15f
	const float spindashFriction = 0.107f; //0.09f
	int spindashDelay = 0;
	int spindashTimer = 0;
	const int spindashTimerMax = 30;
	int spindashReleaseTimer = 0;
	const int spindashReleaseTimerMax = 30;
	int spindashRestartDelay = 0;
	const int spindashRestartDelayMax = 8;
	float storedSpindashSpeed = 0;

	//Drop dash variables
	bool isDropDashing = false;
	float dropDashCharge = 0.0f;
	const float dropDashChargeIncrease = 0.75f;
	const float dropDashChargeDecrease = 0.02f;
	const float dropDashChargeMax = 3.5f;
	const float dropDashChargeMin = 0.5f;
	float storedDropdashSpeed = 0;

	int homingAttackTimer = -1; // -1 = can start a homing attack
	const int homingAttackTimerMax = 10;


	const float surfaceTension = 10.0f; //Increase to make sonic not fly off slopes when going fast
	const float slopeAccel = 0.092f; //How much you are influenced by the terrain's slope

	const int wallStickTimerMax = 30; //How long you stay on a wall after you go too slow
	int wallStickTimer = 0;

	float animCount = 0;
	float airSpinRotation = 0;//Rotation used when in the air

	const float ballSlopeAccelFactor = 1.25f; //Additional accel on slopes from being in ball
	const float wallThreshold = 0.3f; //How steep a slope must be to be considered a wall
	const float wallSpeedStickThreshold = 2.0f; //How fast you must be going to keep sticking on a wall
	const float autoUnrollThreshold = 0.45f; //Automatically unrolls from ball form when under this speed
	const float bounceFactor = 0.75f; //Speed you retain from a bounce
	const float cantStickBounceFactor = 0.6f; //Speed you retain from not sticking to a wall
	const float smoothTransitionThreshold = 0.6f; //How similar 2 triangles must be to run between them
	const float waterExitBoost = 0.4f; //When you jump out of water, get this boost
	const float waterEntryMaxYVel = -1.0f; //When you enter water, yVel cant be less than this
	const float waterEntrySlowdown = 0.75f; //When you enter water, slowdown horizontal speed
	const float waterDeceleration = 0.987f; //When in water, speed gets multiplied by this every frame

	Triangle3D* triCol = nullptr;
	Vector3f* colPos = nullptr;

	float modelRunIndex = 0;

	float cameraRadius = 104;
	float cameraRadiusTarget = 104;
	const float cameraLaziness = 3;
	const float cameraRadiusZoom = 40;
	const float cameraRadiusZoomOut = 104;
	float cameraYawReal = 0;
	float cameraPitchReal = 0;
	float cameraYawTarget = 0;
	float cameraPitchTarget = 0;


	//movement inputs
	bool jumpInput = 0;
	bool actionInput = 0;
	bool action2Input = 0;
	bool shoulderInput = 0;
	bool selectInput = 0;
	bool specialInput = 0;
	bool previousJumpInput = 0;
	bool previousActionInput = 0;
	bool previousAction2Input = 0;
	bool previousShoulderInput = 0;
	bool previousSelectInput = 0;
	bool previousSpecialInput = 0;
	float zoomInput = 0;
	float movementInputX = 0;
	float movementInputY = 0;
	float cameraInputX = 0;
	float cameraInputY = 0;
	float movementAngle = 0;

	//bool canMove = true;
	int canMoveTimer = -1;

	float spindashAngle = 0;
	bool canStartSpindash = false;
	bool bufferedSpindashInput = false;

	bool isJumping = false;
	bool isSpindashing = false;
	bool isSkidding = false;
	bool isBall = false;
	bool isBouncing = false;
	bool isStomping = false;
	bool isLightdashing = false;

	bool justBounced = false; //Are we in the air after doing a bounce?
	bool justHomingAttacked = false; //Are we in the air after doing a homing attack?

	float headHeight = 7;
	bool firstPerson = false;

	float displayHeightOffset = 0.8f; //How much the model is shifted vertically when displaying
	Vector3f previousDisplayPos;

	int iFrame = 0;
	int hitTimer = 0;

	int deadTimer = -1;

	bool inWater = false;
	bool inWaterPrevious = false;
	float waterHeight = 0;

	bool isGettingExternallyMoved = false;
	float xDisp = 0;
	float yDisp = 0;
	float zDisp = 0;

	Source* stompSource = nullptr;

	Vector3f previousLightdashPosition;
	int lightdashFrameEnd = 0;

	ShieldMagnet* myShieldMagnet = nullptr;
	ShieldGreen*  myShieldGreen  = nullptr;

	int combo = 0;

	int invincibleTimer = 0;
	int speedShoesTimer = 0;

	bool onRocket = false;

public:
	PlayerSonic(float, float, float);

	void step();

	bool isPlayer();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	void setCameraAngles(float newYaw, float newPitch);

	void setCameraTargetYaw(float yaw);

	void setCameraTargetPitch(float pitch);

	void increaseGroundSpeed(float dx, float dz);

	float getSpeed();

	void goUp();

	void setCanMoveTimer(int newMoveTimer);

	void setGroundSpeed(float newXspd, float newZspd);

	float getXVelGround();

	float getZVelGround();

	float getxVel();

	void setxVel(float xVel);

	float getyVel();

	void setyVel(float yVel);

	float getzVel();

	void setzVel(float zVel);

	void setxVelAir(float xVelAir);

	float getXVelAir();

	void setzVelAir(float zVelAir);

	float getZVelAir();

	void setHoverCount(int newCount);

	int getHoverCount();

	void setOnPlane(bool on);

	float getHitboxHorizontal();

	float getHitboxVertical();

	void stopMoving();

	void setInWater(float height);

	void takeDamage(Vector3f* damageSource);

	void rebound(Vector3f* source);

	bool isVulnerable();

	void die();

	Vector3f getOverallVel();

	float getSpindashSpeed();

	void debugAdjustCamera();

	void boostMe(float amount);

	void setDisplacement(float x, float y, float z);

	void setGravity(float newGrav);

	bool isDying();

	void setOnPlanePrevious(bool on);

	int getSpindashTimer();

	void setSpindashTimer(int newTimer);

	bool isChargingSpindash();

	void setIsBall(bool newisBall);

	//returns the speed player goes after releasing a spindash
	float calculateSpindashSpeed(int spindashCharge);

	bool isOnGround();

	//Returns the normal of the triangle that the player has collided with
	Vector3f* getCurrNorm();

	//Returns the center position of where the player is being drawn.
	Vector3f getCenterPosition();

	ShieldMagnet* getShieldMagnet();

	void setShieldMagnet(ShieldMagnet* newMagnet);

	ShieldGreen* getShieldGreen();

	void setShieldGreen(ShieldGreen* newGreen);

	void increaseCombo();

	void setInvincibleTimer(int newTimer);

	void setSpeedshoesTimer(int newTimer);

	void setOnRocket(bool onRocket);

private:
	void adjustCamera();

	void moveMeGround();

	void setMovementInputs();

	void checkSkid();

	void applyFrictionAir();

	void moveMeAir();

	void limitMovementSpeedAir();

	void applyFriction(float frictionToApply);

	void limitMovementSpeed(float limit);

	void calcSpindashAngle();

	void spindash(int timer);

	void homingAttack();

	void initiateBounce();

	void initiateStomp();

	void bounceOffGround(Vector3f* surfaceNormal, float b, int s);

	//attempt to continue a lightdash
	//if lightdash cant continue, sets isLightdashing
	//to false
	void attemptLightdash();

	void createLimbs();

	void addLimbsToGame();

	void removeLimbsFromGame();

	void updateLimbs(int animIndex, float time);

	void updateLimbsMatrix();

	void setLimbsVisibility(bool visible);

	void animate();

	void createSpindashTrails(Vector3f* initPos, Vector3f* endPos, int count, int life);

	void newSpindashTrail(Vector3f* position, int life, int colourID);

	void newSpindashTrail(Vector3f* position, float xVel, float yVel, float zVel, float gravity, int life, float size, int colourID);

	void createStompParticles();

	void popOffWall();

	void dropDash(float charge);
};
#endif