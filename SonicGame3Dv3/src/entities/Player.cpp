#include <list>
#include <iostream>
#include <math.h>

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


std::list<TexturedModel*> Player::models;

extern int INPUT_JUMP;
extern int INPUT_ACTION;
extern int INPUT_ACTION2;
extern int INPUT_PREVIOUS_JUMP;
extern int INPUT_PREVIOUS_ACTION;
extern int INPUT_PREVIOUS_ACTION2;
extern float INPUT_X;
extern float INPUT_Y;
extern float INPUT_X2;
extern float INPUT_Y2;

Player::Player(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	currNorm.x = 0;
	currNorm.y = 1;
	currNorm.z = 0;
}

void Player::step()
{
	setMovementInputs();
	adjustCamera();
	moveMeGround();
	if (CollisionChecker::checkCollision(position.x, position.y, position.z, position.x+xVelGround, position.y, position.z+zVelGround))
	{
		xVelGround = 0;
		zVelGround = 0;
	}
	else
	{
		increasePosition(xVelGround, 0, zVelGround);
	}
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

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/Amy/", "Head.obj");
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

	//if (isBall == false)
	//{
		xVelGround += (float)(moveSpeedCurrent*cos(toRadians(cam->getYaw() + movementAngle)));
		zVelGround += (float)(moveSpeedCurrent*sin(toRadians(cam->getYaw() + movementAngle)));
	//}
	//else
	//{
		//xVelGround += (float)(moveSpeedCurrent*cos(toRadians(cam.getYaw() + movementAngle)))*0.8;
		//zVelGround += (float)(moveSpeedCurrent*sin(toRadians(cam.getYaw() + movementAngle)))*0.8;
	//}

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
	//shoulderInput = Input.shoulderInput;
	//selectInput = Input.selectInput;
	//specialInput = INPUT_SPE;

	previousJumpInput = INPUT_PREVIOUS_JUMP;
	previousActionInput = INPUT_PREVIOUS_ACTION;
	previousAction2Input = INPUT_PREVIOUS_ACTION2;
	//previousShoulderInput = Input.previousShoulderInput;
	//previousSelectInput = Input.previousSelectInput;
	//previousSpecialInput = Input.previousSpecialInput;

	movementInputX = INPUT_X;
	movementInputY = INPUT_Y;
	cameraInputX = INPUT_X2;
	cameraInputY = INPUT_Y2;

	//zoomInput = Input.zoomInput;

	float inputMag = (float)sqrt(movementInputX*movementInputX + movementInputY*movementInputY);
	moveSpeedCurrent = moveAcceleration*inputMag;
	moveSpeedAirCurrent = moveAccelerationAir*inputMag;
	movementAngle = (float)toDegrees(atan2(movementInputY, movementInputX));
}

void Player::adjustCamera()
{
	//float time = (float)DisplayManager.getFactor();
	//float time = 1.0f;

	//cameraRadius += (cameraRadiusTarget - cameraRadius) / 20;

	//cameraRadiusTarget += zoomInput*time;
	//cameraRadiusTarget = Math.max(cameraRadiusZoom, cameraRadiusTarget);
	//cameraRadiusTarget = Math.min(cameraRadiusZoomOut, cameraRadiusTarget);

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