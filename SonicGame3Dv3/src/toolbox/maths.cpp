#include <cmath>

#include "matrix.h"
#include "vector.h"
#include "../entities/camera.h"
#include "maths.h"
#include "../engineTester/main.h"
#include "../entities/ring.h"
#include "../entities/player.h"

float toRadians(float degrees)
{
	return (degrees*0.01745329251f);
}

float toDegrees(float radians)
{
	return (radians*57.2957795131f);
}

/*
** Blank Matrix4f should have already been created. This function does not allocate any memory to matrix.
*/

void createTransformationMatrix(Matrix4f* matrix, Vector3f* translation, float rx, float ry, float rz, float rs, float scale)
{
	matrix->setIdentity();
	matrix->translate(translation);
	Vector3f vec(0, 0, 0);

	vec.set(0, 1, 0);
	matrix->rotate(toRadians(ry), &vec);

	vec.set(0, 0, 1);
	matrix->rotate(toRadians(rz), &vec);

	vec.set(1, 0, 0);
	matrix->rotate(toRadians(rx), &vec);

	vec.set(0, 0, 1);
	matrix->rotate(toRadians(rs), &vec);

	vec.set(scale, scale, scale);
	matrix->scale(&vec);
}


void createViewMatrix(Matrix4f* matrix, Camera* cam)
{
	matrix->setIdentity();

	//vec.set(0, 0, 1);
	//matrix->rotate(toRadians(cam->getRoll()), &vec);

	Vector3f vec(1, 0, 0);
	matrix->rotate(toRadians(cam->getPitch()), &vec);

	vec.set(0, 1, 0);
	matrix->rotate(toRadians(cam->getYaw()), &vec);

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

int sign(float value)
{
	if (value > 0)
	{
		return 1;
	}
	else if(value < 0)
	{
		return -1;
	}
	return 0;
}

Vector3f mapInputs3(float angle, float mag, Vector3f* VecC)
{
	angle = fmod(angle, (float)(M_PI * 2));
	float tempx = (float)cos(angle)*mag;
	float tempz = (float)sin(angle)*mag;

	float CDir = (float)atan2(VecC->z, VecC->x);
	CDir += (float)(M_PI / 2);
	float Cx = (float)cos(CDir);
	float Cz = (float)sin(CDir);

	float CDist = (float)sqrt(VecC->x*VecC->x + VecC->z*VecC->z);
	float CPitch = (float)(M_PI / 2 + atan2(VecC->y, CDist));

	double result[3] = { 0, 0, 0 }; //storage for the answer
	rotatePoint(result, 0, 0, 0, Cx, 0, Cz, tempx, 0, tempz, CPitch);

	Vector3f res((float)result[0], (float)result[1], (float)result[2]);

	return res;
}

/**
* Calculate the x and z speeds relative to a plane based off
* the previous position you are coming in from
*
* @param xspd the x speed that you are going at before collision
* @param yspd the y speed that you are going at before collision
* @param zspd the z speed that you are going at before collision
* @param A the collision point on the triangle
* @param normal the normal of the triangle
*/
Vector3f calculatePlaneSpeed(float xspd, float yspd, float zspd, Vector3f* colPos, Vector3f* normal)
{
	Vector3f A(xspd, yspd, zspd);
	Vector3f Blue = projectOntoPlane(&A, normal);

	//Rotate normal along y axis 90 degrees
	float CDir = (float)atan2(-normal->z, -normal->x);
	CDir += (float)(M_PI / 2);
	float Cx = (float)cos(CDir);
	float Cz = (float)sin(CDir);

	float CDist = (float)sqrt(normal->x*normal->x + normal->z*normal->z);
	float CPitch = (float)(M_PI / 2 + atan2(-normal->y, CDist));

	double result[3] = { 0, 0, 0 }; //storage for the answer
	rotatePoint(result, 0, 0, 0, Cx, 0, Cz, Blue.x, Blue.y, Blue.z, -CPitch);

	return Vector3f((float)result[0], (float)result[1], (float)result[2]);



	//normY = -std::fabs(normY);
	//normY = std::fmax(0.001f, normY);

	//find the relative x speed
	/*
	float xDiff = xspd;
	float yDiff = yspd;
	float dist = (float)sqrt(xDiff*xDiff + yDiff*yDiff);
	float angle1 = (float)atan2(-normY, -normX);
	float angle2 = (float)atan2(yDiff, xDiff);
	float actualAngle = angle2 - angle1;
	float xLength = (float)sin(actualAngle)*dist;

	//find the relative z speed
	float zDiff = zspd;//A.z-B.z;
	dist = (float)sqrt(zDiff*zDiff + yDiff*yDiff);
	angle1 = (float)atan2(-normY, -normZ);
	angle2 = (float)atan2(yDiff, zDiff);
	actualAngle = angle2 - angle1;
	float zLength = (float)sin(actualAngle)*dist;

	std::fprintf(stdout, "wall norm: %f, %f, %f\n", normX, normY, normZ);
	std::fprintf(stdout, "speeds: %f, %f, %f\n", xspd, yspd, zspd);
	std::fprintf(stdout, "ouput: %f, %f\n", xLength, zLength);
	std::fprintf(stdout, "\n");

	return Vector3f(xLength, 0, zLength);
	*/
}

//Equation from https://sites.google.com/site/glennmurray/Home/rotation-matrices-and-formulas
//Point that axis goes through,
//direction of axis,
//point to rotate, 
//angle of rotation
void rotatePoint(double result[],
	double a, double b, double c,
	double u, double v, double w,
	double x, double y, double z,
	double theta)
{
	double l = sqrt(u*u + v*v + w*w);

	double l2 = l*l;

	double u2 = u*u;
	double v2 = v*v;
	double w2 = w*w;
	double cosT = cos(theta);
	double oneMinusCosT = 1 - cosT;
	double sinT = sin(theta);

	result[0] = ((a*(v2 + w2) - u*(b*v + c*w - u*x - v*y - w*z)) * oneMinusCosT
		+ l2*x*cosT
		+ l*(-c*v + b*w - w*y + v*z)*sinT) / l2;

	result[1] = ((b*(u2 + w2) - v*(a*u + c*w - u*x - v*y - w*z)) * oneMinusCosT
		+ l2*y*cosT
		+ l*(c*u - a*w + w*x - u*z)*sinT) / l2;

	result[2] = ((c*(u2 + v2) - w*(a*u + b*v - u*x - v*y - w*z)) * oneMinusCosT
		+ l2*z*cosT
		+ l*(-b*u + a*v - v*x + u*y)*sinT) / l2;
}

/**
* @param initialVelocity
* @param surfaceNormal
* @param elasticity Scale of the resulting vector relative to the original velocity
*/
Vector3f bounceVector(Vector3f* initialVelocity, Vector3f* surfaceNormal, float elasticity)
{
	Vector3f twoNtimesVdotN(surfaceNormal);
	twoNtimesVdotN.scale(-2 * initialVelocity->dot(surfaceNormal));

	Vector3f Vnew = (twoNtimesVdotN + initialVelocity);
	Vnew.scale(elasticity);

	return Vnew;
}


//Projects vector A to be parallel to vector normal
Vector3f projectOntoPlane(Vector3f* A, Vector3f* normal)
{
	Vector3f B(0, 0, 0);
	Vector3f C(A);
	Vector3f N(normal->x, normal->y, normal->z);

	N.scale(C.dot(&N));
	B = C - N;

	return B;
}

/** Returns the point on a sphere that has the given angles from the center
* @param angH in radians
* @param angV in radians
* @param radius
* @return
*/
Vector3f spherePositionFromAngles(float angH, float angV, float radius)
{
	float y = (float)(radius*sin(angV));
	float hpt = (float)(radius*cos(angV));

	float x = (float)(hpt*cos(angH));
	float z = (float)(hpt*sin(angH));

	return Vector3f(x, y, z);
}

float random()
{
	return (rand()%100000)/100000.0f;
}

float nextGaussian()
{
	return (float)(*Global::distribution)((*Global::generator));
}