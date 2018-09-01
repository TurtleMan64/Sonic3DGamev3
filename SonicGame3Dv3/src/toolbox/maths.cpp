#include <cmath>
#include<random>
#include<chrono>

#include "matrix.h"
#include "vector.h"
#include "../entities/camera.h"
#include "maths.h"
#include "../engineTester/main.h"
#include "../entities/ring.h"
#include "../entities/playersonic.h"

std::mt19937* Maths::generatorUniform = new std::mt19937(0);
std::uniform_real_distribution<float>* Maths::distributionUniform = new std::uniform_real_distribution<float>(0.0f, 1.0f);

std::default_random_engine* Maths::generatorNormal = new std::default_random_engine(0);
std::normal_distribution<float>* Maths::distributionNormal = new std::normal_distribution<float>(0.0f, 1.0f);

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
	Vector3f vec;

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

void createTransformationMatrix(Matrix4f* matrix, Vector3f* translation, float rx, float ry, float rz, float rs, float scaleX, float scaleY, float scaleZ)
{
	matrix->setIdentity();
	matrix->translate(translation);
	Vector3f vec;

	vec.set(0, 1, 0);
	matrix->rotate(toRadians(ry), &vec);

	vec.set(0, 0, 1);
	matrix->rotate(toRadians(rz), &vec);

	vec.set(1, 0, 0);
	matrix->rotate(toRadians(rx), &vec);

	vec.set(0, 0, 1);
	matrix->rotate(toRadians(rs), &vec);

	vec.set(scaleX, scaleY, scaleZ);
	matrix->scale(&vec);
}

void createTransformationMatrix(Matrix4f* result, Vector2f* translation, float rotation, Vector2f* scale)
{
	result->setIdentity();
	result->translate(translation);
	Vector3f axis(0, 0, 1);
	result->rotate(toRadians(rotation), &axis);
	result->scale(scale);
}

//Based on how sadx calculates rotations
void createTransformationMatrixSADX(Matrix4f* matrix, Vector3f* translation, float rx, float ry, float rz, float scale)
{
	matrix->setIdentity();
	matrix->translate(translation);
	Vector3f vec;

	vec.set(0, 0, 1);
	matrix->rotate(toRadians(rz), &vec);

	vec.set(1, 0, 0);
	matrix->rotate(toRadians(rx), &vec);

	vec.set(0, 1, 0);
	matrix->rotate(toRadians(ry), &vec);

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


Matrix4f Maths::lookAtRH(Vector3f* eye, Vector3f* focus, Vector3f* up)
{
	Vector3f f(focus);
	f = f-eye;
	f.normalize();

	Vector3f s = f.cross(up);
	s.normalize();

	Vector3f u = s.cross(&f);

	Matrix4f result;

	result.m00 =  s.x;
	result.m10 =  s.y;
	result.m20 =  s.z;
	result.m01 =  u.x;
	result.m11 =  u.y;
	result.m21 =  u.z;
	result.m02 = -f.x;
	result.m12 = -f.y;
	result.m22 = -f.z;
	result.m30 = -s.dot(eye);
	result.m31 = -u.dot(eye);
	result.m32 =  f.dot(eye);

	return result;
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

//angle in radians
Vector3f mapInputs3(float angle, float mag, Vector3f* VecC)
{
	angle = fmod(angle, (float)(M_PI * 2));
	float tempx = cosf(angle)*mag;
	float tempz = sinf(angle)*mag;

	float CDir = atan2f(VecC->z, VecC->x);
	CDir += (float)(M_PI / 2);
	float Cx = cosf(CDir);
	float Cz = sinf(CDir);

	float CDist = sqrtf(VecC->x*VecC->x + VecC->z*VecC->z);
	float CPitch = (float)(M_PI / 2 + atan2(VecC->y, CDist));

	float result[3] = { 0, 0, 0 }; //storage for the answer
	rotatePoint(result, 0, 0, 0, Cx, 0, Cz, tempx, 0, tempz, CPitch);

	Vector3f res(result[0], result[1], result[2]);

	return res;
}

//angle in radians
Vector3f mapCamera(float yaw, float pitch, float mag, Vector3f* VecC)
{
	yaw = fmod(yaw, (float)(M_PI * 2));
	float tempx = cosf(yaw)*mag;
	float tempz = sinf(yaw)*mag;
	float tempy = 0;

	float rotAxisX = cosf(yaw + (float)(M_PI / 2.0f));
	float rotAxisZ = sinf(yaw + (float)(M_PI / 2.0f));

	pitch = fmod(pitch, (float)(M_PI * 2));

	float result2[3] = { 0, 0, 0 };
	rotatePoint(result2, 0, 0, 0, rotAxisX, 0, rotAxisZ, tempx, tempy, tempz, pitch);
	tempx = result2[0];
	tempy = result2[1];
	tempz = result2[2];


	float CDir = atan2f(VecC->z, VecC->x);
	CDir += (float)(M_PI / 2);
	float Cx = cosf(CDir);
	float Cz = sinf(CDir);

	float CDist = sqrtf(VecC->x*VecC->x + VecC->z*VecC->z);
	float CPitch = (float)(M_PI / 2 + atan2f(VecC->y, CDist));

	float result[3] = { 0, 0, 0 }; //storage for the answer
	rotatePoint(result, 0, 0, 0, Cx, 0, Cz, tempx, tempy, tempz, CPitch);

	Vector3f res(result[0], result[1], result[2]);

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
Vector3f calculatePlaneSpeed(float xspd, float yspd, float zspd, Vector3f* normal)
{
	Vector3f A(xspd, yspd, zspd);
	Vector3f Blue = projectOntoPlane(&A, normal);

	//Rotate normal along y axis 90 degrees
	float CDir = atan2f(-normal->z, -normal->x);
	CDir += (float)(M_PI / 2);
	float Cx = cosf(CDir);
	float Cz = sinf(CDir);

	float CDist = sqrtf(normal->x*normal->x + normal->z*normal->z);
	float CPitch = ((float)(M_PI / 2) + atan2f(-normal->y, CDist));

	float result[3] = { 0, 0, 0 }; //storage for the answer
	rotatePoint(result, 0, 0, 0, Cx, 0, Cz, Blue.x, Blue.y, Blue.z, -CPitch);

	return Vector3f(result[0], result[1], result[2]);



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
void rotatePoint(float result[],
	float a, float b, float c,
	float u, float v, float w,
	float x, float y, float z,
	float theta)
{
	float l = sqrtf(u*u + v*v + w*w);

	float l2 = l*l;

	float u2 = u*u;
	float v2 = v*v;
	float w2 = w*w;
	float cosT = cosf(theta);
	float oneMinusCosT = 1 - cosT;
	float sinT = sinf(theta);

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
	float y   = (radius*sinf(angV));
	float hpt = (radius*cosf(angV));

	float x = (hpt*cosf(angH));
	float z = (hpt*sinf(angH));

	return Vector3f(x, y, z);
}

Vector3f randomPointOnSphere()
{
	//float u = Maths::nextUniform();
	//float v = Maths::nextUniform();

	//float lat = 2*((float)M_PI)*u;
	//float lng = acosf(2*v - 1);

	//return spherePositionFromAngles(lng, lat, 1);


	float z   = Maths::nextUniform()*2 - 1;
	float lng = Maths::nextUniform()*2*(float)M_PI;

	float radius = sqrtf(1-(z)*(z));

	float x = radius*cosf(lng);
	float y = radius*sinf(lng);

	return Vector3f(x, y, z);


	//Makes a 3D Bernoulli Lemniscate for some reason???

	//float theta = 2 * (float)M_PI * Maths::nextUniform();
    //float phi = acosf(1 - 2 * Maths::nextUniform());
    //float x = sinf(phi) * cosf(theta);
    //float y = sinf(phi) * sinf(theta);
    //float z = cosf(phi);

	//return spherePositionFromAngles(x, y, z);
}

float Maths::random()
{
	return (rand() % RAND_MAX) / ((float)(RAND_MAX));
}

float Maths::nextGaussian()
{
	return (*Maths::distributionNormal)(*Maths::generatorNormal);
}

float Maths::nextUniform()
{
	return (*Maths::distributionUniform)(*Maths::generatorUniform);
}