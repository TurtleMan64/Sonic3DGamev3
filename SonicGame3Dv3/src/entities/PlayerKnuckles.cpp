#include <list>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "entities.h"
#include "controllableplayer.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "playerknuckles.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../toolbox/input.h"
#include "../toolbox/maths.h"
#include "camera.h"
#include "../collision/collisionchecker.h"
#include "../collision/triangle3d.h"
#include "../animation/body.h"
#include "../animation/limb.h"
#include "../animation/animationresources.h"
#include "skysphere.h"
#include "../entities/ring.h"
#include "maniaknucklesmodel.h"
#include "../audio/audioplayer.h"
#include "../audio/source.h"
#include "../particles/particle.h"
#include "../particles/particleresources.h"
#include "stage.h"
#include "shieldmagnet.h"
#include "shieldgreen.h"
#include "../toolbox/mainmenu.h"

std::list<TexturedModel*> PlayerKnuckles::modelBody;
std::list<TexturedModel*> PlayerKnuckles::modelHead;
std::list<TexturedModel*> PlayerKnuckles::modelLeftHumerus;
std::list<TexturedModel*> PlayerKnuckles::modelLeftForearm;
std::list<TexturedModel*> PlayerKnuckles::modelLeftHand;
std::list<TexturedModel*> PlayerKnuckles::modelLeftThigh;
std::list<TexturedModel*> PlayerKnuckles::modelLeftShin;
std::list<TexturedModel*> PlayerKnuckles::modelLeftFoot;
std::list<TexturedModel*> PlayerKnuckles::modelRightHumerus;
std::list<TexturedModel*> PlayerKnuckles::modelRightForearm;
std::list<TexturedModel*> PlayerKnuckles::modelRightHand;
std::list<TexturedModel*> PlayerKnuckles::modelRightThigh;
std::list<TexturedModel*> PlayerKnuckles::modelRightShin;
std::list<TexturedModel*> PlayerKnuckles::modelRightFoot;

ManiaKnucklesModel* PlayerKnuckles::maniaKnuckles;

int PlayerKnuckles::characterID = 4;

extern InputStruct Inputs;

PlayerKnuckles::PlayerKnuckles(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	currNorm.x = 0;
	currNorm.y = 1;
	currNorm.z = 0;
	xDisp = 0;
	yDisp = 0;
	zDisp = 0;
	setVisible(false); //Our limbs are what will be visible
	PlayerKnuckles::maniaKnuckles = nullptr;
	createLimbs();
}

void PlayerKnuckles::step()
{
	animCount++;
	if (getY() < -5)
	{
		inWater = true;
		waterHeight = 0;
	}

	setMovementInputs();
	adjustCamera();
	checkSkid();

	iFrame = std::max(0, iFrame-1);
	hitTimer = std::max(0, hitTimer-1);
	canMoveTimer = std::max(0, canMoveTimer - 1);
	deadTimer = std::max(-1, deadTimer - 1);
	canGlideTimer = std::max(0, canGlideTimer-1);
	punchingTimer = std::max(0, punchingTimer-1);
	drillDiveAudioTimer = std::max(0, drillDiveAudioTimer-1);
	invincibleTimer = std::max(0,  invincibleTimer-1);


	if (diggingTimer == 1 && !isClimbing)
	{
		popOffWall();
	}

	diggingTimer = std::max(0, diggingTimer-1);

	dropDashCharge = std::fmaxf(0, dropDashCharge-dropDashChargeDecrease);

	if (deadTimer == 59)
	{
		Vector3f partVel(0, 0, 0);
		new Particle(ParticleResources::textureBlackFadeOut, Global::gameCamera->getFadePosition1(), &partVel, 0, 66, 0, 400, 0, true);
	}
	else if (deadTimer == 0)
	{
		Global::shouldLoadLevel = true;
	}

	if (invincibleTimer != 0)
	{
		Vector3f center = Global::gamePlayer->getCenterPosition();

		for (int i = 0; i < 2; i++)
		{
			Vector3f off = randomPointOnSphere();
			off.scale(8);
			Vector3f pos = center + off;
			off.scale(1/16.0f);
			new Particle(ParticleResources::textureSparkleYellow, &pos, &off,
					0, 5, 0, 3, -(3.0f / 5.0f), false);
			off.scale(-16.0f);
			pos = center + off;
			off.scale(1/16.0f);
			new Particle(ParticleResources::textureSparkleGreen, &pos, &off,
					0, 5, 0, 3, -(3.0f / 5.0f), false);

			off = randomPointOnSphere();
			off.scale(8);
			pos = center + off;
			off.scale(1/16.0f);
			new Particle(ParticleResources::textureSparkleRed, &pos, &off,
					0, 5, 0, 3, -(3.0f / 5.0f), false);
			off.scale(-16.0f);
			pos = center + off;
			off.scale(1/16.0f);
			new Particle(ParticleResources::textureSparkleBlue, &pos, &off,
					0, 5, 0, 3, -(3.0f / 5.0f), false);

			off = randomPointOnSphere();
			off.scale(8);
			pos = center + off;
			off.scale(1/16.0f);
			new Particle(ParticleResources::textureSparkleLightBlue, &pos, &off,
					0, 5, 0, 3, -(3.0f / 5.0f), false);
			off.scale(-16.0f);
			pos = center + off;
			off.scale(1/16.0f);
			new Particle(ParticleResources::textureSparkleWhite, &pos, &off,
					0, 5, 0, 3, -(3.0f / 5.0f), false);
		}
	}

	if (punchingTimer == 1)
	{
		isPunching = false;
	}

	if (diggingTimer == 0)
	{
		isDigging = false;
	}

	if (diggingTimer % 8 == 1)
	{
		AudioPlayer::play(43, getPosition());
	}

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

		if (inWater == false)
		{
			if (isGliding)
			{
				yVel = fmaxf(yVel-glideGravity, glideTerminalVelocity);
			}
			else
			{
				yVel -= gravity;
			}
		}
	}
	else //on ground
	{
		hitTimer = 0;

		xVelAir = 0;
		zVelAir = 0;
		applyFriction(frictionGround);
		moveMeGround();
		if (speedShoesTimer == 0)
		{
			limitMovementSpeed(normalSpeedLimit);
		}
		else
		{
			limitMovementSpeed(normalSpeedLimit*2);
		}
	}

	if (isBall)
	{
		xVelGround += currNorm.x*slopeAccel*ballSlopeAccelFactor;
		zVelGround += currNorm.z*slopeAccel*ballSlopeAccelFactor;
	}
	else
	{
		xVelGround += currNorm.x*slopeAccel;
		zVelGround += currNorm.z*slopeAccel;
	}

	if (isPunching)
	{
		xVelGround = punchGroundVelX;
		zVelGround = punchGroundVelZ;
	}

	if (isClimbing)
	{
		float fakeCamYaw = toDegrees(atan2f(currNorm.z, currNorm.x))-90;

		float inputMag = sqrtf(movementInputX*movementInputX + movementInputY*movementInputY);

		xVelGround = climbSpeed*inputMag*cosf(toRadians(fakeCamYaw + movementAngle));
		zVelGround = climbSpeed*inputMag*sinf(toRadians(fakeCamYaw + movementAngle));

		wallStickTimer = wallStickTimerMax;
	}

	if (isDigging)
	{
		xVelGround = 0;
		zVelGround = 0;

		wallStickTimer = wallStickTimerMax;

		int dirtToMake = 5;
		while (dirtToMake > 0)
		{
			Vector3f pos(getX()-currNorm.x, getY()-currNorm.y, getZ()-currNorm.z);
			Vector3f vel(currNorm);
			vel.x += (Maths::random()-0.5f);
			vel.y += (Maths::random()-0.5f);
			vel.z += (Maths::random()-0.5f);

			new Particle(ParticleResources::textureDirt, &pos, &vel, 0.08f, 60, 0, 2*Maths::random()+0.5f, 0, false);

			dirtToMake--;
		}
	}

	float inputX = xVelGround;
	float inputY = zVelGround;
	float mag = sqrtf(inputX*inputX + inputY*inputY);

	float inputDir = (atan2f(inputY, inputX));
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
		isDropDashing = false;
		justBounced = false;
		isGliding = false;
		isDrillDiving = false;
		canGlideTimer = 0;
		homingAttackTimer = -1;
		dropDashCharge = 0.0f;
		float speed = sqrtf(xVelGround*xVelGround + zVelGround*zVelGround);
		if (currNorm.y <= wallThreshold && speed < wallSpeedStickThreshold) //Arbitrary constants
		{
			wallStickTimer--;
		}
		else
		{
			wallStickTimer = wallStickTimerMax;
		}

		xVel = Ax;
		yVel = Ay;
		zVel = Az;
		xVelAir = 0;
		zVelAir = 0;
		hoverCount = hoverLimit;

		if (combo > 1)
		{
			Global::gameScore += 100*(combo-1);
		}
		combo = 0;

		if (wallStickTimer < 0)
		{
			popOffWall();
		}

		if (isClimbing && currNorm.y > climbSlopeStop)
		{
			isClimbing = false;
		}

		if (jumpInput && !previousJumpInput && !isPunching)
		{
			increasePosition(currNorm.x * 2, currNorm.y * 2, currNorm.z * 2);
			xVelAir = xVel + currNorm.x*jumpPower + xDisp;
			zVelAir = zVel + currNorm.z*jumpPower + zDisp;
			yVel = yVel + currNorm.y*jumpPower + yDisp;
			xVel = 0;
			zVel = 0;
			xVelGround = 0;
			zVelGround = 0;
			isJumping = true;
			onPlane = false;
			isClimbing = false;

			AudioPlayer::play(12, getPosition());
		}

		if (speed < autoUnrollThreshold)
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

		if (spindashRestartDelay > 0)
		{
			if ((actionInput && !previousActionInput) || (action2Input && !previousAction2Input))
			{
				bufferedSpindashInput = true;
			}
		}

		if ((((actionInput && !previousActionInput) || (action2Input && !previousAction2Input)) && canStartSpindash) 
		  || (bufferedSpindashInput && (actionInput || action2Input) && canStartSpindash))
		{
			if (!isSpindashing)
			{
				//storedSpindashSpeed = (float)sqrt(xVelGround*xVelGround + zVelGround*zVelGround);
			}
			//isSpindashing = true;
		}

		if (!actionInput && !action2Input)
		{
			isSpindashing = false;
			bufferedSpindashInput = false;
		}

		if (isSpindashing)
		{
			spindashTimer = std::min(spindashTimer + 1, spindashTimerMax);
			if (spindashTimer == 1)
			{
				AudioPlayer::play(14, getPosition());
			}
			isSpindashing = true;
			calcSpindashAngle();
			if (spindashTimer > spindashDelay)
			{
				//TODO: testing this
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
			//if (isBall)
			{
				//spindashReleaseTimer = spindashReleaseTimerMax;
				//spindashRestartDelay = spindashRestartDelayMax;
			}

			//isBall = false;
		}

		if (((actionInput && !previousActionInput) || (action2Input && !previousAction2Input)))
		{
			if (!isPunching && !isClimbing)
			{
				if (speed < punchSpeedThreshold)
				{
					punchType = 0;
				}
				else
				{
					punchType = 1;
				}
				isPunching = true;
				AudioPlayer::play(33, getPosition());
				punchingTimer = punchingTimerMax;
				float speedScale = 1;
				float newSpd = sqrtf(xVelGround*xVelGround+zVelGround*zVelGround);

				if (newSpd < 0.001f)
				{
					punchGroundVelX =  punchSpeedSlow*cosf(toRadians(getRotY()));
					punchGroundVelZ = -punchSpeedSlow*sinf(toRadians(getRotY()));
				}
				else
				{
					switch (punchType)
					{
					case 0:
						speedScale = punchSpeedSlow/speed; //this might need to be switched
						break;

					default:
						speedScale = punchSpeedFast/speed;
						break;
					}
					punchGroundVelX = xVelGround*speedScale;
					punchGroundVelZ = zVelGround*speedScale;
				}
				xVelGround = punchGroundVelX;
				zVelGround = punchGroundVelZ;
			}

			if (isClimbing)
			{
				if (triCol->isDiggable())
				{
					isDigging = true;
					diggingTimer = diggingTimerMax;
					canMoveTimer = diggingTimerMax;
					xVelGround = 0;
					zVelGround = 0;
				}
			}
		}
	}
	else //In the air
	{
		if (jumpInput && !previousJumpInput && homingAttackTimer == -1 && (isJumping || isBall || isBouncing) && !isDropDashing)
		{
			//homingAttack();
		}

		if (actionInput && !previousActionInput && (isJumping || isGliding) && !isDrillDiving && !inWater)
		{
			isDrillDiving = true;
			isGliding = false;
			yVel = drillDiveSpeed;
			xVelAir = xVelAir*0.95f;
			zVelAir = zVelAir*0.95f;
			canGlideTimer = 0;
			hoverCount = 0;
			drillDiveAudioTimer = drillDiveAudioTimerMax;

			sourceDrillDive = AudioPlayer::play(31, getPosition(), 1, false);
		}

		if (action2Input && !previousAction2Input && (isJumping || isBall) && !isBouncing && homingAttackTimer == -1 && !isStomping && !isDropDashing)
		{
			//initiateStomp();
		}

		if (jumpInput && !previousJumpInput && canGlideTimer == 0 && !isGliding && !inWater)
		{
			isGliding = true;
			isDrillDiving = false;
			yVel = 0;
			hoverCount = 0;

			float currSpd = sqrtf(xVelAir*xVelAir + zVelAir*zVelAir);

			if (currSpd < glideSpeedLimit*0.6f)
			{
				xVelAir =  0.6f*glideSpeedLimit*cosf(toRadians(getRotY()));
				zVelAir = -0.6f*glideSpeedLimit*sinf(toRadians(getRotY()));
			}
			else
			{
				xVelAir =  currSpd*cosf(toRadians(getRotY()));
				zVelAir = -currSpd*sinf(toRadians(getRotY()));
			}

			sourceGlide = AudioPlayer::play(32, getPosition(), 1, true);
		}

		if (jumpInput && isGliding)
		{
			canGlideTimer = canGlideTimerMax;
		}

		if (!jumpInput && isGliding)
		{
			isGliding = false;
			isJumping = true;
			hoverCount = 0;
		}

		if (yVel > 0 && isGliding)
		{
			isGliding = false;
			isJumping = false;
			hoverCount = 30;
		}

		if (yVel > 0 && isDrillDiving)
		{
			isDrillDiving = false;
			isJumping = false;
			hoverCount = 30;
		}

		isSpindashing = false;
		isPunching = false;
		isClimbing = false;
		isDigging = false;
		diggingTimer = 0;
		punchingTimer = 0;
		canStartSpindash = false;
		bufferedSpindashInput = false;
		spindashReleaseTimer = 0;
		spindashRestartDelay = 0;
		spindashTimer = 0;
		storedSpindashSpeed = 0;
		climbAnimTime = 0;
		wallStickTimer = wallStickTimerMax;
		if (hoverCount > 0)
		{
			yVel += hoverAccel;
		}

		//TODO: make new buttons for this
		if (specialInput && !previousSpecialInput && (isJumping || isBall) && !isBouncing && homingAttackTimer == -1 && !isStomping)
		{
			//isDropDashing = true;
			//dropDashCharge += dropDashChargeIncrease;
			
			//AudioPlayer::play(14, getPosition());
		}
	}

	spindashReleaseTimer = std::max(spindashReleaseTimer - 1, 0);
	spindashRestartDelay = std::max(spindashRestartDelay - 1, 0);
	if (homingAttackTimer > 0)
	{
		homingAttackTimer--;
	}

	if (drillDiveAudioTimer == 1 && isDrillDiving)
	{
		sourceDrillDive = AudioPlayer::play(31, getPosition(), 1, false);
		//stop previous one?
		drillDiveAudioTimer = drillDiveAudioTimerMax;
	}

	if (sourceGlide != nullptr)
	{
		sourceGlide->setPosition(getX(), getY(), getZ());

		if (!isGliding)
		{
			sourceGlide->stop();
			sourceGlide = nullptr;
		}
	}
	if (sourceDrillDive != nullptr)
	{
		sourceDrillDive->setPosition(getX(), getY(), getZ());

		if (!isDrillDiving)
		{
			sourceDrillDive->stop();
			sourceDrillDive = nullptr;
		}
	}

	onPlanePrevious = onPlane;

	CollisionChecker::setCheckPlayer();
	if (CollisionChecker::checkCollision(getX(), getY(), getZ(), (getX() + (xVel + xVelAir + xDisp)), (getY() + (yVel + yDisp)), (getZ() + (zVel + zVelAir + zDisp))))
	{
		triCol = CollisionChecker::getCollideTriangle();
		colPos = CollisionChecker::getCollidePosition();
		bool bonked = false;
		if (onPlane == false) //Transition from air to ground
		{
			if (inWater)
			{
				Vector3f currDisp(xVel+xVelAir+xDisp, yVel+yDisp, zVel+zVelAir+zDisp);
				Vector3f parToWall = projectOntoPlane(&currDisp, &(triCol->normal));
				xVelGround = 0;
				zVelGround = 0;
				xVelAir = parToWall.x;
				yVel    = parToWall.y;
				zVelAir = parToWall.z;
			}

			//New idea: if the wall is very steep, check if we are approaching the wall at too flat of an angle.
			//If we are, do a small bounce off the wall sintead of sticking to it.

			bool canStick = true;

			//Is the wall steep?
			if (triCol->normal.y < wallThreshold) //Some arbitrary steepness constant
			{
				//Not sure if I like this...
				canStick = false;
			}

			if (isDrillDiving && (actionInput || action2Input) && triCol->isDiggable() && !isDigging)
			{
				isDigging = true;
				diggingTimer = diggingTimerMax;
				canMoveTimer = diggingTimerMax;

				setPosition(colPos);
				increasePosition(triCol->normal.x, triCol->normal.y, triCol->normal.z);
				onPlane = true;
				isDrillDiving = false;
			}
			else
			{
				if (canStick)
				{
					Vector3f speeds = calculatePlaneSpeed(xVel + xVelAir + xDisp, yVel + yDisp, zVel + zVelAir + zDisp, &(triCol->normal));
					xVelGround = speeds.x;
					zVelGround = speeds.z;
					isBall = false;
					onPlane = true;

					//if (isDropDashing)
					{
						//dropDash(dropDashCharge);
					}
				}
				else
				{
					if (isGliding)
					{
						isGliding = false;
						isClimbing = true;
						onPlane = true;

						canMoveTimer = 16;
					}
					else
					{
						bounceOffGround(&(triCol->normal), cantStickBounceFactor, 18);

						setPosition(colPos);
						increasePosition(triCol->normal.x * 1.5f, triCol->normal.y * 1.5f, triCol->normal.z * 1.5f);

						//canMoveTimer = 8;
						isBall = true;
						isDropDashing = false;
						bonked = true;
					}
				}
			}
		}
		else //check if you can smoothly transition from previous triangle to this triangle
		{
			float dotProduct = currNorm.dot(&(triCol->normal));
			float thresholdToUse = smoothTransitionThreshold;
			if (isClimbing)
			{
				thresholdToUse = smoothClimbTransitionThreshold;
			}

			if (dotProduct < thresholdToUse)
			{
				xVelGround = 0;
				zVelGround = 0;

				bonked = true;

				Vector3f currDisp(xVel + xDisp, yVel + yDisp, zVel + zDisp);

				Vector3f parToWall = projectOntoPlane(&currDisp, &(triCol->normal));

				float sameness = parToWall.length();

				projectOntoPlane(&parToWall, &currNorm);

				Vector3f newGroundSpeeds = calculatePlaneSpeed(parToWall.x, parToWall.y, parToWall.z, &currNorm);

				if (isBall || isSpindashing)
				{
					//bounce off the wall instead of sliding along it
					float reflectFactor = fmaxf(0, fminf(sameness, 1.0f));

					Vector3f bounceV = bounceVector(&currDisp, &(triCol->normal), reflectFactor);
					Vector3f bounceGroundSpeeds = calculatePlaneSpeed(bounceV.x, bounceV.y, bounceV.z, &currNorm);
					xVelGround = bounceGroundSpeeds.x;
					zVelGround = bounceGroundSpeeds.z;
					canMoveTimer = 3;
				}
				else
				{
					//slide along the wall
					if (sameness > 0.2f)
					{
						xVelGround = newGroundSpeeds.x;
						zVelGround = newGroundSpeeds.z;
						canMoveTimer = 3;
						setPosition(colPos);
						increasePosition(triCol->normal.x * 1.0f, triCol->normal.y * 1.0f, triCol->normal.z * 1.0f);
					}
					else
					{
						currNorm.set(0, 1, 0);
					}
				}
			}
			else
			{
				float speedBefore = sqrtf(xVelGround*xVelGround+zVelGround*zVelGround);
				Vector3f directionOG(xVel, yVel, zVel);
				Vector3f newDirection = projectOntoPlane(&directionOG, &(triCol->normal));
				if (newDirection.lengthSquared() != 0)
				{
					newDirection.normalize();
					newDirection.scale(speedBefore);
					Vector3f newSpeeds = calculatePlaneSpeed(newDirection.x, newDirection.y, newDirection.z, &(triCol->normal));
					xVelGround = newSpeeds.x;
					zVelGround = newSpeeds.z;
				}
			}
			onPlane = true;
		}

		if (bonked == false)
		{
			setPosition(colPos);
			currNorm.set(&(triCol->normal));
			increasePosition(currNorm.x * 1.0f, currNorm.y * 1.0f, currNorm.z * 1.0f);
		}

		airTimer = 0;
	}
	else
	{
		increasePosition(((xVel + xVelAir + xDisp)), ((yVel + yDisp)), ((zVel + zVelAir + zDisp)));

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
			float thresholdToUse = smoothTransitionThreshold;
			if (isClimbing)
			{
				thresholdToUse = smoothClimbTransitionThreshold;
			}
			if (dotProduct < thresholdToUse) //It's a wall, pretend the collision check didn't see it
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
			float thresholdToUse = smoothTransitionThreshold;
			if (isClimbing)
			{
				thresholdToUse = smoothClimbTransitionThreshold;
			}
			if (dotProduct < thresholdToUse)
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

	if (getY() < Global::deathHeight)
	{
		die();
	}

	if (!inWater && inWaterPrevious)
	{
		AudioPlayer::play(5, getPosition());
		Vector3f pos(getX(), waterHeight + 5, getZ());
		Vector3f vel(0, 0, 0);
		new Particle(ParticleResources::textureSplash, &pos, &vel, 0, 30, 0, 10, 0, false);
		yVel += waterExitBoost;
		hoverCount = hoverLimit/2;
		
		float totXVel = xVel + xVelAir;
		float totZVel = zVel + zVelAir;
		int numBubbles = ((int)abs(yVel * 8)) + 18;
		for (int i = 0; i < numBubbles; i++)
		{
			float xOff = (7 * (Maths::random() - 0.5f));
			float zOff = (7 * (Maths::random() - 0.5f));

			Vector3f bubPos(
				getX() + xOff,
				waterHeight + 2,
				getZ() + zOff);

			Vector3f bubVel(
				Maths::random() - 0.5f + totXVel*0.4f,
				Maths::random()*0.3f + 0.2f + yVel*0.3f,
				Maths::random() - 0.5f + totZVel*0.4f);

			new Particle(ParticleResources::textureBubble, &bubPos, &bubVel, 0.05f, 60, 0, 4, 0, false);
		}
	}

	//underwater friction
	if (inWater && !inWaterPrevious)
	{
		AudioPlayer::play(5, getPosition());
		Vector3f pos(getX(), waterHeight + 5, getZ());
		Vector3f vel(0, 0, 0);
		new Particle(ParticleResources::textureSplash, &pos, &vel, 0, 30, 0, 10, 0, false);

		float totXVel = xVel + xVelAir;
		float totZVel = zVel + zVelAir;
		int numBubbles = ((int)abs(yVel * 8)) + 18;
		for (int i = 0; i < numBubbles; i++)
		{
			float xOff = (7 * (Maths::random() - 0.5f));
			float zOff = (7 * (Maths::random() - 0.5f));

			Vector3f bubPos(
				getX() + xOff,
				waterHeight + 2,
				getZ() + zOff);

			Vector3f bubVel(
				Maths::random() - 0.5f + totXVel*0.4f,
				Maths::random()*0.3f + 0.2f - yVel*0.3f,
				Maths::random() - 0.5f + totZVel*0.4f);

			new Particle(ParticleResources::textureBubble, &bubPos, &bubVel, 0.05f, 60, 0, 4, 0, false);
		}

		yVel = fmaxf(yVel, waterEntryMaxYVel);
		xVelGround *= waterEntrySlowdown;
		zVelGround *= waterEntrySlowdown;
		xVelAir *= waterEntrySlowdown;
		zVelAir *= waterEntrySlowdown;
	}

	if (inWater)
	{
		xVelGround *= waterDeceleration;
		zVelGround *= waterDeceleration;
		xVelAir *= waterDeceleration;
		zVelAir *= waterDeceleration;

		onPlane = false;
		isGliding = false;
		isDrillDiving = false;
		isBall = false;
		isJumping = false;
		isClimbing = false;
		isPunching = false;
		hoverCount = 0;
		xVelGround = 0;
		zVelGround = 0;
		xVel = 0;
		zVel = 0;

		swimStrokeTimer = std::fmaxf(0, swimStrokeTimer-2.0f);

		yVel = yVel*0.97f;

		if (jumpInput)
		{
			yVel+=0.08f;
		}

		if (actionInput || action2Input)
		{
			yVel-=0.08f;
		}

		if (jumpInput && !previousJumpInput)
		{
			swimStrokeTimer = 100.0f;
		}

		if ((actionInput || action2Input) && !(previousActionInput || previousAction2Input))
		{
			swimStrokeTimer = 100.0f;
		}
	}
	else
	{
		swimStrokeTimer = 0;
	}

	if (specialInput && !previousSpecialInput && !isLightdashing)
	{
		//isLightdashing = true;
	}

	if (isLightdashing)
	{
		attemptLightdash();
	}

	isGettingExternallyMoved = false;
	xDisp = 0;
	yDisp = 0;
	zDisp = 0;

	//adjustCamera();

	animate(); //idea : in animate, when jumping, center the camera at not head height. then add back in the 10 units or whatever you get from jumping

	inWaterPrevious = inWater;
	inWater = false;

	float skyYVal = 0;
	if (Global::gameSkySphere->getFollowsY())
	{
		skyYVal = getY();
	}
	Global::gameSkySphere->setPosition(getX(), skyYVal, getZ());

	switch (Global::levelID)
	{
		case LVL_SPEED_HIGHWAY: Global::gameSkySphere->setPosition(getX(), 4550, getZ()); break;
		case LVL_PUMPKIN_HILL:  Global::gameSkySphere->setPosition(getX(), 2020, getZ()); break;
		default: break;
	}
}

void PlayerKnuckles::addLimbsToGame()
{
	Main_addEntity(myBody);
	Main_addEntity(myHead);
	Main_addEntity(myLeftHumerus);
	Main_addEntity(myLeftForearm);
	Main_addEntity(myLeftHand);
	Main_addEntity(myLeftThigh);
	Main_addEntity(myLeftShin);
	Main_addEntity(myLeftFoot);
	Main_addEntity(myRightHumerus);
	Main_addEntity(myRightForearm);
	Main_addEntity(myRightHand);
	Main_addEntity(myRightThigh);
	Main_addEntity(myRightShin);
	Main_addEntity(myRightFoot);
}

void PlayerKnuckles::removeLimbsFromGame()
{
	Main_deleteEntity(myBody); myBody = nullptr;
	Main_deleteEntity(myHead); myHead = nullptr;
	Main_deleteEntity(myLeftHumerus); myLeftHumerus = nullptr;
	Main_deleteEntity(myLeftForearm); myLeftForearm = nullptr;
	Main_deleteEntity(myLeftHand); myLeftHand = nullptr;
	Main_deleteEntity(myLeftThigh); myLeftThigh = nullptr;
	Main_deleteEntity(myLeftShin); myLeftShin = nullptr;
	Main_deleteEntity(myLeftFoot); myLeftFoot = nullptr;
	Main_deleteEntity(myRightHumerus); myRightHumerus = nullptr;
	Main_deleteEntity(myRightForearm); myRightForearm = nullptr;
	Main_deleteEntity(myRightHand); myRightHand = nullptr;
	Main_deleteEntity(myRightThigh); myRightThigh = nullptr;
	Main_deleteEntity(myRightShin); myRightShin = nullptr;
	Main_deleteEntity(myRightFoot); myRightFoot = nullptr;
}

void PlayerKnuckles::setLimbsVisibility(bool newVisible)
{
	if (myBody == nullptr) return;
	myBody->setVisible(newVisible);
	myHead->setVisible(newVisible);
	myLeftHumerus->setVisible(newVisible);
	myLeftForearm->setVisible(newVisible);
	myLeftHand->setVisible(newVisible);
	myLeftThigh->setVisible(newVisible);
	myLeftShin->setVisible(newVisible);
	myLeftFoot->setVisible(newVisible);
	myRightHumerus->setVisible(newVisible);
	myRightForearm->setVisible(newVisible);
	myRightHand->setVisible(newVisible);
	myRightThigh->setVisible(newVisible);
	myRightShin->setVisible(newVisible);
	myRightFoot->setVisible(newVisible);
}

void PlayerKnuckles::updateLimbs(int animIndex, float time)
{
	if (myBody == nullptr) return;
	myBody->animationIndex = animIndex;
	myHead->animationIndex = animIndex;
	myLeftHumerus->animationIndex = animIndex;
	myLeftForearm->animationIndex = animIndex;
	myLeftHand->animationIndex = animIndex;
	myLeftThigh->animationIndex = animIndex;
	myLeftShin->animationIndex = animIndex;
	myLeftFoot->animationIndex = animIndex;
	myRightHumerus->animationIndex = animIndex;
	myRightForearm->animationIndex = animIndex;
	myRightHand->animationIndex = animIndex;
	myRightThigh->animationIndex = animIndex;
	myRightShin->animationIndex = animIndex;
	myRightFoot->animationIndex = animIndex;
	myBody->update(time);
	myHead->update(time);
	myLeftHumerus->update(time);
	myLeftForearm->update(time);
	myLeftHand->update(time);
	myLeftThigh->update(time);
	myLeftShin->update(time);
	myLeftFoot->update(time);
	myRightHumerus->update(time);
	myRightForearm->update(time);
	myRightHand->update(time);
	myRightThigh->update(time);
	myRightShin->update(time);
	myRightFoot->update(time);
}

void PlayerKnuckles::updateLimbsMatrix()
{
	if (myBody == nullptr) return;
	myBody->updateTransformationMatrix();
	myHead->updateTransformationMatrix();
	myLeftHumerus->updateTransformationMatrix();
	myLeftForearm->updateTransformationMatrix();
	myLeftHand->updateTransformationMatrix();
	myLeftThigh->updateTransformationMatrix();
	myLeftShin->updateTransformationMatrix();
	myLeftFoot->updateTransformationMatrix();
	myRightHumerus->updateTransformationMatrix();
	myRightForearm->updateTransformationMatrix();
	myRightHand->updateTransformationMatrix();
	myRightThigh->updateTransformationMatrix();
	myRightShin->updateTransformationMatrix();
	myRightFoot->updateTransformationMatrix();
}

void PlayerKnuckles::createLimbs()
{
	if (PlayerKnuckles::characterID == 4) //Mania Knuckles
	{
		PlayerKnuckles::maniaKnuckles = new ManiaKnucklesModel;
		INCR_NEW
		Main_addEntity(PlayerKnuckles::maniaKnuckles);

		float s = 1.0f;

		displayHeightOffset = 0.5f;
		myBody =         new Body(&modelBody);
		myHead =         new Limb(&modelHead,         0.97f*s,-0.5f*s,  0,      myBody,   nullptr);        INCR_NEW
		myLeftHumerus =  new Limb(&modelLeftHumerus,  0.6f*s,  0,      -0.8f*s, myBody,   nullptr);        INCR_NEW
		myLeftForearm =  new Limb(&modelLeftForearm,  0,      -1.5f*s,  0,      nullptr,  myLeftHumerus);  INCR_NEW
		myLeftHand =     new Limb(&modelLeftHand,     0,	  -1.3f*s,  0,      nullptr,  myLeftForearm);  INCR_NEW
		myLeftThigh =    new Limb(&modelLeftThigh,   -0.9f*s,  0,      -0.3f*s, myBody,   nullptr);        INCR_NEW
		myLeftShin =     new Limb(&modelLeftShin,     0,	  -1.5f*s,  0,      nullptr,  myLeftThigh);    INCR_NEW
		myLeftFoot =     new Limb(&modelLeftFoot,     0,	  -1.5f*s,  0,      nullptr,  myLeftShin);     INCR_NEW
		myRightHumerus = new Limb(&modelRightHumerus, 0.6f*s,  0,       0.8f*s, myBody,   nullptr);        INCR_NEW
		myRightForearm = new Limb(&modelRightForearm, 0,	  -1.5f*s,  0,      nullptr,  myRightHumerus); INCR_NEW
		myRightHand =    new Limb(&modelRightHand,    0,	  -1.3f*s,  0,      nullptr,  myRightForearm); INCR_NEW
		myRightThigh =   new Limb(&modelRightThigh,  -0.9f*s,  0,       0.3f*s, myBody,   nullptr);        INCR_NEW
		myRightShin =    new Limb(&modelRightShin,    0,	  -1.5f*s,  0,      nullptr,  myRightThigh);   INCR_NEW
		myRightFoot =    new Limb(&modelRightFoot,    0,	  -1.5f*s,  0,      nullptr,  myRightShin);    INCR_NEW

		s = 0.33f;

		myBody->setScale(s);
		myHead->setScale(s);
		myLeftHumerus->setScale(s);
		myLeftForearm->setScale(s);
		myLeftHand->setScale(s);
		myLeftThigh->setScale(s);
		myLeftShin->setScale(s);
		myLeftFoot->setScale(s);
		myRightHumerus->setScale(s);
		myRightForearm->setScale(s);
		myRightHand->setScale(s);
		myRightThigh->setScale(s);
		myRightShin->setScale(s);
		myRightFoot->setScale(s);
	}
	else if (PlayerKnuckles::characterID == 5) //Amy
	{
		//modern
		displayHeightOffset = 1.45f;
		myBody =         new Body(&modelBody); INCR_NEW
		myHead =         new Limb(&modelHead,         0.81f,  0,      0,     myBody,  nullptr);        INCR_NEW
		myLeftHumerus =  new Limb(&modelLeftHumerus,  0.8f,   0,     -1.05f, myBody,  nullptr);        INCR_NEW
		myLeftForearm =  new Limb(&modelLeftForearm,  0,     -1.51f,  0,     nullptr, myLeftHumerus);  INCR_NEW
		myLeftHand =     new Limb(&modelLeftHand,     0,     -1.7f,   0,     nullptr, myLeftForearm);  INCR_NEW
		myLeftThigh =    new Limb(&modelLeftThigh,   -1.06f,  0,     -0.55f, myBody,  nullptr);        INCR_NEW
		myLeftShin =     new Limb(&modelLeftShin,     0,     -1.85f,  0,     nullptr, myLeftThigh);    INCR_NEW
		myLeftFoot =     new Limb(&modelLeftFoot,     0,     -1.8f,   0,     nullptr, myLeftShin);     INCR_NEW
		myRightHumerus = new Limb(&modelRightHumerus, 0.8f,   0,      1.05f, myBody,  nullptr);        INCR_NEW
		myRightForearm = new Limb(&modelRightForearm, 0,     -1.51f,  0,     nullptr, myRightHumerus); INCR_NEW
		myRightHand =    new Limb(&modelRightHand,    0,     -1.7f,   0,     nullptr, myRightForearm); INCR_NEW
		myRightThigh =   new Limb(&modelRightThigh,  -1.06f,  0,      0.55f, myBody,  nullptr);        INCR_NEW
		myRightShin =    new Limb(&modelRightShin,    0,     -1.85f,  0,     nullptr, myRightThigh);   INCR_NEW
		myRightFoot =    new Limb(&modelRightFoot,    0,     -1.8f,   0,     nullptr, myRightShin);    INCR_NEW
	}
	else if (PlayerKnuckles::characterID == 6) //WanamaDage
	{
		displayHeightOffset = 7.7f;
		myBody =         new Body(&modelBody); INCR_NEW
		myHead =         new Limb(&modelHead,         4.835f,  0.715f,  0.0f,  myBody,  nullptr);        INCR_NEW
		myLeftHumerus =  new Limb(&modelLeftHumerus,  3.963f,  0.28f,  -2.73f, myBody,  nullptr);        INCR_NEW
		myLeftForearm =  new Limb(&modelLeftForearm,  0,      -3.7f,    0,     nullptr, myLeftHumerus);  INCR_NEW
		myLeftHand =     new Limb(&modelLeftHand,     0,      -4.18f,   0,     nullptr, myLeftForearm);  INCR_NEW
		myLeftThigh =    new Limb(&modelLeftThigh,   -3.893f,  0.42f,  -1.92f, myBody,  nullptr);        INCR_NEW
		myLeftShin =     new Limb(&modelLeftShin,     0,      -4.42f,   0,     nullptr, myLeftThigh);    INCR_NEW
		myLeftFoot =     new Limb(&modelLeftFoot,     0,      -3.75f,   0,     nullptr, myLeftShin);     INCR_NEW
		myRightHumerus = new Limb(&modelRightHumerus, 3.963f,  0.28f,   2.73f, myBody,  nullptr);        INCR_NEW
		myRightForearm = new Limb(&modelRightForearm, 0,      -3.7f,    0,     nullptr, myRightHumerus); INCR_NEW
		myRightHand =    new Limb(&modelRightHand,    0,      -4.18f,   0,     nullptr, myRightForearm); INCR_NEW
		myRightThigh =   new Limb(&modelRightThigh,  -3.893f,  0.42f,   1.92f, myBody,  nullptr);        INCR_NEW
		myRightShin =    new Limb(&modelRightShin,    0,      -4.42f,   0,     nullptr, myRightThigh);   INCR_NEW
		myRightFoot =    new Limb(&modelRightFoot,    0,      -3.75f,   0,     nullptr, myRightShin);    INCR_NEW
	}
	else if (PlayerKnuckles::characterID == 7) //Pac Man
	{
		displayHeightOffset = 1.95f*2.0f;
		myBody         = new Body(&modelBody);                                                           INCR_NEW
		myHead         = new Limb(&modelHead,         0.0f,    0.0f,    0.0f,  myBody,  nullptr);        INCR_NEW
		myLeftHumerus  = new Limb(&modelLeftHumerus,  0.0f,   -0.2f*1.3f,   -2.85f*1.3f, myBody,  nullptr);        INCR_NEW
		myLeftForearm  = new Limb(&modelLeftForearm,  0,      -1.0f*1.3f,    0,     nullptr, myLeftHumerus);  INCR_NEW
		myLeftHand     = new Limb(&modelLeftHand,     0,      -1.0f*1.3f,    0,     nullptr, myLeftForearm);  INCR_NEW
		myLeftThigh    = new Limb(&modelLeftThigh,   -2.84f*1.3f,   0.0f,   -0.79f*1.3f, myBody,  nullptr);        INCR_NEW
		myLeftShin     = new Limb(&modelLeftShin,     0,      -1.0f*1.3f,    0,     nullptr, myLeftThigh);    INCR_NEW
		myLeftFoot     = new Limb(&modelLeftFoot,     0,      -1.0f*1.3f,    0,     nullptr, myLeftShin);     INCR_NEW
		myRightHumerus = new Limb(&modelRightHumerus, 0.0f,    0.2f*1.3f,    2.85f*1.3f, myBody,  nullptr);        INCR_NEW
		myRightForearm = new Limb(&modelRightForearm, 0,      -1.0f*1.3f,    0,     nullptr, myRightHumerus); INCR_NEW
		myRightHand    = new Limb(&modelRightHand,    0,      -1.0f*1.3f,    0,     nullptr, myRightForearm); INCR_NEW
		myRightThigh   = new Limb(&modelRightThigh,  -2.84f*1.3f,   0.0f,    0.79f*1.3f, myBody,  nullptr);        INCR_NEW
		myRightShin    = new Limb(&modelRightShin,    0,      -1.0f*1.3f,    0,     nullptr, myRightThigh);   INCR_NEW
		myRightFoot    = new Limb(&modelRightFoot,    0,      -1.0f*1.3f,    0,     nullptr, myRightShin);    INCR_NEW
	}
	else if (PlayerKnuckles::characterID == 8) //Metal Sonic
	{
		displayHeightOffset = 0.1f;
		myBody =         new Body(&modelBody);
		myHead =         new Limb(&modelHead,         1.2f,  -0.3f,   0,     myBody,   nullptr);        INCR_NEW
		myLeftHumerus =  new Limb(&modelLeftHumerus,  0.9f,	  0,     -0.9f,  myBody,   nullptr);        INCR_NEW
		myLeftForearm =  new Limb(&modelLeftForearm,  0,     -1.3f,   0,     nullptr,  myLeftHumerus);  INCR_NEW
		myLeftHand =     new Limb(&modelLeftHand,     0,	 -1.3f,   0,     nullptr,  myLeftForearm);  INCR_NEW
		myLeftThigh =    new Limb(&modelLeftThigh,   -0.9f,   0,     -0.3f,  myBody,   nullptr);        INCR_NEW
		myLeftShin =     new Limb(&modelLeftShin,     0,	 -1.3f,   0,     nullptr,  myLeftThigh);    INCR_NEW
		myLeftFoot =     new Limb(&modelLeftFoot,     0,	 -1.4f,   0,     nullptr,  myLeftShin);     INCR_NEW
		myRightHumerus = new Limb(&modelRightHumerus, 0.9f,   0,      0.9f,  myBody,   nullptr);        INCR_NEW
		myRightForearm = new Limb(&modelRightForearm, 0,	 -1.3f,   0,     nullptr,  myRightHumerus); INCR_NEW
		myRightHand =    new Limb(&modelRightHand,    0,	 -1.3f,   0,     nullptr,  myRightForearm); INCR_NEW
		myRightThigh =   new Limb(&modelRightThigh,  -0.9f,   0,      0.3f,  myBody,   nullptr);        INCR_NEW
		myRightShin =    new Limb(&modelRightShin,    0,	 -1.3f,   0,     nullptr,  myRightThigh);   INCR_NEW
		myRightFoot =    new Limb(&modelRightFoot,    0,	 -1.4f,   0,     nullptr,  myRightShin);    INCR_NEW
	}

	AnimationResources::assignAnimationsHuman(myBody, myHead,
		myLeftHumerus, myLeftForearm, myLeftHand,
		myRightHumerus, myRightForearm, myRightHand,
		myLeftThigh, myLeftShin, myLeftFoot,
		myRightThigh, myRightShin, myRightFoot);

	addLimbsToGame();
}

std::list<TexturedModel*>* PlayerKnuckles::getModels()
{
	return nullptr; //We should never be visible, so this should never be called anyway
}

void PlayerKnuckles::loadStaticModels()
{
	PlayerKnuckles::characterID = 4;

	if (MainMenu::unlockedCharacters.size() > 1)
	{
		if (MainMenu::unlockedCharacters[MainMenu::characterSelectIndex] == "AMY")
		{
			PlayerKnuckles::characterID = 5;
		}
		else if (MainMenu::unlockedCharacters[MainMenu::characterSelectIndex] == "NPC")
		{
			PlayerKnuckles::characterID = 6;
		}
		else if (MainMenu::unlockedCharacters[MainMenu::characterSelectIndex] == "PAC-MAN")
		{
			PlayerKnuckles::characterID = 7;
		}
		else if (MainMenu::unlockedCharacters[MainMenu::characterSelectIndex] == "METAL SONIC")
		{
			PlayerKnuckles::characterID = 8;
		}
	}

	if (PlayerKnuckles::characterID == 4) //Mania Sonic
	{
		ManiaKnucklesModel::loadStaticModels();

		loadObjModel(&PlayerKnuckles::modelBody,         "res/Models/ManiaKnuckles/", "Body.obj");
		loadObjModel(&PlayerKnuckles::modelHead,         "res/Models/ManiaKnuckles/", "Head.obj");
		loadObjModel(&PlayerKnuckles::modelLeftHumerus,  "res/Models/ManiaKnuckles/", "Thigh.obj");
		loadObjModel(&PlayerKnuckles::modelLeftForearm,  "res/Models/ManiaKnuckles/", "Forearm.obj");
		loadObjModel(&PlayerKnuckles::modelLeftHand,     "res/Models/ManiaKnuckles/", "HandLeft.obj");
		loadObjModel(&PlayerKnuckles::modelLeftThigh,    "res/Models/ManiaKnuckles/", "Thigh.obj");
		loadObjModel(&PlayerKnuckles::modelLeftShin,     "res/Models/ManiaKnuckles/", "Shin.obj");
		loadObjModel(&PlayerKnuckles::modelLeftFoot,     "res/Models/ManiaKnuckles/", "FootLeft.obj");
		loadObjModel(&PlayerKnuckles::modelRightHumerus, "res/Models/ManiaKnuckles/", "Thigh.obj");
		loadObjModel(&PlayerKnuckles::modelRightForearm, "res/Models/ManiaKnuckles/", "Forearm.obj");
		loadObjModel(&PlayerKnuckles::modelRightHand,    "res/Models/ManiaKnuckles/", "HandRight.obj");
		loadObjModel(&PlayerKnuckles::modelRightThigh,   "res/Models/ManiaKnuckles/", "Thigh.obj");
		loadObjModel(&PlayerKnuckles::modelRightShin,    "res/Models/ManiaKnuckles/", "Shin.obj");
		loadObjModel(&PlayerKnuckles::modelRightFoot,    "res/Models/ManiaKnuckles/", "FootRight.obj");
	}
	else if (PlayerKnuckles::characterID == 5) //Amy
	{
		loadObjModel(&PlayerKnuckles::modelBody,         "res/Models/AmyModern/", "Body.obj");
		loadObjModel(&PlayerKnuckles::modelHead,         "res/Models/AmyModern/", "Head.obj");
		loadObjModel(&PlayerKnuckles::modelLeftHumerus,  "res/Models/AmyModern/", "Humerus.obj");
		loadObjModel(&PlayerKnuckles::modelLeftForearm,  "res/Models/AmyModern/", "Forearm.obj");
		loadObjModel(&PlayerKnuckles::modelLeftHand,     "res/Models/AmyModern/", "HandLeft.obj");
		loadObjModel(&PlayerKnuckles::modelLeftThigh,    "res/Models/AmyModern/", "Thigh.obj");
		loadObjModel(&PlayerKnuckles::modelLeftShin,     "res/Models/AmyModern/", "Shin.obj");
		loadObjModel(&PlayerKnuckles::modelLeftFoot,     "res/Models/AmyModern/", "ShoeLeft.obj");
		loadObjModel(&PlayerKnuckles::modelRightHumerus, "res/Models/AmyModern/", "Humerus.obj");
		loadObjModel(&PlayerKnuckles::modelRightForearm, "res/Models/AmyModern/", "Forearm.obj");
		loadObjModel(&PlayerKnuckles::modelRightHand,    "res/Models/AmyModern/", "HandRight.obj");
		loadObjModel(&PlayerKnuckles::modelRightThigh,   "res/Models/AmyModern/", "Thigh.obj");
		loadObjModel(&PlayerKnuckles::modelRightShin,    "res/Models/AmyModern/", "Shin.obj");
		loadObjModel(&PlayerKnuckles::modelRightFoot,    "res/Models/AmyModern/", "ShoeRight.obj");
	}
	else if (PlayerKnuckles::characterID == 6) //WanamaDage
	{
		loadObjModel(&PlayerKnuckles::modelBody,         "res/Models/WanamaDageLimbs/", "Body.obj");
		loadObjModel(&PlayerKnuckles::modelHead,         "res/Models/WanamaDageLimbs/", "Head.obj");
		loadObjModel(&PlayerKnuckles::modelLeftHumerus,  "res/Models/WanamaDageLimbs/", "HumerusLeft.obj");
		loadObjModel(&PlayerKnuckles::modelLeftForearm,  "res/Models/WanamaDageLimbs/", "ForearmLeft.obj");
		loadObjModel(&PlayerKnuckles::modelLeftHand,     "res/Models/WanamaDageLimbs/", "HandLeft.obj");
		loadObjModel(&PlayerKnuckles::modelLeftThigh,    "res/Models/WanamaDageLimbs/", "ThighLeft.obj");
		loadObjModel(&PlayerKnuckles::modelLeftShin,     "res/Models/WanamaDageLimbs/", "ShinLeft.obj");
		loadObjModel(&PlayerKnuckles::modelLeftFoot,     "res/Models/WanamaDageLimbs/", "Shoe.obj");
		loadObjModel(&PlayerKnuckles::modelRightHumerus, "res/Models/WanamaDageLimbs/", "HumerusRight.obj");
		loadObjModel(&PlayerKnuckles::modelRightForearm, "res/Models/WanamaDageLimbs/", "ForearmRight.obj");
		loadObjModel(&PlayerKnuckles::modelRightHand,    "res/Models/WanamaDageLimbs/", "HandRight.obj");
		loadObjModel(&PlayerKnuckles::modelRightThigh,   "res/Models/WanamaDageLimbs/", "ThighRight.obj");
		loadObjModel(&PlayerKnuckles::modelRightShin,    "res/Models/WanamaDageLimbs/", "ShinRight.obj");
		loadObjModel(&PlayerKnuckles::modelRightFoot,    "res/Models/WanamaDageLimbs/", "Shoe.obj");
	}
	else if (PlayerKnuckles::characterID == 7) //Pac Man
	{
		loadObjModel(&PlayerKnuckles::modelBody,         "res/Models/PacMan/", "HeadBody.obj");
		loadObjModel(&PlayerKnuckles::modelHead,         "res/Models/PacMan/", "Blank.obj");
		loadObjModel(&PlayerKnuckles::modelLeftHumerus,  "res/Models/PacMan/", "Limb.obj");
		loadObjModel(&PlayerKnuckles::modelLeftForearm,  "res/Models/PacMan/", "Limb.obj");
		loadObjModel(&PlayerKnuckles::modelLeftHand,     "res/Models/PacMan/", "Hand.obj");
		loadObjModel(&PlayerKnuckles::modelLeftThigh,    "res/Models/PacMan/", "Limb.obj");
		loadObjModel(&PlayerKnuckles::modelLeftShin,     "res/Models/PacMan/", "Limb.obj");
		loadObjModel(&PlayerKnuckles::modelLeftFoot,     "res/Models/PacMan/", "Shoe.obj");
		loadObjModel(&PlayerKnuckles::modelRightHumerus, "res/Models/PacMan/", "Limb.obj");
		loadObjModel(&PlayerKnuckles::modelRightForearm, "res/Models/PacMan/", "Limb.obj");
		loadObjModel(&PlayerKnuckles::modelRightHand,    "res/Models/PacMan/", "Hand.obj");
		loadObjModel(&PlayerKnuckles::modelRightThigh,   "res/Models/PacMan/", "Limb.obj");
		loadObjModel(&PlayerKnuckles::modelRightShin,    "res/Models/PacMan/", "Limb.obj");
		loadObjModel(&PlayerKnuckles::modelRightFoot,    "res/Models/PacMan/", "Shoe.obj");
	}
	else if (PlayerKnuckles::characterID == 8) //Metal Sonic
	{
		loadObjModel(&PlayerKnuckles::modelBody,         "res/Models/MetalSonic/", "Body.obj");
		loadObjModel(&PlayerKnuckles::modelHead,         "res/Models/MetalSonic/", "Head.obj");
		loadObjModel(&PlayerKnuckles::modelLeftHumerus,  "res/Models/MetalSonic/", "Humerus.obj");
		loadObjModel(&PlayerKnuckles::modelLeftForearm,  "res/Models/MetalSonic/", "Forearm.obj");
		loadObjModel(&PlayerKnuckles::modelLeftHand,     "res/Models/MetalSonic/", "HandLeft.obj");
		loadObjModel(&PlayerKnuckles::modelLeftThigh,    "res/Models/MetalSonic/", "Humerus.obj");
		loadObjModel(&PlayerKnuckles::modelLeftShin,     "res/Models/MetalSonic/", "Forearm.obj");
		loadObjModel(&PlayerKnuckles::modelLeftFoot,     "res/Models/MetalSonic/", "Shoe.obj");
		loadObjModel(&PlayerKnuckles::modelRightHumerus, "res/Models/MetalSonic/", "Humerus.obj");
		loadObjModel(&PlayerKnuckles::modelRightForearm, "res/Models/MetalSonic/", "Forearm.obj");
		loadObjModel(&PlayerKnuckles::modelRightHand,    "res/Models/MetalSonic/", "HandRight.obj");
		loadObjModel(&PlayerKnuckles::modelRightThigh,   "res/Models/MetalSonic/", "Humerus.obj");
		loadObjModel(&PlayerKnuckles::modelRightShin,    "res/Models/MetalSonic/", "Forearm.obj");
		loadObjModel(&PlayerKnuckles::modelRightFoot,    "res/Models/MetalSonic/", "Shoe.obj");
	}
}

void PlayerKnuckles::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting player knuckles models...\n");
	#endif

	Entity::deleteModels(&PlayerKnuckles::modelBody);
	Entity::deleteModels(&PlayerKnuckles::modelHead);
	Entity::deleteModels(&PlayerKnuckles::modelLeftHumerus);
	Entity::deleteModels(&PlayerKnuckles::modelLeftForearm);
	Entity::deleteModels(&PlayerKnuckles::modelLeftHand);
	Entity::deleteModels(&PlayerKnuckles::modelLeftThigh);
	Entity::deleteModels(&PlayerKnuckles::modelLeftShin);
	Entity::deleteModels(&PlayerKnuckles::modelLeftFoot);
	Entity::deleteModels(&PlayerKnuckles::modelRightHumerus);
	Entity::deleteModels(&PlayerKnuckles::modelRightForearm);
	Entity::deleteModels(&PlayerKnuckles::modelRightHand);
	Entity::deleteModels(&PlayerKnuckles::modelRightThigh);
	Entity::deleteModels(&PlayerKnuckles::modelRightShin);
	Entity::deleteModels(&PlayerKnuckles::modelRightFoot);
}

void PlayerKnuckles::moveMeGround()
{
	Camera* cam = Global::gameCamera;

	if (isBall == false)
	{
		xVelGround += moveSpeedCurrent*cosf(toRadians(cam->getYaw() + movementAngle));
		zVelGround += moveSpeedCurrent*sinf(toRadians(cam->getYaw() + movementAngle));
	}
	else
	{
		xVelGround += moveSpeedCurrent*cosf(toRadians(cam->getYaw() + movementAngle))*0.8f;
		zVelGround += moveSpeedCurrent*sinf(toRadians(cam->getYaw() + movementAngle))*0.8f;
	}

	float currSpeed = sqrtf((xVelGround*xVelGround) + (zVelGround*zVelGround));
	float currDir = toDegrees(atan2f(zVelGround, xVelGround));

	if (moveSpeedCurrent > 0.01f && currSpeed > 0.5f)
	{
		float worldSpaceMovementAngle = cam->getYaw() + movementAngle;
		float diff = compareTwoAngles(worldSpaceMovementAngle, currDir);

		float newDiff = diff / 8;

		float newAngle = currDir + newDiff;

		if (currNorm.y <= wallThreshold && (
			(fabsf(diff) > 45.0f && currSpeed < 5.0f) ||
			(fabsf(diff) > 75.0f && currSpeed < 12.0f)))
		{
			if (!isClimbing && !isPunching)
			{
				popOffWall();
			}
		}

		if (fabsf(diff) > 120.0f)
		{
			xVelGround *= 0.97f;
			zVelGround *= 0.97f;
		}
		else
		{
			xVelGround = currSpeed*cosf(toRadians(newAngle));
			zVelGround = currSpeed*sinf(toRadians(newAngle));
		}

		float factor = 1 - (abs(diff) / turnPenaltyRun);
		zVelGround *= factor;
		zVelGround *= factor;
	}
}

void PlayerKnuckles::setMovementInputs()
{
	jumpInput     = Inputs.INPUT_JUMP;
	actionInput   = Inputs.INPUT_ACTION;
	action2Input  = Inputs.INPUT_ACTION2;
	shoulderInput = Inputs.INPUT_SHOULDER;
	selectInput   = Inputs.INPUT_SELECT;
	specialInput  = Inputs.INPUT_SPECIAL;

	previousJumpInput     = Inputs.INPUT_PREVIOUS_JUMP;
	previousActionInput   = Inputs.INPUT_PREVIOUS_ACTION;
	previousAction2Input  = Inputs.INPUT_PREVIOUS_ACTION2;
	previousShoulderInput = Inputs.INPUT_PREVIOUS_SHOULDER;
	previousSelectInput   = Inputs.INPUT_PREVIOUS_SELECT;
	previousSpecialInput  = Inputs.INPUT_PREVIOUS_SPECIAL;

	movementInputX = Inputs.INPUT_X;
	movementInputY = Inputs.INPUT_Y;
	cameraInputX   = Inputs.INPUT_X2;
	cameraInputY   = Inputs.INPUT_Y2;

	zoomInput = Inputs.INPUT_ZOOM;

	float inputMag = sqrtf(movementInputX*movementInputX + movementInputY*movementInputY);
	moveSpeedCurrent = moveAcceleration*inputMag;
	if (isGliding)
	{
		moveSpeedAirCurrent = glideAcceleration*inputMag;
	}
	else if (inWater)
	{
		moveSpeedAirCurrent = moveAccelerationWater*inputMag;
	}
	else
	{
		moveSpeedAirCurrent = moveAccelerationAir*inputMag;
	}
	movementAngle = toDegrees(atan2f(movementInputY, movementInputX));

	if (canMoveTimer != 0 || hitTimer > 0 || deadTimer >= 0 || Global::finishStageTimer >= 0)
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
		inputMag = 0;
	}

	if (Global::isAutoCam && (!onPlane || (onPlane && triCol->normal.y > 0.1f)))
	{
		if (inputMag > 0.2f)
		{
			float diff = compareTwoAngles(movementAngle + Global::gameCamera->getYaw() + 90, Global::gameCamera->getYaw());

			if (!onPlane)
			{
				if (fabsf(diff) < 110.0f)
				{
					if (diff > 75.0f)
					{
						diff = 75.0f;
					}
					else if (diff < -75.0f)
					{
						diff = -75.0f;
					}

					diff = diff*0.03f;
					cameraInputX += diff;
				}
			}
			else 
			{
				if (fabsf(diff) < 150.0f)
				{
					diff = diff*0.03f;
					cameraInputX += diff;
				}
			}
		}
	}
}

void PlayerKnuckles::setCanMoveTimer(int newMoveTimer)
{
	canMoveTimer = newMoveTimer;
}

void PlayerKnuckles::checkSkid()
{
	bool prevSkid = isSkidding;
	isSkidding = false;
	if (currNorm.y > 0.8f)
	{
		float degAngle = movementAngle;

		degAngle = fmodf(-degAngle - cameraYawTarget, 360);

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
					AudioPlayer::play(13, getPosition());
				}
			}
		}
	}
}

void PlayerKnuckles::applyFrictionAir()
{
	float mag = sqrtf((xVelGround*xVelGround) + (zVelGround*zVelGround));
	float fricToApply = frictionAir;
	if (isGliding)
	{
		fricToApply = glideFriction;
	}
	if (inWater)
	{
		fricToApply = frictionWater;
	}

	if (mag != 0)
	{
		int before = sign(zVelGround);
		zVelGround -= (((fricToApply)*(zVelGround)) / (mag));
		int after = sign(zVelGround);
		if (before != after)
		{
			zVelGround = 0;
		}
		before = sign(xVelGround);
		xVelGround -= (((fricToApply)*(xVelGround)) / (mag));
		after = sign(xVelGround);
		if (before != after)
		{
			xVelGround = 0;
		}
	}

	mag = sqrtf((xVelAir*xVelAir) + (zVelAir*zVelAir));
	if (mag != 0)
	{
		int before = sign(zVelAir);
		zVelAir -= (((fricToApply)*(zVelAir)) / (mag));
		int after = sign(zVelAir);
		if (before != after)
		{
			zVelAir = 0;
		}
		before = sign(xVelAir);
		xVelAir -= (((fricToApply)*(xVelAir)) / (mag));
		after = sign(xVelAir);
		if (before != after)
		{
			xVelAir = 0;
		}
	}
}

void PlayerKnuckles::moveMeAir()
{
	Camera* cam = Global::gameCamera;
	xVelAir += (moveSpeedAirCurrent*cosf(toRadians(cam->getYaw() + movementAngle)));
	zVelAir += (moveSpeedAirCurrent*sinf(toRadians(cam->getYaw() + movementAngle)));

	float currSpeed = sqrtf((xVelAir*xVelAir) + (zVelAir*zVelAir));
	float currDir = toDegrees(atan2f(zVelAir, xVelAir));

	if (moveSpeedAirCurrent > 0.01f && currSpeed > 0.5f)
	{
		float worldSpaceMovementAngle = cam->getYaw() + movementAngle;
		float diff = compareTwoAngles(worldSpaceMovementAngle, currDir);

		float newDiff = diff / 8;

		float newAngle = currDir + newDiff;

		xVelAir = (currSpeed*cosf(toRadians(newAngle)));
		zVelAir = (currSpeed*sinf(toRadians(newAngle)));

		float factor = 1 - (abs(diff) / 900);
		xVelAir *= factor;
		zVelAir *= factor;
	}
}

void PlayerKnuckles::limitMovementSpeedAir()
{
	float myspeed = sqrtf(xVelAir*xVelAir + zVelAir*zVelAir);
	if (inWater)
	{
		if (myspeed > waterSpeedLimit)
		{
			xVelAir = (xVelAir*((myspeed - slowDownWaterRate) / (myspeed)));
			zVelAir = (zVelAir*((myspeed - slowDownWaterRate) / (myspeed)));
		}
	}
	else
	{
		if (isGliding)
		{
			if (myspeed > glideSpeedLimit)
			{
				xVelAir = (xVelAir*((myspeed - glideSlowDownRate) / (myspeed)));
				zVelAir = (zVelAir*((myspeed - glideSlowDownRate) / (myspeed)));
			}
		}
		else
		{
			if (myspeed > airSpeedLimit)
			{
				xVelAir = (xVelAir*((myspeed - slowDownAirRate) / (myspeed)));
				zVelAir = (zVelAir*((myspeed - slowDownAirRate) / (myspeed)));
			}
		}
	}
}

void PlayerKnuckles::limitMovementSpeed(float limit)
{
	if (isBall)
	{
		limit = limit*0.1f;
	}

	float myspeed = sqrtf(xVelGround*xVelGround + zVelGround*zVelGround);
	if (myspeed > limit)
	{
		xVelGround = xVelGround*((myspeed - slowDownRate) / (myspeed));
		zVelGround = zVelGround*((myspeed - slowDownRate) / (myspeed));
	}
}

void PlayerKnuckles::applyFriction(float frictionToApply)
{
	if (isBall)
	{
		frictionToApply *= 0.11f;
	}

	float mag = sqrtf((xVelGround*xVelGround) + (zVelGround*zVelGround));
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

void PlayerKnuckles::calcSpindashAngle()
{
	Camera* cam = Global::gameCamera;
	float inputMag = sqrtf(movementInputX*movementInputX + movementInputY*movementInputY);
	if (inputMag >= 0.3)
	{
		spindashAngle = ((toRadians(-cam->getYaw() - movementAngle)));
	}
	else
	{
		spindashAngle = ((toRadians(getRotY())));
	}
}

void PlayerKnuckles::dropDash(float charge)
{
	float dx =  cosf(toRadians(getRotY()));
	float dz = -sinf(toRadians(getRotY()));

	charge = fminf(charge, dropDashChargeMax);
	charge = fmaxf(charge, dropDashChargeMin);

	float totalSpd = sqrtf(xVelGround*xVelGround + zVelGround*zVelGround);

	float factor = std::fminf(1, 5.0f / totalSpd);

	factor = std::fmaxf(0.35f, factor);

	charge = charge*factor;

	xVelGround += dx*charge;
	zVelGround += dz*charge;

	isBall = true;
	isDropDashing = false;
	AudioPlayer::play(15, getPosition());
}

void PlayerKnuckles::spindash(int /*timer*/)
{
	/*
	float dx = cosf(spindashAngle);
	float dz = -sinf(spindashAngle);

	float totalSpd = sqrtf(xVelGround*xVelGround + zVelGround*zVelGround);

	float factor = calculateSpindashSpeed(timer);

	xVelGround += dx*factor;
	zVelGround += dz*factor;

	float newSpeed = sqrtf(xVelGround*xVelGround + zVelGround*zVelGround);

	if (totalSpd > 1 && newSpeed < storedSpindashSpeed)
	{
		xVelGround = cosf(spindashAngle)*storedSpindashSpeed;
		zVelGround = -sinf(spindashAngle)*storedSpindashSpeed;
	}

	isBall = true;
	AudioPlayer::play(15, getPosition());
	storedSpindashSpeed = 0;
	*/
}

float PlayerKnuckles::getSpindashSpeed()
{
	return storedSpindashSpeed;
}

void PlayerKnuckles::homingAttack()
{
	Camera* cam = Global::gameCamera;

	float homingPower = 5.5f;

	float currSpeed = sqrt(xVelAir*xVelAir + zVelAir*zVelAir);

	homingPower = std::max(currSpeed, homingPower);

	float angle = -cam->getYaw() - movementAngle;
	if (moveSpeedCurrent < 0.05f)
	{
		angle = getRotY();
	}

	//if (characterID == 2)
	{
		bool targetNearest = false;
		float closestMatchingAngle = 360;
		float stickAngle = -cam->getYaw() - movementAngle;

		if (moveSpeedCurrent < 0.05f)
		{
			angle = getRotY();
			targetNearest = true;
		}

		Entity* closest = nullptr;
		float dist = 16000; //Homing attack range. Distance squared
		float myX = position.x;
		float myZ = position.z;
		float myY = position.y;

		extern std::unordered_map<Entity*, Entity*> gameEntities;

		for (auto e : gameEntities)
		{
			if (e.first->canHomingAttackOn())
			{
				float xDiff = e.first->getX() - myX;
				float zDiff = e.first->getZ() - myZ;
				float yDiff = myY - e.first->getY();
				float thisDist = xDiff*xDiff + zDiff*zDiff + yDiff*yDiff;

				if (targetNearest)
				{
					if (yDiff > -6 && thisDist < dist)
					{
						dist = thisDist;
						closest = e.first;
					}
				}
				else
				{
					if (thisDist < dist)
					{
						//calculate angle to this target
						float toTargetAngle = toDegrees(atan2f(zDiff, -xDiff)) + 180;
						//calculate difference in angles
						float angleDiff = abs(compareTwoAngles(stickAngle, toTargetAngle));

						if (angleDiff < 60)
						{
							if (yDiff > -6 && angleDiff < closestMatchingAngle)
							{
								closestMatchingAngle = angleDiff;
								closest = e.first;
							}
						}
					}
				}
			}
		}

		if (closest != nullptr)
		{
			
			float xDiff = -(myX - closest->getX());
			float zDiff = -(myZ - closest->getZ());
			float yDiff = -(myY - closest->getY());

			Vector3f unitDir(xDiff, yDiff + 3.5f, zDiff);
			unitDir.normalize();
			homingPower = 6.7f;

			unitDir.x *= homingPower;
			unitDir.y *= homingPower;
			unitDir.z *= homingPower;

			xVelAir = unitDir.x;
			yVel    = unitDir.y;
			zVelAir = unitDir.z;
			
		}
		else
		{
			xVelAir =  cosf(toRadians(angle))*homingPower;
			zVelAir = -sinf(toRadians(angle))*homingPower;
		}
	}
	//else
	{
		//xVelAir = (float)cos(toRadians(angle))*homingPower;
		//zVelAir = -(float)sin(toRadians(angle))*homingPower;
	}

	homingAttackTimer = homingAttackTimerMax;
	isBall = false;
	isJumping = true;
	isBouncing = false;
	isStomping = false;
	justBounced = false;
	AudioPlayer::play(11, getPosition());
}

void PlayerKnuckles::initiateBounce()
{
	/*
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
	justBounced = true;
	*/
}

void PlayerKnuckles::initiateStomp()
{
	/*
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

	stompSource = AudioPlayer::play(16, getPosition());
	*/
}

void PlayerKnuckles::bounceOffGround(Vector3f* surfaceNormal, float b, int s)
{
	Vector3f V = Vector3f(xVelAir, yVel, zVelAir);
	Vector3f N = Vector3f(surfaceNormal);

	Vector3f Vnew = bounceVector(&V, &N, b);

	xVelAir = Vnew.x;
	yVel = Vnew.y;
	zVelAir = Vnew.z;

	xVel = 0;
	zVel = 0;

	//isBall = true;
	//isBouncing = false;
	//isStomping = false;
	//homingAttackTimer = -1;
	//hoverCount = 0;
	AudioPlayer::play(s, getPosition());
}

//attempt to continue a lightdash
//if lightdash cant continue, sets isLightdashing
//to false
void PlayerKnuckles::attemptLightdash()
{
	if (Global::gameClock % 2 != 0)
	{
		return;
	}
	//find nearest ring
	Entity* closest = nullptr;
	float dist = 2000; //distance squared
	float myX = getX();
	float myZ = getZ();
	float myY = getY();

	extern std::unordered_map<Entity*, Entity*> gameEntities;

	for (auto e : gameEntities)
	{
		if (e.first->canLightdashOn())
		{
			float xDiff = e.first->getX() - myX;
			float zDiff = e.first->getZ() - myZ;
			float yDiff = e.first->getY() - myY;
			float newDist = xDiff*xDiff + zDiff*zDiff + yDiff*yDiff;
			if (newDist < dist)
			{
				dist = newDist;
				closest = e.first;
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
		xVelGround = 0;
		zVelGround = 0;

		//set xVelAir and zVelAir to the direction to the ring
		Vector3f diff(closest->getX() - myX, closest->getY() - myY, closest->getZ() - myZ);
		diff.normalize();

		xVelAir = diff.x * 5;
		zVelAir = diff.z * 5;
		yVel = diff.y * 5;


		Vector3f diffNew;
		diffNew.x = closest->getX() - previousLightdashPosition.x;
		diffNew.y = closest->getY() - previousLightdashPosition.y;
		diffNew.z = closest->getZ() - previousLightdashPosition.z;

		Vector3f vel(0, 0.0f, 0);

		int count = 0;
		while (count < 20)
		{
			Vector3f pos;
			pos.x = previousLightdashPosition.x + ((diffNew.x*count) / 20.0f);
			pos.y = previousLightdashPosition.y + ((diffNew.y*count) / 20.0f);
			pos.z = previousLightdashPosition.z + ((diffNew.z*count) / 20.0f);

			new Particle(ParticleResources::textureOrangeTrail, &pos, &vel,
				0, 70, 0, 12, -(12.0f / 70.0f), false);
			count++;
		}



		//move to ring location
		setX(closest->getX());
		setY(closest->getY());
		setZ(closest->getZ());

		previousLightdashPosition.set(closest->getPosition());
	}
	else
	{
		//doesnt pass threshold?
		isLightdashing = false;
	}
}

void PlayerKnuckles::adjustCamera()
{
	if (deadTimer == -1)
	{
		cameraRadius += (cameraRadiusTarget - cameraRadius) / 20;

		cameraRadiusTarget += zoomInput;
		cameraRadiusTarget = fmax(cameraRadiusZoom, cameraRadiusTarget);
		cameraRadiusTarget = fmin(cameraRadiusZoomOut, cameraRadiusTarget);

		Camera* cam = Global::gameCamera;
		//Vector3f* camPos = cam->getPosition();

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
		cameraYawTarget += cameraInputX;


		cam->setYaw(cam->getYaw() + (cameraYawTarget - cam->getYaw()) / cameraLaziness);
		cam->setPitch(cam->getPitch() + (cameraPitchTarget - cam->getPitch()) / cameraLaziness);



		Vector3f headPos(
			position.x + currNorm.x*headHeight,
			position.y + currNorm.y*headHeight,
			position.z + currNorm.z*headHeight);

		Vector3f camPos(
			headPos.x + (float)(cos(toRadians(cam->getYaw() + 90))*(cameraRadius*(cos(toRadians(cam->getPitch()))))),
			headPos.y - (float)(sin(toRadians(cam->getPitch() + 180))*cameraRadius),
			headPos.z + (float)(sin(toRadians(cam->getYaw() + 90))*(cameraRadius*(cos(toRadians(cam->getPitch()))))));


		if (CollisionChecker::checkCollision(position.x, position.y, position.z, headPos.x, headPos.y, headPos.z) == true)
		{
			Vector3f* posCol = CollisionChecker::getCollidePosition();

			Vector3f diff;

			diff.x = posCol->x - getX();
			diff.y = posCol->y - getY();
			diff.z = posCol->z - getZ();

			//float newHeadHeight = diff.length() - 1;

			//camPos.set(getX() + currNorm.x*newHeadHeight,
			//	getY() + currNorm.y*newHeadHeight,
			//	getZ() + currNorm.z*newHeadHeight);
		}
		else if (CollisionChecker::checkCollision(headPos.x, headPos.y, headPos.z, camPos.x, camPos.y, camPos.z) == true)
		{
			Vector3f* posCol = CollisionChecker::getCollidePosition();

			Vector3f diff;

			diff.x = posCol->x - headPos.x;
			diff.y = posCol->y - headPos.y;
			diff.z = posCol->z - headPos.z;

			float newRadius = diff.length() - 4;

			diff.normalize();
			diff.scale(newRadius);

			camPos.set(
				headPos.x + diff.x,
				headPos.y + diff.y,
				headPos.z + diff.z);

		}


		cam->setPosition(&camPos);

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
		/*
		Vector3f normOpp(currNorm);
		normOpp.neg();

		Vector3f newCamPos = mapCamera(toRadians(cameraYawTarget+90), 0, cameraRadius, &normOpp);

		float newYaw = atan2f(newCamPos.z, newCamPos.x);
		float newPitch = atan2f(newCamPos.y, sqrtf(newCamPos.x*newCamPos.x + newCamPos.z*newCamPos.z));

		newCamPos.set(
			headPos.x + newCamPos.x,
			headPos.y + newCamPos.y,
			headPos.z + newCamPos.z);

		cam->setPosition(&newCamPos);

		cam->setYaw(toDegrees(newYaw)-90);
		cam->setPitch(toDegrees(newPitch));
		*/
	}
	else
	{
		Camera* cam = Global::gameCamera;

		float xDiff = (cam->getPosition()->getX() - getX());
		float yDiff = (cam->getPosition()->getY() - getY());
		float zDiff = (cam->getPosition()->getZ() - getZ());


		float newYaw = atan2f(zDiff, xDiff);
		float newPitch = atan2f(yDiff, sqrtf(xDiff*xDiff + zDiff*zDiff));

		cam->setYaw(toDegrees(newYaw)-90);
		cam->setPitch(toDegrees(newPitch));
	}
}

void PlayerKnuckles::setCameraAngles(float newYaw, float newPitch)
{
	cameraYawTarget = newYaw;
	cameraPitchTarget = newPitch;
	Camera* cam = Global::gameCamera;
	cam->setYaw(newYaw);
	cam->setPitch(newPitch);
}

void PlayerKnuckles::setCameraTargetYaw(float yaw)
{
	cameraYawTarget = yaw;

	Camera* cam = Global::gameCamera;

	float diff = compareTwoAngles(yaw, cam->getYaw());

	cam->setYaw(yaw - diff);
}

void PlayerKnuckles::setCameraTargetPitch(float pitch)
{
	cameraPitchTarget = pitch;

	Camera* cam = Global::gameCamera;

	float diff = compareTwoAngles(pitch, cam->getPitch());

	cam->setPitch(pitch - diff);
}

void PlayerKnuckles::animate()
{
	float xrel = xVelGround + xVelAir;
	float zrel = zVelGround + zVelAir;
	float ang = atan2f(zrel, xrel);
	Vector3f normOpp(currNorm);
	normOpp.neg();
	Vector3f ans = mapInputs3(ang, 10, &normOpp);
	float yrot = toDegrees(atan2f(-ans.z, ans.x));
	float dist = sqrtf(ans.x*ans.x + ans.z*ans.z);
	float zrot = toDegrees(atan2f(ans.y, dist));

	float twistAngle = toDegrees(atan2f(-zVelGround - zVelAir, xVelGround + xVelAir));
	float nX = currNorm.x;
	float nY = currNorm.y;
	float nZ = currNorm.z;
	float normHLength = sqrtf(nX*nX + nZ*nZ);
	float pitchAngle = toDegrees(atan2f(nY, normHLength));
	float yawAngle = toDegrees(atan2f(-nZ, nX));
	float diff = compareTwoAngles(twistAngle, yawAngle);

	Vector3f displayPos(
		getX() + nX*displayHeightOffset,
		getY() + nY*displayHeightOffset,
		getZ() + nZ*displayHeightOffset);

	Vector3f dspOff(0, 0, 0);

	if (onPlane)
	{
		if (isBouncing ||
			isBall ||
			isSpindashing ||
			spindashReleaseTimer > 0 ||
			isDigging)
		{
			if (isDigging)
			{
				float digDist = 0;
				if (diggingTimer > diggingTimerMax/2)
				{
					digDist = -20*((float)(diggingTimerMax - diggingTimer))/diggingTimerMax;
				}
				else
				{
					digDist = -20*((float)diggingTimer)/diggingTimerMax;
				}
				dspOff.set(currNorm.x*digDist, currNorm.y*digDist, currNorm.z*digDist);
				displayPos.set(
					getX() + nX*digDist,
					getY() + nY*digDist,
					getZ() + nZ*digDist);
			}
			else
			{
				dspOff.set(currNorm.x*2.5f, currNorm.y*2.5f, currNorm.z*2.5f);
			}
		}
		else
		{
			dspOff.set(-currNorm.x * 1, -currNorm.y * 1, -currNorm.z * 1);
		}
	}

	float dspX = getX() + dspOff.x;
	float dspY = getY() + dspOff.y;
	float dspZ = getZ() + dspOff.z;

	Vector3f displayPosPrev(previousPos);
	displayPosPrev.x += nX*displayHeightOffset + dspOff.x;
	displayPosPrev.y += nY*displayHeightOffset + dspOff.y;
	displayPosPrev.z += nZ*displayHeightOffset + dspOff.z;

	float mySpeed = sqrtf(xrel*xrel + zrel*zrel);


	setLimbsVisibility(true);
	if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(true); }

	if (firstPerson)
	{
		setLimbsVisibility(false);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
	}
	else
	{
		if (iFrame % 4 == 2 || iFrame % 4 == 3)
		{
			setLimbsVisibility(false);
			if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		}
	}

	if (mySpeed > 0.01f)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, diff, yawAngle, pitchAngle, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr)
		{
			PlayerKnuckles::maniaKnuckles->setOrientation(dspX, dspY, dspZ, diff, yawAngle, pitchAngle, 0);
		}
		setRotY(yrot);
		setRotZ(zrot);
	}
	else
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, getRotY(), 90, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr)
		{
			PlayerKnuckles::maniaKnuckles->setOrientation(dspX, dspY, dspZ, 0, getRotY(), 90, 0);
		}
	}

	float modelIncreaseVal = (mySpeed)*0.3f;
	modelRunIndex += modelIncreaseVal;

	float climbTimeBefore = climbAnimTime;
	climbAnimTime += mySpeed*3.5f;
	climbAnimTime = fmodf(climbAnimTime, 100);

	if (isClimbing && 
		(climbTimeBefore > climbAnimTime || 
		(climbTimeBefore < 50 && climbAnimTime >= 50)))
	{
		AudioPlayer::play(29, getPosition());
	}

	if (modelRunIndex >= 20)
	{
		modelRunIndex = fmodf(modelRunIndex, 20);
	}
	if (mySpeed == 0)
	{
		modelRunIndex = 0;
	}

	if (homingAttackTimer > 0)
	{
		float height = 2;
		if (characterID == 6) height = -5;
		if (characterID == 7) height = -2.65f;
		Vector3f offset(currNorm.x*height, currNorm.y*height, currNorm.z*height);
		Vector3f prevPos(previousDisplayPos);
		prevPos = prevPos + offset;
		Vector3f newPos(displayPos);
		newPos = newPos + offset;
		createSpindashTrails(&prevPos, &newPos, 5, 20);
	}

	//For punching animation
	if (PlayerKnuckles::characterID == 4)
	{
		myRightHand->setScale(0.33f);
	}
	else
	{
		myRightHand->setScale(1.0f);
	}

	if (deadTimer >= 0)
	{
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, getRotY(), 0, 0);
		updateLimbs(19, 0);
	}
	else if (onRocket)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, getRotY(), 75, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		updateLimbs(25, 0);
	}
	else if (isDigging)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, diff+diggingTimer*40, yawAngle, pitchAngle+180, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		updateLimbs(20, 0);
	}
	else if (isGliding)
	{
		float h = sqrtf(xVelAir*xVelAir + zVelAir*zVelAir);
		float zr = toDegrees(atan2f(yVel, h));
		zr = fmaxf(zr, -10);
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, getRotY(), zr, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		updateLimbs(20, 0);
	}
	else if (isDrillDiving)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, animCount*42, -90, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		updateLimbs(20, 0);

		float height = 2;
		Vector3f offset(currNorm.x*height, currNorm.y*height, currNorm.z*height);
		Vector3f prevPos(previousDisplayPos);
		prevPos = prevPos + offset;
		Vector3f newPos(displayPos);
		newPos = newPos + offset;
		createSpindashTrails(&prevPos, &newPos, 5, 20);
	}
	else if (isLightdashing)
	{
		float h = sqrtf(xVelAir*xVelAir + zVelAir*zVelAir);
		float zr = toDegrees(atan2f(yVel, h));
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, getRotY(), zr, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		updateLimbs(18, 0);
	}
	else if (isStomping)
	{
		float h = sqrtf(xVelAir*xVelAir + zVelAir*zVelAir);
		float zr = (toDegrees(atan2f(yVel, h)));
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, twistAngle, pitchAngle, zr + 90);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }

		float height = 2;
		if (characterID == 6) height = -5;
		if (characterID == 7) height = -2.65f;
		Vector3f offset(currNorm.x*height, currNorm.y*height, currNorm.z*height);
		Vector3f prevPos(previousDisplayPos);
		prevPos = prevPos + offset;
		Vector3f newPos(displayPos);
		newPos = newPos + offset;
		createSpindashTrails(&prevPos, &newPos, 5, 20);
		updateLimbs(3, 100);
	}
	else if (isBouncing)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, twistAngle, pitchAngle, airSpinRotation);
		if (PlayerKnuckles::maniaKnuckles != nullptr)
		{
			PlayerKnuckles::maniaKnuckles->setOrientation(dspX, dspY, dspZ, 0, twistAngle, pitchAngle, airSpinRotation);
			PlayerKnuckles::maniaKnuckles->animate(12, 0);
			setLimbsVisibility(false);
		}
		float height = 2;
		if (characterID == 6) height = -5;
		if (characterID == 7) height = -2.65f;
		Vector3f offset(currNorm.x*height, currNorm.y*height, currNorm.z*height);
		Vector3f prevPos(previousDisplayPos);
		prevPos = prevPos + offset;
		Vector3f newPos(displayPos);
		newPos = newPos + offset;
		createSpindashTrails(&prevPos, &newPos, 5, 20);
		updateLimbs(12, 0);
		airSpinRotation += -60;
	}
	else if (isDropDashing)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, twistAngle, pitchAngle, airSpinRotation);
		if (PlayerKnuckles::maniaKnuckles != nullptr)
		{
			PlayerKnuckles::maniaKnuckles->setOrientation(dspX, dspY, dspZ, 0, twistAngle, pitchAngle, airSpinRotation);
			PlayerKnuckles::maniaKnuckles->animate(12, 0);
			setLimbsVisibility(false);
		}
		updateLimbs(12, 0);
		airSpinRotation += -(1 + sqrt(dropDashCharge)*18);
	}
	else if (inWater)
	{
		float h = sqrtf(xVelAir*xVelAir + zVelAir*zVelAir);
		float zr = (toDegrees(atan2f(yVel, h)));
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, twistAngle, pitchAngle, zr);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }

		swimAnim += 1.5f*sqrtf(h*h + yVel*yVel);
		swimAnim = fmodf(swimAnim, 100);

		if (swimStrokeTimer <= 0)
		{
			updateLimbs(15, swimAnim);
		}
		else
		{
			updateLimbs(16, 100-swimStrokeTimer);
		}
	}
	else if (isJumping)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, twistAngle, pitchAngle, airSpinRotation);
		if (PlayerKnuckles::maniaKnuckles != nullptr)
		{
			PlayerKnuckles::maniaKnuckles->setOrientation(dspX, dspY, dspZ, 0, twistAngle, pitchAngle, airSpinRotation);
			PlayerKnuckles::maniaKnuckles->animate(12, 0);
			setLimbsVisibility(false);
		}
		updateLimbs(12, 0);
		airSpinRotation += -35;
	}
	else if (isPunching)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, diff, yawAngle, pitchAngle, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		float time = 100*(punchingTimerMax-punchingTimer)/(punchingTimerMax+0.01f);
		updateLimbs(22, time*2);

		float height = 5;
		Vector3f offset(currNorm.x*height, currNorm.y*height, currNorm.z*height);
		Vector3f prevPos(previousDisplayPos);
		prevPos = prevPos + offset;
		Vector3f newPos(displayPos);
		newPos = newPos + offset;
		createSpindashTrails(&prevPos, &newPos, 3, 20);
	}
	else if (isClimbing)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, yawAngle+180, -pitchAngle+100, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		updateLimbs(23, climbAnimTime);
	}
	else if (isBall)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(dspX, dspY, dspZ, diff, yawAngle, pitchAngle, airSpinRotation);
		if (PlayerKnuckles::maniaKnuckles != nullptr)
		{
			PlayerKnuckles::maniaKnuckles->setOrientation(dspX, dspY, dspZ, diff, yawAngle, pitchAngle, airSpinRotation);
			PlayerKnuckles::maniaKnuckles->animate(12, 0);
			setLimbsVisibility(false);
		}
		float height = 2;
		if (characterID == 6) height = -5;
		if (characterID == 7) height = -2.65f;
		Vector3f offset(currNorm.x*height, currNorm.y*height, currNorm.z*height);
		Vector3f prevPos(previousDisplayPos);
		prevPos = prevPos + offset;
		Vector3f newPos(displayPos);
		newPos = newPos + offset;
		createSpindashTrails(&prevPos, &newPos, 5, 20);
		updateLimbs(12, 0);
		airSpinRotation += -70;
	}
	else if (isSpindashing)
	{
		float twistAngleNew = toDegrees(spindashAngle);
		float diffNew = compareTwoAngles(twistAngleNew, yawAngle);

		setRotY(toDegrees(spindashAngle));
		float zrotoff = -(spindashTimer*spindashTimer*0.8f);
		if (spindashTimer >= spindashTimerMax)
		{
			zrotoff = -(animCount * 50);
		}
		if (myBody != nullptr) myBody->setBaseOrientation(dspX, dspY, dspZ, diffNew, yawAngle, pitchAngle, zrotoff);
		updateLimbs(12, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr)
		{
			PlayerKnuckles::maniaKnuckles->setOrientation(dspX, dspY, dspZ, diffNew, yawAngle, pitchAngle, zrotoff);
			setLimbsVisibility(false);
			PlayerKnuckles::maniaKnuckles->animate(12, 0);
		}
	}
	else if (spindashReleaseTimer > 0)
	{
		float zrotoff = (spindashReleaseTimer*spindashReleaseTimer*0.8f);
																		  //zrotoff = -count*40; //different look, might look better?
		if (myBody != nullptr) myBody->setBaseOrientation(dspX, dspY, dspZ, diff, yawAngle, pitchAngle, zrotoff);
		updateLimbs(12, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr)
		{
			PlayerKnuckles::maniaKnuckles->setOrientation(dspX, dspY, dspZ, diff, yawAngle, pitchAngle, zrotoff);
			setLimbsVisibility(false);
			PlayerKnuckles::maniaKnuckles->animate(12, 0);
		}
	}
	else if (onPlane && mySpeed < 0.01f)
	{
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		float time = fmodf((animCount * 1.0f), 100);
		updateLimbs(0, time);
	}
	else if (isSkidding)
	{
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, diff, yawAngle, pitchAngle, 0);
		updateLimbs(8, 0);
	}
	else if (hitTimer > 0)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, diff, yawAngle, pitchAngle, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		updateLimbs(11, 0);
	}
	else if (onPlane == false)
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, 0, getRotY(), 75, 0);
		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		updateLimbs(21, 0);
	}
	else
	{
		if (myBody != nullptr) myBody->setBaseOrientation(&displayPos, diff, yawAngle, pitchAngle, 0);
		float time = 10 * modelRunIndex * 0.5f;
		updateLimbs(1, time);
		if (PlayerKnuckles::maniaKnuckles != nullptr)
		{
			PlayerKnuckles::maniaKnuckles->setOrientation(dspX, dspY, dspZ, diff, yawAngle, pitchAngle, 0);
			setLimbsVisibility(false);

			if (mySpeed < 3.9f)
			{
				PlayerKnuckles::maniaKnuckles->animate(15, time);
			}
			else
			{
				PlayerKnuckles::maniaKnuckles->animate(1, time);
			}
		}
		airSpinRotation = 0;
	}
	
	float snowRadius = 110;
	int snowDensity = 15;

	switch (Global::levelID)
	{
		case LVL_SNOWHEAD:
		{
			float radius2 = snowRadius * 2;
			float radius = snowRadius;
			float basex = getX() - radius;
			float basey = getY();
			float basez = getZ() - radius;
			int density = snowDensity;
			for (int i = 0; i < density; i++)
			{
				Vector3f pos(basex + radius2*Maths::random(),
							 basey + radius*Maths::random(),
							 basez + radius2*Maths::random());

				Vector3f vel(0.25f*7.5f, -0.4f*7.5f, 0.15f*7.5f);

				new Particle(ParticleResources::textureSnowball, &pos, &vel, 
					0, 80, 0, Maths::random() + 0.75f, -0.02f, false);
			}
			break;
		}

		default:
		{
			break;
		}
	}

	//Stage finished stuff
	//if (Global::finishStageTimer == 1)
	//{
	//	Vector3f partVel(0, 0, 0);
	//	new Particle(ParticleResources::textureWhiteFadeOutAndIn, Global::gameCamera->getFadePosition1(), &partVel, 0, 120, 0, 400, 0, true);
	//}
	//else if (Global::finishStageTimer == 60)
	//{
	//	AudioPlayer::stopBGM();
	//	AudioPlayer::play(24, getPosition());
	//}
	//else if (Global::finishStageTimer == 490)
	//{
	//	Vector3f partVel(0, 0, 0);
	//	new Particle(ParticleResources::textureBlackFadeOutAndIn, Global::gameCamera->getFadePosition1(), &partVel, 0, 120, 0, 400, 0, true);
	//
	//	AudioPlayer::play(25, getPosition());
	//}
	//
	//if (Global::finishStageTimer >= 1 &&
	//	Global::finishStageTimer < 60)
	//{
	//	AudioPlayer::setBGMVolume((60-Global::finishStageTimer)/60.0f);
	//}

	if (Global::finishStageTimer >= 60)
	{
		position.set(&Global::gameStage->finishPlayerPosition);
		position.y = Global::gameStage->finishPlayerPosition.y + displayHeightOffset;
		setRotY(Global::gameStage->finishPlayerRotY);
		setCameraTargetYaw(-(getRotY()+180)+90);
		setCameraTargetPitch(Global::gameStage->finishCameraPitch);
		cameraRadiusTarget = 40;

		setGroundSpeed(0, 0);
		xVelAir = 0;
		zVelAir = 0;
		yVel = 0;
		xVel = 0;
		zVel = 0;
		isJumping = false;
		isSpindashing = false;
		isSkidding = false;
		isBall = false;
		isBouncing = false;
		isStomping = false;
		isLightdashing = false;
		isDrillDiving = false;

		if (PlayerKnuckles::maniaKnuckles != nullptr) { PlayerKnuckles::maniaKnuckles->setVisible(false); }
		if (myBody != nullptr) myBody->setBaseOrientation(&position, 0, getRotY(), 90, 0);
		setLimbsVisibility(true);

		float finishTimeAnim = fminf((float)(Global::finishStageTimer-100)*2.0f, 99.99f);

		updateLimbs(14, finishTimeAnim);
	}

	previousDisplayPos.set(&displayPos);
	updateLimbsMatrix();
}

void PlayerKnuckles::createSpindashTrails(Vector3f* initPos, Vector3f* endPos, int count, int life)
{
	Vector3f diff(endPos);
	diff.x -= initPos->x;
	diff.y -= initPos->y;
	diff.z -= initPos->z;

	diff.scale(1.0f / (count));

	for (int i = 0; i < count; i++)
	{
		Vector3f offset(&diff);
		offset.scale((float)i);
		offset.x += initPos->x;
		offset.y += initPos->y;
		offset.z += initPos->z;

		newSpindashTrail(&offset, life, characterID);
	}
}

void PlayerKnuckles::newSpindashTrail(Vector3f* trailPos, int life, int colourID)
{
	newSpindashTrail(trailPos, 0, 0, 0, 0, life, 10, colourID);
}

void PlayerKnuckles::newSpindashTrail(Vector3f* trailPos, float trailXVel, float trailYVel, float trailZVel, float trailGravity, int life, float size, int /*colourID*/)
{
	Vector3f spd(trailXVel, trailYVel, trailZVel);
	switch (characterID)
	{
		case 0:
			new Particle(ParticleResources::textureLightBlueTrail,
				trailPos, &spd,
				trailGravity, life, 0, size, -(size / life), false);
			break;

		case 1:
			new Particle(ParticleResources::textureBlueTrail,
				trailPos, &spd,
				trailGravity, life, 0, size, -(size / life), false);
			break;

		case 2:
			new Particle(ParticleResources::textureBlackTrail,
				trailPos, &spd,
				trailGravity, life, 0, size, -(size / life), false);
			break;

		case 3:
			new Particle(ParticleResources::textureGrayTrail,
				trailPos, &spd,
				trailGravity, life, 0, size, -(size / life), false);
			break;

		case 4:
			new Particle(ParticleResources::textureRedTrail,
				trailPos, &spd,
				trailGravity, life, 0, size, -(size / life), false);
			break;

		case 5:
			new Particle(ParticleResources::texturePinkTrail,
				trailPos, &spd,
				trailGravity, life, 0, size, -(size / life), false);
			break;

		case 6:
			new Particle(ParticleResources::textureDarkGreenTrail,
				trailPos, &spd,
				trailGravity, life, 0, size, -(size / life), false);
			break;

		case 7:
			new Particle(ParticleResources::textureOrangeTrail,
				trailPos, &spd,
				trailGravity, life, 0, size, -(size / life), false);
			break;

		default:
			break;
	}
}

void PlayerKnuckles::createStompParticles()
{
	float totXVel = xVel + xVelAir;
	float totZVel = zVel + zVelAir;
	int numBubbles = ((int)abs(yVel * 10)) + 18;
	for (int i = 0; i < numBubbles; i++)
	{
		float xOff = (18 * (Maths::random() - 0.5f));
		float zOff = (18 * (Maths::random() - 0.5f));

		Vector3f pos(getX() + xOff, getY() + 2, getZ() + zOff);

		newSpindashTrail(&pos, 
			(Maths::random() - 0.5f) * 3 + totXVel*0.8f,
			(Maths::random()*1.2f + 0.5f),
			(Maths::random() - 0.5f) * 3 + totZVel*0.8f,
			0.08f, 25, 14, characterID);
	}
}

void PlayerKnuckles::goUp()
{
	yVel += 0.5f;
}

bool PlayerKnuckles::isPlayer()
{
	return true;
}

void PlayerKnuckles::setGroundSpeed(float newXspd, float newZspd)
{
	xVelGround = newXspd;
	zVelGround = newZspd;
}

float PlayerKnuckles::getxVel()
{
	return xVel;
}

void PlayerKnuckles::setxVel(float newXVel)
{
	xVel = newXVel;
}

float PlayerKnuckles::getyVel()
{
	return yVel;
}

void PlayerKnuckles::setyVel(float newYVel)
{
	yVel = newYVel;
}

float PlayerKnuckles::getzVel()
{
	return zVel;
}

void PlayerKnuckles::setzVel(float newZVel)
{
	zVel = newZVel;
}

void PlayerKnuckles::setxVelAir(float newXVelAir)
{
	xVelAir = newXVelAir;
}

float PlayerKnuckles::getXVelAir()
{
	return xVelAir;
}

void PlayerKnuckles::setzVelAir(float newZVelAir)
{
	zVelAir = newZVelAir;
}

float PlayerKnuckles::getZVelAir()
{
	return zVelAir;
}

void PlayerKnuckles::setHoverCount(int newCount)
{
	hoverCount = newCount;
}

int PlayerKnuckles::getHoverCount()
{
	return hoverCount;
}

void PlayerKnuckles::setOnPlane(bool on)
{
	onPlane = on;
}

void PlayerKnuckles::setOnPlanePrevious(bool on)
{
	onPlanePrevious = on;
}

float PlayerKnuckles::getHitboxHorizontal()
{
	return 6;
}

float PlayerKnuckles::getHitboxVertical()
{
	return 12;
}

void PlayerKnuckles::stopMoving()
{
	xVel = 0;
	yVel = 0;
	zVel = 0;
	xVelAir = 0;
	zVelAir = 0;
	xVelGround = 0;
	zVelGround = 0;
	isPunching = false;
}

void PlayerKnuckles::setInWater(float height)
{
	inWater = true;
	waterHeight = height;
}

void PlayerKnuckles::increaseGroundSpeed(float dx, float dz)
{
	xVelGround += dx;
	zVelGround += dz;
}

float PlayerKnuckles::getSpeed()
{
	float xSpd = xVelAir + xVelGround;
	float zSpd = zVelAir + zVelGround;

	return sqrtf(xSpd*xSpd + zSpd*zSpd);
}

void PlayerKnuckles::takeDamage(Vector3f* damageSource)
{
	if (iFrame == 0)
	{
		float xDiff = damageSource->x - getX();
		float zDiff = damageSource->z - getZ();
		float newDirection = atan2f(zDiff, -xDiff);
		xVelAir =  1.5f*cosf(newDirection);
		zVelAir = -1.5f*sinf(newDirection);
		xVel = 0;
		zVel = 0;
		xVelGround = 0;
		zVelGround = 0;
		onPlane = false;
		yVel = 1.5f;
		iFrame = 120;
		hitTimer = 120;
		isJumping = false;
		isSpindashing = false;
		isSkidding = false;
		isBall = false;
		isBouncing = false;
		isStomping = false;
		isLightdashing = false;
		spindashReleaseTimer = 0;
		spindashRestartDelay = 0;

		if (myShieldGreen != nullptr || myShieldMagnet != nullptr)
		{
			if (myShieldMagnet != nullptr)
			{
				Main_deleteTransparentEntity(myShieldMagnet);
				myShieldMagnet = nullptr;
			}
			if (myShieldGreen != nullptr)
			{
				Main_deleteTransparentEntity(myShieldGreen);
				myShieldGreen = nullptr;
			}
		}
		else
		{
			int ringsToScatter = Global::gameRingCount;
			Global::gameRingCount = 0;

			if (ringsToScatter == 0)
			{
				die();
			}
			else
			{
				AudioPlayer::play(10, getPosition());
			}

			ringsToScatter = std::min(ringsToScatter, 80);

			while (ringsToScatter > 0)
			{
				float spoutSpd = 3.5f;
				float anglH = (float)(M_PI * 2 * Maths::random());
				float anglV = (toRadians(Maths::nextGaussian() * 42 + 90));

				float yspd = (spoutSpd*sin(anglV));
				float hpt = (spoutSpd*cos(anglV));

				float xspd = (hpt*cos(anglH));
				float zspd = (hpt*sin(anglH));

				Ring* ring = new Ring(getX(), getY()+5, getZ(), xspd, yspd, zspd);
				INCR_NEW

				Main_addEntity(ring);

				ringsToScatter--;
			}
		}
	}
}

void PlayerKnuckles::rebound(Vector3f* source)
{
	if (onPlane == false)
	{
		yVel = 2.1f;
		xVelAir = 0;
		zVelAir = 0;
		setX(source->x);
		setZ(source->z);
		setY(source->y + 3.5f);
		homingAttackTimer = -1;
		hoverCount = hoverLimit / 2;
	}
}

bool PlayerKnuckles::isVulnerable()
{
	return !(
		homingAttackTimer > 0 ||
		isBouncing ||
		isJumping ||
		isBall ||
		isSpindashing ||
		isStomping ||
		isPunching ||
		isDigging ||
		invincibleTimer != 0);
}

void PlayerKnuckles::die()
{
	if (deadTimer == -1 && Global::finishStageTimer == -1)
	{
		AudioPlayer::play(9, getPosition());
		deadTimer = 180;
	}
}

Vector3f PlayerKnuckles::getOverallVel()
{
	return Vector3f(xVel, yVel, zVel);
}

float PlayerKnuckles::getXVelGround()
{
	return xVelGround;
}

float PlayerKnuckles::getZVelGround()
{
	return zVelGround;
}

void PlayerKnuckles::debugAdjustCamera()
{
	cameraInputX = Inputs.INPUT_X2;
	cameraInputY = Inputs.INPUT_Y2;

	zoomInput = Inputs.INPUT_ZOOM;




	cameraRadius += (cameraRadiusTarget - cameraRadius) / 20;

	cameraRadiusTarget += zoomInput;
	cameraRadiusTarget = fmax(cameraRadiusZoom, cameraRadiusTarget);
	cameraRadiusTarget = fmin(cameraRadiusZoomOut, cameraRadiusTarget);

	Camera* cam = Global::gameCamera;

	cameraPitchTarget += cameraInputY;
	cameraYawTarget += cameraInputX;

	cam->setYaw(cam->getYaw() + (cameraYawTarget - cam->getYaw()) / cameraLaziness);
	cam->setPitch(cam->getPitch() + (cameraPitchTarget - cam->getPitch()) / cameraLaziness);

	Vector3f headPos(
		position.x + currNorm.x*headHeight,
		position.y + currNorm.y*headHeight,
		position.z + currNorm.z*headHeight);

	Vector3f camPos(
		headPos.x + (cosf(toRadians(cam->getYaw() + 90))*(cameraRadius*(cosf(toRadians(cam->getPitch()))))),
		headPos.y - (sinf(toRadians(cam->getPitch() + 180))*cameraRadius),
		headPos.z + (sinf(toRadians(cam->getYaw() + 90))*(cameraRadius*(cosf(toRadians(cam->getPitch()))))));


	if (CollisionChecker::checkCollision(position.x, position.y, position.z, headPos.x, headPos.y, headPos.z) == true)
	{
		Vector3f* posCol = CollisionChecker::getCollidePosition();

		Vector3f diff;

		diff.x = posCol->x - getX();
		diff.y = posCol->y - getY();
		diff.z = posCol->z - getZ();
	}
	else if (CollisionChecker::checkCollision(headPos.x, headPos.y, headPos.z, camPos.x, camPos.y, camPos.z) == true)
	{
		Vector3f* posCol = CollisionChecker::getCollidePosition();

		Vector3f diff;

		diff.x = posCol->x - headPos.x;
		diff.y = posCol->y - headPos.y;
		diff.z = posCol->z - headPos.z;

		float newRadius = diff.length() - 4;

		diff.normalize();
		diff.scale(newRadius);

		camPos.set(
			headPos.x + diff.x,
			headPos.y + diff.y,
			headPos.z + diff.z);
	}

	cam->setPosition(&camPos);
}

//Do a small 'pop off' off the wall
void PlayerKnuckles::popOffWall()
{
	xVelAir = xVel + currNorm.x * 1.5f;
	zVelAir = zVel + currNorm.z * 1.5f;
	yVel = yVel + currNorm.y * 1.5f;
	xVel = 0;
	zVel = 0;
	xVelGround = 0;
	zVelGround = 0;
	onPlane = false;
	currNorm.set(0, 1, 0);
}

void PlayerKnuckles::boostMe(float amount)
{
	float rad = sqrtf(xVelGround*xVelGround + zVelGround*zVelGround);
	if (rad > 1)
	{
		float ang = atan2f(-zVelGround, xVelGround);
		rad += amount;
		xVelGround =  rad*cosf(ang);
		zVelGround = -rad*sinf(ang);
	}
}

void PlayerKnuckles::setDisplacement(float xDsp, float yDsp, float zDsp)
{
	xDisp = xDsp;
	yDisp = yDsp;
	zDisp = zDsp;
	isGettingExternallyMoved = true;
}

void PlayerKnuckles::setGravity(float newGrav)
{
	gravity = newGrav;
}

bool PlayerKnuckles::isDying()
{
	return deadTimer != -1;
}

void PlayerKnuckles::setSpindashTimer(int newTimer)
{
	spindashTimer = newTimer;
}

int PlayerKnuckles::getSpindashTimer()
{
	return spindashTimer;
}

bool PlayerKnuckles::isChargingSpindash()
{
	return isSpindashing;
}

void PlayerKnuckles::setIsBall(bool newIsBall)
{
	isBall = newIsBall;
}

float PlayerKnuckles::calculateSpindashSpeed(int spindashCharge)
{
	float mag = spindashPower*spindashCharge;
	float totalSpd = sqrtf(xVelGround*xVelGround + zVelGround*zVelGround);

	float factor = std::fminf(1, 6.5f / totalSpd);

	factor = std::fmaxf(0.85f, factor);

	return factor*mag;
}

bool PlayerKnuckles::isOnGround()
{
	return onPlane;
}

Vector3f* PlayerKnuckles::getCurrNorm()
{
	return &currNorm;
}

Vector3f PlayerKnuckles::getCenterPosition()
{
	float x = getX();
	float y = getY();
	float z = getZ();
	const float r = 5;

	float xrel = xVelGround + xVelAir;
	float zrel = zVelGround + zVelAir;

	float mySpeed = sqrtf(xrel*xrel + zrel*zrel);

	if (onPlane)
	{
		if (mySpeed < 0.01f)
		{
			y += r;
		}
		else
		{
			x += currNorm.x*r;
			y += currNorm.y*r;
			z += currNorm.z*r;
		}
	}
	else
	{
		if (!isBall &&
			!isJumping &&
			!isDropDashing &&
			!isBouncing &&
			!isLightdashing &&
			!isStomping)
		{
			y += r;
		}
	}

	return Vector3f(x, y, z);
}

ShieldMagnet* PlayerKnuckles::getShieldMagnet()
{
	return myShieldMagnet;
}

void PlayerKnuckles::setShieldMagnet(ShieldMagnet* newMagnet)
{
	if (myShieldMagnet != nullptr)
	{
		Main_deleteTransparentEntity(myShieldMagnet);
		myShieldMagnet = nullptr;
	}
	if (myShieldGreen != nullptr)
	{
		Main_deleteTransparentEntity(myShieldGreen);
		myShieldGreen = nullptr;
	}
	myShieldMagnet = newMagnet;
}

ShieldGreen* PlayerKnuckles::getShieldGreen()
{
	return myShieldGreen;
}

void PlayerKnuckles::setShieldGreen(ShieldGreen* newGreen)
{
	if (myShieldMagnet != nullptr)
	{
		Main_deleteTransparentEntity(myShieldMagnet);
		myShieldMagnet = nullptr;
	}
	if (myShieldGreen != nullptr)
	{
		Main_deleteTransparentEntity(myShieldGreen);
		myShieldGreen = nullptr;
	}
	myShieldGreen = newGreen;
}

int PlayerKnuckles::getDiggingTimer()
{
	return diggingTimer;
}

void PlayerKnuckles::increaseCombo()
{
	combo+=1;
}

void PlayerKnuckles::setInvincibleTimer(int newTimer)
{
	invincibleTimer = newTimer;
}

void PlayerKnuckles::setSpeedshoesTimer(int newTimer)
{
	speedShoesTimer = newTimer;
}

void PlayerKnuckles::setOnRocket(bool newOnRocket)
{
	onRocket = newOnRocket;
}