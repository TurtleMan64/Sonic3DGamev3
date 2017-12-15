#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>


class Vector3f
{
public:
	float x;
	float y;
	float z;

	Vector3f();
	Vector3f(float, float, float);
	Vector3f(Vector3f*);

	float getX();
	float getY();
	float getZ();

	void set(float, float, float);

	float length();

	Vector3f normalized();

	void neg();

	float dot(Vector3f*);

	Vector3f cross(Vector3f*);

	Vector3f operator + (const Vector3f &other);

	Vector3f operator - (const Vector3f &other);

	Vector3f operator * (const Vector3f &other);

	Vector3f operator / (const Vector3f &other);
};

class Vector2f
{
public:
	float x;
	float y;

	Vector2f();
	Vector2f(float, float);
	Vector2f(Vector2f*);

	float getX();
	float getY();

	void set(float, float);

	float length();

	Vector2f normalized();

	void neg();

	float dot(Vector2f*);

	Vector2f operator + (const Vector2f &other);

	Vector2f operator - (const Vector2f &other);

	Vector2f operator * (const Vector2f &other);

	Vector2f operator / (const Vector2f &other);
};
#endif