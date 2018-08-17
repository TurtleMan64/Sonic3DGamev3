#ifndef MHTANK_H
#define MHTANK_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class MH_Tank : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	MH_Tank();
	MH_Tank(float x, float y, float z);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif
