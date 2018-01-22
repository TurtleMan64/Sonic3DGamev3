#include "collideableobject.h"

#include "../collision/collisionmodel.h"


CollideableObject::CollideableObject()
{

}

void CollideableObject::updateCMJustPosition()
{
	collideModelOriginal->transformModel(collideModelTransformed, getPosition());
}

void CollideableObject::updateCollisionModel()
{
	collideModelOriginal->transformModel(collideModelTransformed, getPosition(), -getRotY());
}

void CollideableObject::updateCollisionModelWithZ()
{
	collideModelOriginal->transformModel(collideModelTransformed, getPosition(), -getRotY(), getRotZ());
}