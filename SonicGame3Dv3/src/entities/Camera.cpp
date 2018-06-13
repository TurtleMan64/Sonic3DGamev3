#include <glad/glad.h>

#include "../models/models.h"
#include "../toolbox/vector.h"
#include "camera.h"
#include "../toolbox/input.h"
#include "../toolbox/maths.h"
#include "../particles/particleresources.h"
#include "../particles/particle.h"

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
	position.y = 20;
	position.z = 0;
	prevPos.x = 0;
	prevPos.y = 20;
	prevPos.z = 0;
	pitch = 0;
	yaw = 0;
	roll = 0;
}

void Camera::refresh()
{
	float radius = 0.6f;
	Vector3f newPos(
		position.x - cosf(toRadians(yaw + 90))*(radius*(cosf(toRadians(pitch)))),
		position.y + sinf(toRadians(pitch + 180))*radius,
		position.z - sinf(toRadians(yaw + 90))*(radius*(cosf(toRadians(pitch)))));

	fadePosition.x = newPos.x;
	fadePosition.y = newPos.y;
	fadePosition.z = newPos.z;

	if (position.y < 0)
	{
		Vector3f partVel(0, 0, 0);
		new Particle(ParticleResources::textureInWater, &fadePosition, &partVel, 0, 10, 0, 400, 0, true);
	}
}

Vector3f Camera::calcVelocity()
{
	Vector3f diff(getPosition());

	diff = diff-prevPos;

	prevPos.set(getPosition());

	return diff;
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

void Camera::invertPitch()
{
	pitch = -pitch;
}

Vector3f* Camera::getFadePosition()
{
	return &fadePosition;
}