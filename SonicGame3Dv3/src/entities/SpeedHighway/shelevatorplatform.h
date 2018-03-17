#ifndef SHELEVATORPLATFORM_H
#define SHELEVATORPLATFORM_H

class TexturedModel;
class Source;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class SH_ElevatorPlatform : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

	Vector3f pointPos[4];

	int pointIDs[4];
	int currentState;

	float speed;
	Vector3f moveDir[4];
	Vector3f newPos;
	Source* cranePlatSource = nullptr;

	Vector3f pointGreaterPos[4];

public:
	SH_ElevatorPlatform();
	SH_ElevatorPlatform(float x, float y, float z, float rotY, float speed, int point1ID, int point2ID, int point3ID, int point4ID);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif
