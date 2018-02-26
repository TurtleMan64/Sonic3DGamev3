#ifndef FFHEALPADS_H
#define FFHEALPADS_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class FF_HealPads : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	FF_HealPads();

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif