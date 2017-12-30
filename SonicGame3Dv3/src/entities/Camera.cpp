#include <glad/glad.h>

#include "../models/models.h"
#include "../toolbox/vector.h"
#include "camera.h"
#include "../toolbox/input.h"
#include "../toolbox/maths.h"

#include <cmath>

extern float INPUT_X;
extern float INPUT_Y;
extern float INPUT_X2;
extern float INPUT_Y2;

extern bool INPUT_ACTION;
extern bool INPUT_ACTION2;
extern bool INPUT_JUMP;

Camera::Camera()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	pitch = 0;
	yaw = 0;
	roll = 0;
}

void Camera::refresh()
{
	float radius = 5;
	Vector3f newPos(
		position.x - (float)(cos(toRadians(yaw + 90))*(radius*(cos(toRadians(pitch))))),
		position.y + (float)(sin(toRadians(pitch + 180))*radius),
		position.z - (float)(sin(toRadians(yaw + 90))*(radius*(cos(toRadians(pitch))))));

	fadePosition.x = newPos.x;
	fadePosition.y = newPos.y;
	fadePosition.z = newPos.z;
}

Vector3f* Camera::getPosition()
{
	return &position;
}
void Camera::setPosition(Vector3f* newPos)
{
	position.x = newPos->x;
	position.y = newPos->y;
	position.z = newPos->z;
}

float Camera::getPitch()
{
	return pitch;
}
void Camera::setPitch(float newPitch)
{
	pitch = newPitch;
}

float Camera::getYaw()
{
	return yaw;
}
void Camera::setYaw(float newYaw)
{
	yaw = newYaw;
}

float Camera::getRoll()
{
	return roll;
}
void Camera::setRoll(float newRoll)
{
	roll = newRoll;
}