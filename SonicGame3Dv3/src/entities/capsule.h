#ifndef CAPSULE_H
#define CAPSULE_H

class TexturedModel;
class Body;

#include <list>
#include "entities.h"
#include "collideableobject.h"

class Capsule : public CollideableObject
{
private:
	static std::list<TexturedModel*> modelsBase;
	static std::list<TexturedModel*> modelsBaseBroke;
	static std::list<TexturedModel*> modelsTop;
	static CollisionModel* cmOriginalBase;
	static CollisionModel* cmOriginalTop;
	
	CollisionModel* collideModelTopTransformed;
	
	Body* top;
	
	bool opened;
	int openedTimer;

public:
	Capsule();
	Capsule(float x, float y, float z);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif