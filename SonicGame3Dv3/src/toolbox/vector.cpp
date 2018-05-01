#include <math.h>
#include "vector.h"



float Vector3f::getX() { return x; }
float Vector3f::getY() { return y; }
float Vector3f::getZ() { return z; }

void Vector3f::set(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

void Vector3f::set(Vector3f* other)
{
	x = other->x;
	y = other->y;
	z = other->z;
}

float Vector3f::length()
{
	return (float)sqrt((x * x) + (y * y) + (z * z));
}

float Vector3f::lengthSquared()
{
	return (x * x) + (y * y) + (z * z);
}

void Vector3f::normalize() {
	float mag = length();

	x = x / mag;
	y = y / mag;
	z = z / mag;
}

void Vector3f::neg() {
	x = -x;
	y = -y;
	z = -z;
}

void Vector3f::scale(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
}

float Vector3f::dot(Vector3f* other) {
	return x * other->getX() + y * other->getY() + z * other->getZ();
}

Vector3f Vector3f::cross(Vector3f* other) {
	float x_ = y * other->getZ() - z * other->getY();
	float y_ = z * other->getX() - x * other->getZ();
	float z_ = x * other->getY() - y * other->getX();

	return Vector3f(x_, y_, z_);
}

Vector3f Vector3f::operator + (const Vector3f &other) {
	return Vector3f(x + other.x, y + other.y, z + other.z);
}

Vector3f Vector3f::operator - (const Vector3f &other) {
	return Vector3f(x - other.x, y - other.y, z - other.z);
}

Vector3f Vector3f::operator * (const Vector3f &other) {
	return Vector3f(x * other.x, y * other.y, z * other.z);
}

Vector3f Vector3f::operator / (const Vector3f &other) {
	return Vector3f(x / other.x, y / other.y, z / other.z);
}


Vector3f::Vector3f() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3f::Vector3f(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f::Vector3f(Vector3f* base) {
	this->x = base->x;
	this->y = base->y;
	this->z = base->z;
}






float Vector2f::getX() { return x; }
float Vector2f::getY() { return y; }

void Vector2f::set(float newX, float newY)
{
	x = newX;
	y = newY;
}

void Vector2f::set(Vector2f* vec)
{
	x = vec->x;
	y = vec->y;
}

float Vector2f::length() {
	return (float)sqrt((x * x) + (y * y));
}

Vector2f Vector2f::normalized() {
	float mag = length();

	return Vector2f(x / mag, y / mag);
}

void Vector2f::neg() {
	x = -x;
	y = -y;
}

float Vector2f::dot(Vector2f* other) {
	return x * other->getX() + y * other->getY();
}

Vector2f Vector2f::operator + (const Vector2f &other) {
	return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator - (const Vector2f &other) {
	return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::operator * (const Vector2f &other) {
	return Vector2f(x * other.x, y * other.y);
}

Vector2f Vector2f::operator / (const Vector2f &other) {
	return Vector2f(x / other.x, y / other.y);
}

Vector2f Vector2f::operator * (const float &scale)
{
	return Vector2f(x * scale, y * scale);
}


Vector2f::Vector2f() {
	x = 0;
	y = 0;
}

Vector2f::Vector2f(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2f::Vector2f(Vector2f* base) {
	this->x = base->x;
	this->y = base->y;
}















float Vector4f::getX() { return x; }
float Vector4f::getY() { return y; }
float Vector4f::getZ() { return z; }
float Vector4f::getW() { return w; }

void Vector4f::set(float newX, float newY, float newZ, float newW)
{
	x = newX;
	y = newY;
	z = newZ;
	w = newW;
}

void Vector4f::set(Vector4f* other)
{
	x = other->x;
	y = other->y;
	z = other->z;
	w = other->w;
}

float Vector4f::length()
{
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

float Vector4f::lengthSquared()
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

void Vector4f::normalize() {
	float mag = length();

	x = x / mag;
	y = y / mag;
	z = z / mag;
	w = w / mag;
}

void Vector4f::neg() {
	x = -x;
	y = -y;
	z = -z;
	w = -w;
}

void Vector4f::scale(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;
}

float Vector4f::dot(Vector4f* other) {
	return x * other->getX() + y * other->getY() + z * other->getZ() + w * other->getW();
}

Vector4f Vector4f::operator + (const Vector4f &other) {
	return Vector4f(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4f Vector4f::operator - (const Vector4f &other) {
	return Vector4f(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4f Vector4f::operator * (const Vector4f &other) {
	return Vector4f(x * other.x, y * other.y, z * other.z, w * other.w);
}

Vector4f Vector4f::operator / (const Vector4f &other) {
	return Vector4f(x / other.x, y / other.y, z / other.z, w / other.w);
}


Vector4f::Vector4f() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4f::Vector4f(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4f::Vector4f(Vector4f* base) {
	this->x = base->x;
	this->y = base->y;
	this->z = base->z;
	this->w = base->w;
}