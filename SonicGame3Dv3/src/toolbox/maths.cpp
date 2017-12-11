#include <math.h>

#include "matrix.h"
#include "vector.h"
#include "../entities/camera.h"
#include "maths.h"

float toRadians(float degrees)
{
	return (float)(degrees*0.01745329251);
}

float toDegrees(float radians)
{
	return (float)(radians*57.2957795131);
}

/*
** Blank Matrix4f should have already been created. This function does not allocate any memory to matrix.
*/

void createTransformationMatrix(Matrix4f* matrix, Vector3f* translation, float rx, float ry, float rz, float scale)
{
	matrix->setIdentity();
	matrix->translate(translation);
	Vector3f vec(1, 0, 0);
	matrix->rotate(toRadians(rx), &vec);
	vec.set(0, 1, 0);
	matrix->rotate(toRadians(ry), &vec);
	vec.set(0, 0, 1);
	matrix->rotate(toRadians(rz), &vec);
	vec.set(scale, scale, scale);
	matrix->scale(&vec);
}


void createViewMatrix(Matrix4f* matrix, Camera* cam)
{
	matrix->setIdentity();
	Vector3f vec(1, 0, 0);
	matrix->rotate(toRadians(cam->getPitch()), &vec);
	vec.set(0, 1, 0);
	matrix->rotate(toRadians(cam->getYaw()), &vec);

	//roll if you want to 

	Vector3f camPos(cam->getPosition());
	camPos.neg();
	matrix->translate(&camPos);
}


//Returns the difference between the two angles
//ang1 and ang2 should be in degrees
float compareTwoAngles(float origAng1, float origAng2)
{
	float ang1 = (float)fmod(fmod(origAng1, 360) + 360, 360);
	float ang2 = (float)fmod(fmod(origAng2, 360) + 360, 360);

	float d = (float)fmod(fabs(ang1 - ang2), 360);
	float r = d > 180 ? 360 - d : d;

	//calculate sign
	int sign = (ang1 - ang2 >= 0 && ang1 - ang2 <= 180) || (ang1 - ang2 <= -180 && ang1 - ang2 >= -360) ? 1 : -1;
	r *= sign;

	return r;
}