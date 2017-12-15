#ifndef PLAYER_H
#define PLAYER_H

class TexturedModel;

#include <list>

#include "entities.h"
#include "../toolbox/vector.h"


class Player : public Entity
{
private:
	static std::list<TexturedModel*> models;

	float xVel = 0;
	float yVel = 0;
	float zVel = 0;

	float xVelGround = 0;
	float zVelGround = 0;

	float xVelAir = 0;
	float zVelAir = 0;

	float cameraRadius = 104;
	float cameraRadiusTarget = 104;
	const float cameraLaziness = 3;
	const float cameraRadiusZoom = 40;
	const float cameraRadiusZoomOut = 104;
	float cameraYawTarget = 0;
	float cameraPitchTarget = 0;
	const float headHeight = 12;

	Vector3f currNorm;

	const float moveAcceleration = 0.07f;
	const float moveAccelerationAir = 0.035f;

	//movement inputs
	char jumpInput = 0;
	char actionInput = 0;
	char action2Input = 0;
	char shoulderInput = 0;
	char selectInput = 0;
	char specialInput = 0;
	char previousJumpInput = 0;
	char previousActionInput = 0;
	char previousAction2Input = 0;
	char previousShoulderInput = 0;
	char previousSelectInput = 0;
	char previousSpecialInput = 0;
	char zoomInput = 0;
	float movementInputX = 0;
	float movementInputY = 0;
	float cameraInputX = 0;
	float cameraInputY = 0;
	float moveSpeedCurrent = 0;
	float moveSpeedAirCurrent = 0;
	float movementAngle = 0;

public:
	Player(float, float, float);

	void step();

	void adjustCamera();

	void moveMeGround();

	void setMovementInputs();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif