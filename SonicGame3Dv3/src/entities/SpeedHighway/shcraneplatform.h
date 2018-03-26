#ifndef SHCRANEPLATFORM_H
#define SHCRANEPLATFORM_H

class TexturedModel;
class Source;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class SH_CranePlatform : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;
	CollisionModel* collideModelTransformed2;

	Vector3f pointPos1;
	Vector3f pointPos2;

	float speed;
	Vector3f moveDir;
	Vector3f newPos;
	bool isMoving;
	bool canMove;
	Source* cranePlatSource = nullptr;

	int point2GreaterX;
	int point2GreaterY;
	int point2GreaterZ;

public:
	SH_CranePlatform();
	SH_CranePlatform(float x, float y, float z, float rotY, float speed, int point1ID, int point2ID);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif
