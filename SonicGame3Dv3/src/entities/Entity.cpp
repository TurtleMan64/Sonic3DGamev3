#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"

#include <list>
#include <iostream>

Entity::Entity()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0; 
	this->scale = 1;
	this->visible = 1;
}

Entity::Entity(Vector3f* position, float rotX, float rotY, float rotZ, float scale)
{
	this->position.x = position->x;
	this->position.y = position->y;
	this->position.z = position->z;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
	this->visible = 1;
}

void Entity::step()
{

}

void Entity::increasePosition(float dx, float dy, float dz)
{
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz)
{
	rotX += dx;
	rotY += dy;
	rotZ += dz;
}

std::list<TexturedModel*>* Entity::getModels()
{
	return nullptr;
}

Vector3f* Entity::getPosition()
{
	return &position;
}
void Entity::setPosition(Vector3f* newPos)
{
	this->position.x = newPos->x;
	this->position.y = newPos->y;
	this->position.z = newPos->z;
}
void Entity::setPosition(float newX, float newY, float newZ)
{
	this->position.x = newX;
	this->position.y = newY;
	this->position.z = newZ;
}

float Entity::getRotX()
{
	return rotX;
}
void Entity::setRotX(float newRotX)
{
	rotX = newRotX;
}

float Entity::getRotY()
{
	return rotY;
}
void Entity::setRotY(float newRotY)
{
	rotY = newRotY;
}

float Entity::getRotZ()
{
	return rotZ;
}
void Entity::setRotZ(float newRotZ)
{
	rotZ = newRotZ;
}

float Entity::getScale()
{
	return scale;
}
void Entity::setScale(float newScale)
{
	scale = newScale;
}

int Entity::getVisible()
{
	return visible;
}
void Entity::setVisible(int newVisible)
{
	visible = newVisible;
}

float Entity::getX()
{
	return position.x;
}

float Entity::getY()
{
	return position.y;
}

float Entity::getZ()
{
	return position.z;
}