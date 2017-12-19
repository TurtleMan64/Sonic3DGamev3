#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

class Triangle3D;
class CollisionModel;

#include <math.h>
#include <list>
#include "../toolbox/vector.h"


class CollisionChecker
{
private:
	static Vector3f collidePosition;
	static Triangle3D* collideTriangle;
	//static CollisionModel* stageCollideModel;
	static std::list<CollisionModel*> collideModels;
	static bool checkPlayer;


public:
	static void initChecker();

	/**
	*  Makes the next collision check set which collision
	*  model the player has collided with, and sets that model
	*  to touching the player.
	*/
	static void setCheckPlayer();

	/**
	*  Sets all collision models to not have the player on them
	*/
	static void falseAlarm();

	static bool checkCollision(
		float px1, float py1, float pz1,
		float px2, float py2, float pz2);

	static bool checkPointInTriangle3D(
		double checkx, double checky, double checkz,
		double cx1, double cy1, double cz1,
		double cx2, double cy2, double cz2,
		double cx3, double cy3, double cz3,
		double nX, double nY, double nZ);

	static bool checkPointInTriangle2D(
		double x, double y,
		double x1, double y1,
		double x2, double y2,
		double x3, double y3);

	//delete's all collide models
	static void deleteAllCollideModels();

	//use this when reloading the same level - then you dont have to regenerate the quad trees
	static void deleteAllCollideModelsExceptQuadTrees();

	//static void deleteStageCollideModel();

	static void deleteCollideModel(CollisionModel* cm);

	static void addCollideModel(CollisionModel* cm);

	//based off of the last collision check
	static Triangle3D* getCollideTriangle();

	//based off of the last collision check
	static Vector3f* getCollidePosition();
};

#endif