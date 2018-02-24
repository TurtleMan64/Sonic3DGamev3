#ifndef TPSPINNINGFLOOR_H
#define TPSPINNINGFLOOR_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class TP_SpinningFloor : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	TP_SpinningFloor();
	TP_SpinningFloor(float x, float y, float z);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif