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
<<<<<<< HEAD

	CollisionModel* collideModelTransformed2;
	CollisionModel* collideModelTransformedBackWall;
	static CollisionModel* cmOriginalBackWall;
=======
	static CollisionModel* cmOriginalBackWall;

	CollisionModel* collideModelTransformed2;
	CollisionModel* collideModelTransformedBackWall;
>>>>>>> upstream/master

	Vector3f pointPos1;
	Vector3f pointPos2;

	float speed;
	bool isMoving;
	bool canMove;
	Source* cranePlatSource = nullptr;

	Vector3f oldPos;

	Vector3f pointDifference;
	float pointLength;

	float timeOffset;

public:
	SH_CranePlatform();
	SH_CranePlatform(float x, float y, float z, float rotY, float speed, int point1ID, int point2ID);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif
