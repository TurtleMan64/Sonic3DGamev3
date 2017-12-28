#ifndef RING_H
#define RING_H

class TexturedModel;

#include <list>
#include "entities.h"


class Ring : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	Ring();
	Ring(float, float, float);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	//std::string getName();
};
#endif