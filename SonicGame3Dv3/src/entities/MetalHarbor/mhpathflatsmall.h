#ifndef MHPATHFLATSMALL_H
#define MHPATHFLATSMALL_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class MH_PathFlatSmall : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	MH_PathFlatSmall();
	MH_PathFlatSmall(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif
