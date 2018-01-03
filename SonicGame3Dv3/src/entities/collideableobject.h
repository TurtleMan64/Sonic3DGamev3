#ifndef COLLIDEABLEOBJECT_H
#define COLLIDEABLEOBJECT_H

class CollisionModel;

#include "entities.h"

class CollideableObject : public Entity
{
protected:
	CollisionModel* collideModelOriginal;
	CollisionModel* collideModelTransformed;

public:
	CollideableObject();

	void updateCMJustPosition();

	void updateCollisionModel();

	void updateCollisionModelWithZ();
};
#endif