#include <glad/glad.h>

#include "../models/models.h"
#include "../toolbox/vector.h"
#include "camera.h"
#include "../toolbox/input.h"

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

void Camera::move()
{
	position.x += INPUT_X*1.5f;
	position.z += INPUT_Y*1.5f;

	position.y += INPUT_JUMP;

	yaw += INPUT_X2;
	pitch += INPUT_Y2;
}

Vector3f* Camera::getPosition()
{
	return &position;
}
void Camera::setPosition(Vector3f* newPos)
{
	memcpy(&this->position, newPos, sizeof(Vector3f));
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