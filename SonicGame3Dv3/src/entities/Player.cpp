#include <list>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "player.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../toolbox/input.h"
#include "../toolbox/maths.h"
#include "camera.h"
#include "../collision/collisionchecker.h"
#include "../collision/triangle3d.h"


std::list<TexturedModel*> Player::models;

extern bool INPUT_JUMP;
extern bool INPUT_ACTION;
extern bool INPUT_ACTION2;
extern bool INPUT_SHOULDER;
extern bool INPUT_SELECT;
extern bool INPUT_SPECIAL;
extern bool INPUT_START;

extern bool INPUT_PREVIOUS_JUMP;
extern bool INPUT_PREVIOUS_ACTION;
extern bool INPUT_PREVIOUS_ACTION2;
extern bool INPUT_PREVIOUS_SHOULDER;
extern bool INPUT_PREVIOUS_SELECT;
extern bool INPUT_PREVIOUS_SPECIAL;
extern bool INPUT_PREVIOUS_START;

extern float INPUT_X;
extern float INPUT_Y;
extern float INPUT_X2;
extern float INPUT_Y2;
extern float INPUT_ZOOM;

Player::Player(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	currNorm.x = 0;
	currNorm.y = 1;
	currNorm.z = 0;
}

void Player::step()
{
	previousPos.set(&position);
	count++;
	setMovementInputs();
	adjustCamera();
	checkSkid();

	iFrame = std::max(0, iFrame-1);
	hitTimer = std::max(0, hitTimer-1);

	if (jumpInput)
	{
		hoverCount = std::max(hoverCount - 1, 0);
	}
	else
	{
		hoverCount = 0;
	}

	if (!onPlane) //in air
	{
		xVelGround = 0;
		zVelGround = 0;
		applyFrictionAir();
		moveMeAir();
		limitMovementSpeedAir();
		yVel -= gravity;
	}
	else //on ground
	{
		hitTimer = 0;

		xVelAir = 0;
		zVelAir = 0;
		applyFriction(frictionGround);
		moveMeGround();
		limitMovementSpeed(normalSpeedLimit);
	}

	if (isBall)
	{
		xVelGround += currNorm.x*slopeAccel*1.25f;
		zVelGround += currNorm.z*slopeAccel*1.25f;
	}
	else
	{
		xVelGround += currNorm.x*slopeAccel;
		zVelGround += currNorm.z*slopeAccel;
	}

	float inputX = xVelGround;
	float inputY = zVelGround;
	float mag = (float)sqrt(inputX*inputX + inputY*inputY);

	float inputDir = (float)(atan2(inputY, inputX));
	Vector3f negNorm;
	negNorm.set(-currNorm.x, -currNorm.y, -currNorm.z);
	Vector3f mapped = mapInputs3(inputDir, mag, &negNorm);
	float Ax = mapped.x;
	float Ay = mapped.y;
	float Az = mapped.z;

	if (onPlane) //On Ground
	{
		isJumping = false;
		isBouncing = false;
		isStomping = false;
		homingAttackTimer = -1;
		float speed = (float)sqrt(xVelGround*xVelGround + zVelGround*zVelGround);
		if (currNorm.y <= 0 && speed < 1)
		{
			wallStickTimer--;
		}
		else
		{
			wallStickTimer = wallStickTimerMax;
		}

		if (wallStickTimer < 0)
		{
			currNorm = new Vector3f(0, 1, 0);
		}

		xVel = Ax;
		yVel = Ay;
		zVel = Az;
		xVelAir = 0;
		zVelAir = 0;
		hoverCount = hoverLimit;

		if (jumpInput && !previousJumpInput)
		{
			increasePosition(currNorm.x * 2, currNorm.y * 2, currNorm.z * 2);
			xVelAir = xVel + currNorm.x*jumpPower;
			zVelAir = zVel + currNorm.z*jumpPower;
			yVel = yVel + currNorm.y*jumpPower;
			xVel = 0;
			zVel = 0;
			xVelGround = 0;
			zVelGround = 0;
			isJumping = true;
			onPlane = false;

			//AudioSources.play(6, getPosition());
		}

		if (speed < 0.35)
		{
			if (isBall)
			{
				spindashReleaseTimer = spindashReleaseTimerMax;
				spindashRestartDelay = spindashRestartDelayMax;
			}
			isBall = false;
		}

		if (isBall == false && spindashRestartDelay == 0)
		{
			canStartSpindash = true;
		}
		else
		{
			canStartSpindash = false;
		}

		if (((actionInput) || (action2Input))
			&& canStartSpindash)
		{
			if (!isSpindashing)
			{
				storedSpindashSpeed = (float)sqrt(xVelGround*xVelGround + zVelGround*zVelGround);
			}
			isSpindashing = true;
		}

		if (!actionInput && !action2Input)
		{
			isSpindashing = false;
		}

		if (isSpindashing)
		{
			spindashTimer = std::min(spindashTimer + 1, spindashTimerMax);
			if (spindashTimer == 1)
			{
				//AudioSources.play(7, getPosition());
			}
			isSpindashing = true;
			calcSpindashAngle();
			if (spindashTimer > spindashDelay)
			{
				applyFriction(spindashFriction);
			}
		}
		else
		{
			if (spindashTimer > 0)
			{
				spindash(spindashTimer);
			}
			spindashTimer = 0;
			storedSpindashSpeed = 0;
		}

		if (((actionInput && !previousActionInput) || (action2Input && !previousAction2Input)))
		{
			if (isBall)
			{
				spindashReleaseTimer = spindashReleaseTimerMax;
				spindashRestartDelay = spindashRestartDelayMax;
			}

			isBall = false;
		}
	}
	else //In the air
	{
		if (jumpInput && !previousJumpInput && homingAttackTimer == -1 && (isJumping || isBall || isBouncing))
		{
			homingAttack();
		}

		if (actionInput && !previousActionInput && (isJumping || isBall) && !isBouncing && homingAttackTimer == -1 && !isStomping)
		{
			initiateBounce();
		}

		if (action2Input && !previousAction2Input && (isJumping || isBall) && !isBouncing && homingAttackTimer == -1 && !isStomping)
		{
			initiateStomp();
		}

		isSpindashing = false;
		canStartSpindash = false;
		spindashReleaseTimer = 0;
		spindashRestartDelay = 0;
		spindashTimer = 0;
		storedSpindashSpeed = 0;
		wallStickTimer = wallStickTimerMax;
		if (hoverCount > 0)
		{
			yVel += hoverAccel;
		}

		//if (Keyboard.isKeyDown(Keyboard.KEY_J))
		//{
			//yVel += 0.5f;
		//}
	}

	spindashReleaseTimer = std::max(spindashReleaseTimer - 1, 0);
	spindashRestartDelay = std::max(spindashRestartDelay - 1, 0);
	if (homingAttackTimer > 0)
	{
		homingAttackTimer--;
	}

	onPlanePrevious = onPlane;
	CollisionChecker::setCheckPlayer();
	if (CollisionChecker::checkCollision(getX(), getY(), getZ(), (float)(getX() + (xVel + xVelAir + xDisp)), (float)(getY() + (yVel + yDisp)), (float)(getZ() + (zVel + zVelAir + zDisp))))
	{
		triCol = CollisionChecker::getCollideTriangle();
		colPos = CollisionChecker::getCollidePosition();
		bool bonked = false;
		if (onPlane == false) //Transition from ait to ground
		{
			if (isBouncing)
			{
				bounceOffGround(&(triCol->normal));
			}
			else
			{
				Vector3f speeds = calculatePlaneSpeed((float)((xVel + xVelAir + xDisp)), (float)((yVel + yDisp)), (float)(zVel + zVelAir + zDisp), colPos, &(triCol->normal));
				xVelGround = speeds.x;
				zVelGround = speeds.z;
				isBall = false;
				onPlane = true;
			}

			if (isStomping)
			{
				//if (stompSource != null)
				{
					//stompSource.stop();
				}
				//AudioSources.play(33, getPosition());

				//createStompParticles();
			}
		}
		else //check if you can smoothly transition from previous triangle to this triangle
		{
			float dotProduct = currNorm.dot(&(triCol->normal));
			if (dotProduct < 0.6)
			{
				xVelGround = 0;
				zVelGround = 0;

				bonked = true;
				currNorm.set(0, 1, 0);
			}
			onPlane = true;
		}

		if (!bonked)
		{
			setPosition(colPos);
			currNorm.set(&(triCol->normal));
			increasePosition(currNorm.x * 1.0f, currNorm.y * 1.0f, currNorm.z * 1.0f);
		}

		airTimer = 0;
	}
	else
	{
		increasePosition((float)((xVel + xVelAir + xDisp)), (float)((yVel + yDisp)), (float)((zVel + zVelAir + zDisp)));

		//Check for if there's just a small gap "below" us (relative to the normal of the triangle)
		//NEW: If the second check does pass but it is a wall, we pretend that the check didnt pass
		//Also, if we are in the air, then we can just ignore this second check altogether
		bool checkPassed = false;
		CollisionChecker::setCheckPlayer();
		if (onPlane)
		{
			checkPassed = CollisionChecker::checkCollision(getX(), getY(), getZ(), getX() - currNorm.x*surfaceTension, getY() - currNorm.y*surfaceTension, getZ() - currNorm.z*surfaceTension);
		}
		if (checkPassed)
		{
			float dotProduct = currNorm.dot(&(CollisionChecker::getCollideTriangle()->normal));
			if (dotProduct < 0.6) //It's a wall, pretend the collision check didn't see it
			{
				checkPassed = false;
			}
		}

		//Check again
		if (checkPassed)
		{
			triCol = CollisionChecker::getCollideTriangle();
			colPos = CollisionChecker::getCollidePosition();

			bool bonked = false;
			//check if you can smoothly transition from previous triangle to this triangle
			float dotProduct = currNorm.dot(&(CollisionChecker::getCollideTriangle()->normal));
			if (dotProduct < 0.6)
			{
				xVelGround = 0;
				zVelGround = 0;

				bonked = true;
				currNorm.set(0, 1, 0);
			}

			if (!bonked)
			{
				setPosition(colPos);
				currNorm.set(&(triCol->normal));
				increasePosition(currNorm.x * 1.0f, currNorm.y * 1.0f, currNorm.z * 1.0f);
			}
			airTimer = 0;
			onPlane = true;
		}
		else
		{
			CollisionChecker::falseAlarm();
			airTimer++;
			if (onPlane) //transition from on plane to off plane
			{
				xVelGround = 0;
				zVelGround = 0;
				xVelAir = xVel + xDisp;
				zVelAir = zVel + zDisp;
				yVel += yDisp;
				xVel = 0;
				zVel = 0;
			}
			onPlane = false;
		}
	}

	if (airTimer == 1)
	{
		currNorm.set(0, 1, 0);
	}

	if (getY() < -5)
	{
		inWater = true;
		//waterHeight = 0;
	}

	if (getY() < -100)
	{
		//MainGameLoop.shouldRestartLevel = true;
		//AudioSources.play(34, getPosition());
		return;
	}

	if (!inWater && inWaterPrevious)
	{
		//AudioSources.play(30, getPosition());
		//new Particle(ParticleResources.textureSplash, new Vector3f(getX(), waterHeight + 5, getZ()), new Vector3f(0, 0, 0), 0, 30, 0, 10, 0);
		yVel += 0.4f;
		/*
		float totXVel = xVel + xVelAir;
		float totZVel = zVel + zVelAir;
		int numBubbles = ((int)Math.abs(yVel * 8)) + 18;
		for (int i = 0; i < numBubbles; i++)
		{
			float xOff = (float)(7 * (Math.random() - 0.5));
			float zOff = (float)(7 * (Math.random() - 0.5));
			new Particle(
				ParticleResources.textureBubble,
				new Vector3f(getX() + xOff, waterHeight + 2, getZ() + zOff),
				new Vector3f((float)(Math.random() - 0.5f + totXVel*0.4f),
				(float)(Math.random()*0.3 + 0.2f + yVel*0.3),
					(float)(Math.random() - 0.5f + totZVel*0.4f)),
				0.05f, 60, 0, 4, 0);
		}
		*/
	}

	//underwater friction
	if (inWater && !inWaterPrevious)
	{
		//AudioSources.play(30, getPosition());
		//new Particle(ParticleResources.textureSplash, new Vector3f(getX(), waterHeight + 5, getZ()), new Vector3f(0, 0, 0), 0, 30, 0, 10, 0);
		/*
		float totXVel = xVel + xVelAir;
		float totZVel = zVel + zVelAir;
		int numBubbles = ((int)Math.abs(yVel * 8)) + 18;
		for (int i = 0; i < numBubbles; i++)
		{
			float xOff = (float)(7 * (Math.random() - 0.5));
			float zOff = (float)(7 * (Math.random() - 0.5));
			new Particle(
				ParticleResources.textureBubble,
				new Vector3f(getX() + xOff, waterHeight + 2, getZ() + zOff),
				new Vector3f((float)(Math.random() - 0.5f + totXVel*0.4f),
				(float)(Math.random()*0.3 + 0.2f - yVel*0.3),
					(float)(Math.random() - 0.5f + totZVel*0.4f)),
				0.05f, 60, 0, 4, 0);
		}
		*/
		yVel = (float)fmax(yVel, -1);
		xVelGround *= 0.75f;
		zVelGround *= 0.75f;
		xVelAir *= 0.75f;
		zVelAir *= 0.75f;
	}

	if (inWater)
	{

		xVelGround *= 0.987f;
		zVelGround *= 0.987f;
		xVelAir *= 0.987f;
		zVelAir *= 0.987f;
	}

	if (specialInput && !previousSpecialInput && !isLightdashing)
	{
		isLightdashing = true;
	}

	if (isLightdashing)
	{
		attemptLightdash();
	}

	isGettingExternallyMoved = false;
	xDisp = 0;
	yDisp = 0;
	zDisp = 0;

	//animate();

	inWaterPrevious = inWater;
	inWater = false;
}

std::list<TexturedModel*>* Player::getModels()
{
	return &Player::models;
}

void Player::loadStaticModels()
{
	if (Player::models.size() > 0)
	{
		//std::fprintf(stdout, "Player models gone astray\n");
		return;
	}

	std::fprintf(stdout, "Loading player models\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/WanamaDage/", "WanamaDage.obj");
	for (auto newModel : (*newModels))
	{
		Player::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void Player::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting player models...\n");
	for (auto model : Player::models)
	{
		model->deleteMe(); //delete opengl ids
		delete model;
		Global::countDelete++;
	}

	Player::models.clear();
}

void Player::moveMeGround()
{
	Camera* cam = Global::gameCamera;

	if (isBall == false)
	{
		xVelGround += (float)(moveSpeedCurrent*cos(toRadians(cam->getYaw() + movementAngle)));
		zVelGround += (float)(moveSpeedCurrent*sin(toRadians(cam->getYaw() + movementAngle)));
	}
	else
	{
		xVelGround += (float)(moveSpeedCurrent*cos(toRadians(cam->getYaw() + movementAngle)))*0.8f;
		zVelGround += (float)(moveSpeedCurrent*sin(toRadians(cam->getYaw() + movementAngle)))*0.8f;
	}

	float currSpeed = (float)sqrt((xVelGround*xVelGround) + (zVelGround*zVelGround));
	float currDir = (float)toDegrees(atan2(zVelGround, xVelGround));

	if (moveSpeedCurrent > 0.01 && currSpeed > 0.5)
	{
		float worldSpaceMovementAngle = cam->getYaw() + movementAngle;
		float diff = compareTwoAngles(worldSpaceMovementAngle, currDir);

		float newDiff = diff / 8;

		float newAngle = currDir + newDiff;

		if (fabs(diff) > 120)
		{
			xVelGround *= 0.97f;
			zVelGround *= 0.97f;
		}
		else
		{
			xVelGround = (float)(currSpeed*cos(toRadians(newAngle)));
			zVelGround = (float)(currSpeed*sin(toRadians(newAngle)));
		}
	}
}

void Player::setMovementInputs()
{
	jumpInput = INPUT_JUMP;
	actionInput = INPUT_ACTION;
	action2Input = INPUT_ACTION2;
	shoulderInput = INPUT_SHOULDER;
	selectInput = INPUT_SELECT;
	specialInput = INPUT_SPECIAL;

	previousJumpInput = INPUT_PREVIOUS_JUMP;
	previousActionInput = INPUT_PREVIOUS_ACTION;
	previousAction2Input = INPUT_PREVIOUS_ACTION2;
	previousShoulderInput = INPUT_PREVIOUS_SHOULDER;
	previousSelectInput = INPUT_PREVIOUS_SELECT;
	previousSpecialInput = INPUT_PREVIOUS_SPECIAL;

	movementInputX = INPUT_X;
	movementInputY = INPUT_Y;
	cameraInputX = INPUT_X2;
	cameraInputY = INPUT_Y2;

	zoomInput = INPUT_ZOOM;

	float inputMag = (float)sqrt(movementInputX*movementInputX + movementInputY*movementInputY);
	moveSpeedCurrent = moveAcceleration*inputMag;
	moveSpeedAirCurrent = moveAccelerationAir*inputMag;
	movementAngle = (float)toDegrees(atan2(movementInputY, movementInputX));

	if (canMove == false || hitTimer > 0)
	{
		jumpInput = false;
		actionInput = false;
		action2Input = false;
		shoulderInput = false;
		selectInput = false;
		specialInput = false;
		previousJumpInput = false;
		previousActionInput = false;
		previousAction2Input = false;
		previousShoulderInput = false;
		previousSelectInput = false;
		previousSpecialInput = false;
		movementInputX = 0;
		movementInputY = 0;
		moveSpeedCurrent = 0;
		moveSpeedAirCurrent = 0;
		movementAngle = 0;
	}
}

void Player::checkSkid()
{
	bool prevSkid = isSkidding;
	isSkidding = false;
	if (currNorm.y > 0.8)
	{
		float degAngle = movementAngle;

		degAngle = (float)fmod(-degAngle - cameraYawTarget, 360);

		if (degAngle < 0)
		{
			degAngle += 360;
		}

		float myAngle = getRotY();

		if (myAngle < 0)
		{
			myAngle += 360;
		}

		if ((abs(myAngle - degAngle) <= 220) && abs(myAngle - degAngle) >= 140)
		{
			if (movementInputX != 0 || movementInputY != 0)
			{
				isSkidding = true;
				float currSpeed = xVel*xVel + zVel*zVel;
				if (!prevSkid && onPlane && currSpeed > 2)
				{
					//AudioSources.play(9, getPosition());
				}
			}
		}
	}
}

void Player::applyFrictionAir()
{
	float mag = (float)sqrt((xVelGround*xVelGround) + (zVelGround*zVelGround));
	if (mag != 0)
	{
		int before = sign(zVelGround);
		zVelGround -= (((frictionAir)*(zVelGround)) / (mag));
		int after = sign(zVelGround);
		if (before != after)
		{
			zVelGround = 0;
		}
		before = sign(xVelGround);
		xVelGround -= (((frictionAir)*(xVelGround)) / (mag));
		after = sign(xVelGround);
		if (before != after)
		{
			xVelGround = 0;
		}
	}

	mag = (float)sqrt((xVelAir*xVelAir) + (zVelAir*zVelAir));
	if (mag != 0)
	{
		int before = sign(zVelAir);
		zVelAir -= (((frictionAir)*(zVelAir)) / (mag));
		int after = sign(zVelAir);
		if (before != after)
		{
			zVelAir = 0;
		}
		before = sign(xVelAir);
		xVelAir -= (((frictionAir)*(xVelAir)) / (mag));
		after = sign(xVelAir);
		if (before != after)
		{
			xVelAir = 0;
		}
	}
}

void Player::moveMeAir()
{
	Camera* cam = Global::gameCamera;
	xVelAir += (float)(moveSpeedAirCurrent*cos(toRadians(cam->getYaw() + movementAngle)));
	zVelAir += (float)(moveSpeedAirCurrent*sin(toRadians(cam->getYaw() + movementAngle)));

	float currSpeed = (float)sqrt((xVelAir*xVelAir) + (zVelAir*zVelAir));
	float currDir = (float)toDegrees(atan2(zVelAir, xVelAir));

	if (moveSpeedAirCurrent > 0.01 && currSpeed > 0.5)
	{
		float worldSpaceMovementAngle = cam->getYaw() + movementAngle;
		float diff = compareTwoAngles(worldSpaceMovementAngle, currDir);

		float newDiff = diff / 8;

		float newAngle = currDir + newDiff;

		xVelAir = (float)(currSpeed*cos(toRadians(newAngle)));
		zVelAir = (float)(currSpeed*sin(toRadians(newAngle)));

		float factor = 1 - (abs(diff) / 900);
		xVelAir *= factor;
		zVelAir *= factor;
	}
}

void Player::limitMovementSpeedAir()
{
	float myspeed = (float)sqrt(xVelAir*xVelAir + zVelAir*zVelAir);
	if (myspeed > airSpeedLimit)
	{
		xVelAir = (xVelAir*((myspeed - slowDownAirRate) / (myspeed)));
		zVelAir = (zVelAir*((myspeed - slowDownAirRate) / (myspeed)));
	}
}

void Player::limitMovementSpeed(float limit)
{
	if (isBall)
	{
		limit = limit*0.1f;
	}

	float myspeed = (float)sqrt(xVelGround*xVelGround + zVelGround*zVelGround);
	if (myspeed > limit)
	{
		xVelGround = xVelGround*((myspeed - slowDownRate) / (myspeed));
		zVelGround = zVelGround*((myspeed - slowDownRate) / (myspeed));
	}
}

void Player::applyFriction(float frictionToApply)
{
	if (isBall)
	{
		frictionToApply *= 0.11f;
	}

	float mag = (float)sqrt((xVelGround*xVelGround) + (zVelGround*zVelGround));
	if (mag != 0)
	{
		int before = sign(zVelGround);
		zVelGround -= (((frictionToApply)*(zVelGround)) / (mag));
		int after = sign(zVelGround);
		if (before != after)
		{
			zVelGround = 0;
		}
		before = sign(xVelGround);
		xVelGround -= (((frictionToApply)*(xVelGround)) / (mag));
		after = sign(xVelGround);
		if (before != after)
		{
			xVelGround = 0;
		}
	}
}

void Player::calcSpindashAngle()
{
	Camera* cam = Global::gameCamera;
	float inputMag = (float)sqrt(movementInputX*movementInputX + movementInputY*movementInputY);
	if (inputMag >= 0.3)
	{
		spindashAngle = (float)((toRadians(-cam->getYaw() - movementAngle)));
	}
	else
	{
		spindashAngle = (float)((toRadians(getRotY())));
	}
}

void Player::spindash(int timer)
{
	float mag = spindashPower*timer;
	float dx = (float)cos(spindashAngle)*mag;
	float dz = -(float)sin(spindashAngle)*mag;

	float xspd = xVelGround;//+dx;
	float zspd = zVelGround;//+dz;
	float totalSpd = (float)sqrt(xspd*xspd + zspd*zspd);

	float factor = (float)std::fmin(1, 6.5f / totalSpd);
	xVelGround += dx*factor;
	zVelGround += dz*factor;

	float newSpeed = (float)sqrt(xVelGround*xVelGround + zVelGround*zVelGround);

	if (newSpeed < storedSpindashSpeed)
	{
		xVelGround = (float)cos(spindashAngle)*storedSpindashSpeed;
		zVelGround = -(float)sin(spindashAngle)*storedSpindashSpeed;
	}

	isBall = true;
	//AudioSources.play(8, getPosition());
	storedSpindashSpeed = 0;
}

void Player::homingAttack()
{
	Camera* cam = Global::gameCamera;

	float homingPower = 5.5f;
	float angle = -cam->getYaw() - movementAngle;
	if (moveSpeedCurrent < 0.05)
	{
		angle = getRotY();
	}

	if (characterID == 2)
	{
		bool targetNearest = false;
		float closestMatchingAngle = 360;
		float stickAngle = -cam->getYaw() - movementAngle;

		if (moveSpeedCurrent < 0.05)
		{
			angle = getRotY();
			targetNearest = true;
		}

		Entity* closest = nullptr;
		float dist = 12000; //Homing attack range. Distance squared
		float myX = position.x;
		float myZ = position.z;
		float myY = position.y;
		/*
		for (Entity e : MainGameLoop.gameEntities)
		{
			if (e instanceof Motobug ||
				e instanceof ItemCapsule ||
				e instanceof RhinoTank ||
				e instanceof Spinner ||
				e instanceof Spring)
			{
				float xDiff = e.getX() - myX;
				float zDiff = e.getZ() - myZ;
				float yDiff = myY - e.getY();
				float thisDist = xDiff*xDiff + zDiff*zDiff + yDiff*yDiff;

				if (targetNearest)
				{
					if (yDiff > -6 && thisDist < dist)
					{
						dist = thisDist;
						closest = e;
					}
				}
				else
				{
					if (thisDist < dist)
					{
						//calculate angle to this target
						float toTargetAngle = (float)Math.toDegrees(Math.atan2(zDiff, -xDiff)) + 180;
						//calculate difference in angles
						float angleDiff = Math.abs(compareTwoAngles(stickAngle, toTargetAngle));

						if (angleDiff < 60)
						{
							if (yDiff > -6 && angleDiff < closestMatchingAngle)
							{
								closestMatchingAngle = angleDiff;
								closest = e;
							}
						}
					}
				}
			}
		}*/

		if (closest != nullptr)
		{
			/*
			float xDiff = -(myX - closest.getX());
			float zDiff = -(myZ - closest.getZ());
			float yDiff = -(myY - closest.getY());

			Vector3f unitDir = new Vector3f(xDiff, yDiff + 3.5f, zDiff);
			unitDir = unitDir.normalise(unitDir);
			homingPower = 6.7f;

			unitDir.x *= homingPower;
			unitDir.y *= homingPower;
			unitDir.z *= homingPower;

			xVelAir = unitDir.x;
			yVel = unitDir.y;
			zVelAir = unitDir.z;
			*/
		}
		else
		{
			xVelAir = (float)cos(toRadians(angle))*homingPower;
			zVelAir = -(float)sin(toRadians(angle))*homingPower;
		}
	}
	else
	{
		xVelAir = (float)cos(toRadians(angle))*homingPower;
		zVelAir = -(float)sin(toRadians(angle))*homingPower;
	}

	homingAttackTimer = homingAttackTimerMax;
	isBall = false;
	isJumping = true;
	isBouncing = false;
	isStomping = false;
	//AudioSources.play(25, getPosition());
}

void Player::initiateBounce()
{
	if (yVel >= -4.5f)
	{
		yVel = -4.5f;
	}
	else
	{
		yVel -= 1;
	}

	hoverCount = 0;

	isBouncing = true;
	isStomping = false;
	isJumping = false;
	isBall = false;
}

void Player::initiateStomp()
{
	if (yVel >= -4.0f)
	{
		yVel = -4.0f;
	}
	else
	{
		yVel -= 2.0f;
	}

	hoverCount = 0;

	isBouncing = false;
	isStomping = true;
	isJumping = false;
	isBall = false;

	//stompSource = AudioSources.play(32, getPosition());
}

void Player::bounceOffGround(Vector3f* surfaceNormal)
{
	Vector3f V = new Vector3f(xVelAir, yVel, zVelAir);
	Vector3f N = new Vector3f(surfaceNormal);
	float b = 0.75f;

	Vector3f Vnew = bounceVector(&V, &N, b);

	xVelAir = Vnew.x;
	yVel = Vnew.y;
	zVelAir = Vnew.z;

	xVel = 0;
	zVel = 0;

	isBall = true;
	isBouncing = false;
	isStomping = false;
	homingAttackTimer = -1;
	hoverCount = 0;
	//AudioSources.play(26, getPosition());
}

//attempt to continue a lightdash
//if lightdash cant continue, sets isLightdashing
//to false
void Player::attemptLightdash()
{/*
	if (MainGameLoop.gameClock % 2 != 0)
	{
		return;
	}
	//find nearest ring
	Ring closest = null;
	float dist = 2000; //distance squared
	float myX = getX();
	float myZ = getZ();
	float myY = getY();
	for (Entity e : MainGameLoop.gameEntities)
	{
		if (e instanceof Ring)
		{
			float xDiff = e.getX() - myX;
			float zDiff = e.getZ() - myZ;
			float yDiff = e.getY() - myY;
			float newDist = xDiff*xDiff + zDiff*zDiff + yDiff*yDiff;
			if (newDist < dist)
			{
				dist = newDist;
				closest = (Ring)e;
			}
		}
	}


	//check nearest distance
	//System.out.println("dist = "+dist);
	//passes threshold?
	if (dist < 2000)
	{
		onPlane = false;

		xVel = 0;
		zVel = 0;
		relativeXVel = 0;
		relativeZVel = 0;

		//set xVelAir and zVelAir to the direction to the ring
		Vector3f diff = new Vector3f(closest.getX() - myX, closest.getY() - myY, closest.getZ() - myZ);
		diff = diff.normalise(null);

		xVelAir = diff.x * 5;
		zVelAir = diff.z * 5;
		yVel = diff.y * 5;

		//move to ring location
		setX(closest.getX());
		setY(closest.getY());
		setZ(closest.getZ());
	}
	else
	{
		//doesnt pass threshold?
		isLightdashing = false;
	}*/
}

void Player::adjustCamera()
{
	cameraRadius += (cameraRadiusTarget - cameraRadius) / 20;

	cameraRadiusTarget += zoomInput;
	cameraRadiusTarget = fmax(cameraRadiusZoom, cameraRadiusTarget);
	cameraRadiusTarget = fmin(cameraRadiusZoomOut, cameraRadiusTarget);

	Camera* cam = Global::gameCamera;
	Vector3f* camPos = cam->getPosition();

	//if (!firstPerson && !MainGameLoop.freeCamera)
	//{
		//float xDiff = camPos->x - position.x;
		//float zDiff = camPos->z - position.z;
		//float angleRad = (float)toRadians(getRotY());
		//float newZ = (float)(-(zDiff)*cos(angleRad) - (xDiff)*sin(angleRad));
		//float newX = (float)((xDiff)*Math.cos(angleRad) - (zDiff)*Math.sin(angleRad));

		//cameraYawTarget -= (newZ / 65);
	//}


	cameraPitchTarget += cameraInputY;
	cameraYawTarget   += cameraInputX;


	cam->setYaw(cam->getYaw() + (cameraYawTarget - cam->getYaw()) / cameraLaziness);
	cam->setPitch(cam->getPitch() + (cameraPitchTarget - cam->getPitch()) / cameraLaziness);



	Vector3f headPos(
		position.x + currNorm.x*headHeight,
		position.y + currNorm.y*headHeight,
		position.z + currNorm.z*headHeight);

	Vector3f newCamPos(
		headPos.x + (float)(cos(toRadians(cam->getYaw() + 90))*(cameraRadius*(cos(toRadians(cam->getPitch()))))),
		headPos.y - (float)(sin(toRadians(cam->getPitch() + 180))*cameraRadius),
		headPos.z + (float)(sin(toRadians(cam->getYaw() + 90))*(cameraRadius*(cos(toRadians(cam->getPitch()))))));

	/*
	if (CollisionChecker.checkCollision(getPosition(), headPos) == true)
	{
		Vector3f colPos = CollisionChecker.getCollidePosition();

		Vector3f diff = Vector3f.sub(colPos, getPosition(), null);
		float newHeadHeight = diff.length() - 1;

		//System.out.println("headhgith = "+newHeadHeight);

		headPos = new Vector3f(getPosition().getX() + currNorm.x*newHeadHeight,
			getPosition().getY() + currNorm.y*newHeadHeight,
			getPosition().getZ() + currNorm.z*newHeadHeight);
	}
	else if (CollisionChecker.checkCollision(headPos, camPos) == true)
	{
		//System.out.println("collision");
		Vector3f colPos = CollisionChecker.getCollidePosition();

		Vector3f diff = Vector3f.sub(colPos, camPos, null);
		float newRadius = (cameraRadius - 4) - diff.length();

		camPos = new Vector3f(
			headPos.x + (float)(Math.cos(Math.toRadians(cam.getYaw() + 90))*(newRadius*(Math.cos(Math.toRadians(cam.getPitch()))))),
			headPos.y - (float)(Math.sin(Math.toRadians(cam.getPitch() + 180))*newRadius),
			headPos.z + (float)(Math.sin(Math.toRadians(cam.getYaw() + 90))*(newRadius*(Math.cos(Math.toRadians(cam.getPitch()))))));

	}
	*/

	cam->setPosition(&newCamPos);

	//if (zoomInput > 0)
	{
		//firstPerson = true;
	}
	//else if (zoomInput < 0)
	{
		//firstPerson = false;
	}

	//if (firstPerson == true)
	{
		//cam.setPosition(headPos);
	}
}