#include <glad/glad.h>

#include "../models/models.h"
#include "../toolbox/vector.h"
#include "entities.h"

#include <list>

#ifndef RING_H
#define RING_H
class Ring : public Entity
{
public:
	Ring();
	Ring(float, float, float);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif