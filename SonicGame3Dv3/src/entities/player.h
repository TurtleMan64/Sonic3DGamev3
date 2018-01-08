#ifndef PLAYER_H
#define PLAYER_H

class TexturedModel;
class Triangle3D;
class Limb;
class Body;

#include <list>

#include "entities.h"
#include "../toolbox/vector.h"


class Player : public Entity
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
	const float gravity = 0.08f;
	const float hoverAccel = 0.04f;
	const float jumpPower = 1.7f;

	const int hoverLimit = 60;
	int hoverCount = 0;

	const float moveAcceleration = 0.07f;
	float moveSpeedCurrent = 0;
	const float moveAccelerationAir = 0.035f;
	float moveSpeedAirCurrent = 0;

	const float frictionGround = 0.03f;
	const float frictionAir = 0.01f;

	const float normalSpeedLimit = 4.0f;
	const float airSpeedLimit = 2.5f;

	const float slowDownRate = 0.06f; //how fast you slowdown every frame when youre going faster than max speed 
	const float slowDownAirRate = 0.025f;

	const float spindashPower = 0.15f;
	const float spindashFriction = 0.09f;
	int spindashDelay = 0;
	int spindashTimer = 0;
	const int spindashTimerMax = 30;
	int spindashReleaseTimer = 0;
	const int spindashReleaseTimerMax = 30;
	int spindashRestartDelay = 0;
	const int spindashRestartDelayMax = 8;
	float storedSpindashSpeed = 0;

	int homingAttackTimer = -1; // -1 = can start a homing attack
	const int homingAttackTimerMax = 10;


	const float surfaceTension = 10.0f; //3, 10 after new 2nd collision ignore feature
	const float slopeAccel = 0.092f; //how much you are influenced by the terrain's slope

	const int wallStickTimerMax = 30; //how long you stay on a wall after you go too slow
	int wallStickTimer = 0;

	float count = 0;

	Triangle3D* triCol = nullptr;
	Vector3f* colPos = nullptr;

	float modelRunIndex = 0;

	float cameraRadius = 104;
	float cameraRadiusTarget = 104;
	const float cameraLaziness = 3;
	const float cameraRadiusZoom = 40;
	const float cameraRadiusZoomOut = 104;
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

	bool canMove = true;

	float spindashAngle = 0;
	bool canStartSpindash = false;

	bool isJumping = false;
	bool isSpindashing = false;
	bool isSkidding = false;
	bool isBall = false;
	bool isBouncing = false;
	bool isStomping = false;
	bool isLightdashing = false;

	float headHeight = 7;
	bool firstPerson = false;

	float displayHeightOffset = 0.8f; //How much the model is shifted vertically when displaying
	Vector3f previousDisplayPos;

	int iFrame = 0;
	int hitTimer = 0;

	bool inWater = false;
	bool inWaterPrevious = false;
	float waterHeight = 0;

	bool isGettingExternallyMoved = false;
	float xDisp = 0;
	float yDisp = 0;
	float zDisp = 0;

public:
	Player(float, float, float);

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

	/** If canMove is false, then every input from the
	* controller is ignored. It is up to whoever sets this
	* to false to set it back to true.
	*
	* @param newMove
	*/
	void setCanMove(bool newMove);

	void setGroundSpeed(float newXspd, float newZspd);

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

	void setOnPlane(bool on);

	float getHitboxHorizontal();

	float getHitboxVertical();

	void stopMoving();

	void setInWater(float height);

	void takeDamage(Vector3f* damageSource);

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

	void bounceOffGround(Vector3f* surfaceNormal);

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

	//std::string getName();
};
#endif