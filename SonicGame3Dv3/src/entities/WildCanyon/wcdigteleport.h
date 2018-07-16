#ifndef WCDIGTELEPORT_H
#define WCDIGTELEPORT_H

class TexturedModel;

#include "../entities.h"
#include "../collideableobject.h"
#include <list>


class WC_DigTeleport : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

	Vector3f teleportLocation;

public:
	WC_DigTeleport(
		float x, float y, float z, 
		float yRot,
		float xTarget, float yTarget, float zTarget);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif