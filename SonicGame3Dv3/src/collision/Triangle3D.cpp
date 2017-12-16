#include <math.h>
#include "triangle3d.h"
#include "../toolbox/vector.h"


Triangle3D::Triangle3D(Vector3f* newP1, Vector3f* newP2, Vector3f* newP3, char type, int sound, char particle)
{
	this->p1X = newP1->x;
	this->p1Y = newP1->y;
	this->p1Z = newP1->z;

	this->p2X = newP2->x;
	this->p2Y = newP2->y;
	this->p2Z = newP2->z;

	this->p3X = newP3->x;
	this->p3Y = newP3->y;
	this->p3Z = newP3->z;

	this->type = type;
	this->sound = sound;
	this->particle = particle;

	generateValues();
}

void Triangle3D::generateValues()
{
	Vector3f vec1(p1X - p3X, p1Y - p3Y, p1Z - p3Z);
	Vector3f vec2(p2X - p3X, p2Y - p3Y, p2Z - p3Z);

	Vector3f cross = vec1.cross(&vec2);

	float newD = cross.x*p3X + cross.y*p3Y + cross.z*p3Z;

	A = cross.x;
	B = cross.y;
	C = cross.z;
	D = -newD;

	float mag = (float)(sqrt(A*A+B*B+C*C));

	if (mag != 0)
	{
		normal.x = A / mag;
		normal.y = B / mag;
		normal.z = C / mag;
	}
	else
	{
		normal.x = 0;
		normal.y = 1;
		normal.z = 0;
	}

	maxX = (float)fmax(p1X, fmax(p2X, p3X));
	minX = (float)fmin(p1X, fmin(p2X, p3X));
	maxY = (float)fmax(p1Y, fmax(p2Y, p3Y));
	minY = (float)fmin(p1Y, fmin(p2Y, p3Y));
	maxZ = (float)fmax(p1Z, fmax(p2Z, p3Z));
	minZ = (float)fmin(p1Z, fmin(p2Z, p3Z));
}

int Triangle3D::isSlippery()
{
	if (type == 1)
	{
		return 1;
	}

	return 0;
}