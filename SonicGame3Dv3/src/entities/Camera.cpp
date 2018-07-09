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
	//target.set(0,0,0);
	pitch = 0;
	yaw = 0;
	roll = 0;
}

void Camera::refresh()
{
	//float xDiff = position.x - target.x;
	//float zDiff = position.z - target.z;
	//float yDiff = position.y - target.y;
	//float hDist = sqrtf(xDiff*xDiff + zDiff*zDiff);

	//yaw   = -toDegrees(atan2f(-zDiff, xDiff))-90;
	//pitch =  toDegrees(atan2f(yDiff, hDist));

	Vector3f off(
		-cosf(toRadians(yaw + 90))*((cosf(toRadians(pitch)))),
		 sinf(toRadians(pitch + 180)),
		-sinf(toRadians(yaw + 90))*((cosf(toRadians(pitch)))));

	fadePosition1.x = position.x + off.x*0.7f;
	fadePosition1.y = position.y + off.y*0.7f;
	fadePosition1.z = position.z + off.z*0.7f;

	fadePosition2.x = position.x + off.x*0.55f;
	fadePosition2.y = position.y + off.y*0.55f;
	fadePosition2.z = position.z + off.z*0.55f;

	if (position.y < 0)
	{
		Vector3f partVel(0, 0, 0);
		new Particle(ParticleResources::textureInWater, &fadePosition1, &partVel, 0, 10, 0, 400, 0, true);
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

Vector3f* Camera::getFadePosition1()
{
	return &fadePosition1;
}

Vector3f* Camera::getFadePosition2()
{
	return &fadePosition2;
}

//void Camera::setTarget(float x, float y, float z)
//{
	//target.set(x, y, z);
//}

//void Camera::setTarget(Vector3f* newTarget)
//{
	//target.set(newTarget);
//}