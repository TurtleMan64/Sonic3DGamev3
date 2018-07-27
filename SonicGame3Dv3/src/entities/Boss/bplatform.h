#ifndef BPLATFORM_H
#define BPLATFORM_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class B_Platform : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;
	int timer;
	const int timerMax = 200;

public:
	B_Platform();
	B_Platform(float x, float y, float z);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif