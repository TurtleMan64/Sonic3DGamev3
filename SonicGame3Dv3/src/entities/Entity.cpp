#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"

Entity::Entity()
{

}

Entity::Entity(TexturedModel* model, Vector3f* position, float rotX, float rotY, float rotZ, float scale)
{
	memcpy(&this->model, model, sizeof(TexturedModel));
	memcpy(&this->position, position, sizeof(Vector3f));
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
}

void step()
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

TexturedModel* Entity::getModel()
{
	return &model;
}
void Entity::setModel(TexturedModel* newModel)
{
	memcpy(&this->model, newModel, sizeof(TexturedModel));
}

Vector3f* Entity::getPosition()
{
	return &position;
}
void Entity::setPosition(Vector3f* newPos)
{
	memcpy(&this->position, newPos, sizeof(Vector3f));
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