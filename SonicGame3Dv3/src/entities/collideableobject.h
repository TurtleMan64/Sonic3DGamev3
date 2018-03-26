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

	void updateCMJustPosition(CollisionModel* cmToUpdate);

	void updateCollisionModel(CollisionModel* cmToUpdate);

	void updateCollisionModelWithZ(CollisionModel* cmToUpdate);

	void updateCMJustPosition();

	void updateCollisionModel();

	void updateCollisionModelWithZ();
};
#endif