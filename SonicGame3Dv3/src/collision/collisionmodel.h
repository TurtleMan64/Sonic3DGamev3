#ifndef COLLISIONMODEL_H
#define COLLISIONMODEL_H

class Vector3f;
class Triangle3D;

#include <math.h>
#include <list>


class CollisionModel
{
public:
	std::list<Triangle3D*> triangles;

	bool playerIsOn;

	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;

	CollisionModel();

	void generateMinMaxValues();

	void offsetModel(Vector3f* offset);

	void rotateModelY(float yRot, Vector3f* center);

	//makes a collision model be the transformed version of this collision model
	void transformModel(CollisionModel* targetModel, Vector3f* translate, float yRot, float zRot);

	//makes a collision model be the transformed version of this collision model
	void transformModel(CollisionModel* targetModel, Vector3f* translate, float yRot);

	//makes a collision model be the transformed version of this collision model
	void transformModel(CollisionModel* targetModel, Vector3f* translate);

	//calls delete on every Triangle3D contained within triangles list.
	// this MUST be called before this object is deleted, or you memory leak
	// the triangles in the lsit
	void deleteAllTriangles();
};

#endif