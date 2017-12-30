#ifndef RING_H
#define RING_H

class TexturedModel;

#include <list>
#include "entities.h"


class Ring : public Entity
{
private:
	static std::list<TexturedModel*> models;

	static float hitboxH;
	static float hitboxV;

	float xVel;
	float yVel;
	float zVel;
	bool moves;
	int grabTimer;

public:
	Ring();
	Ring(float, float, float);
	Ring(float x, float y, float z, float xVel, float yVel, float zVel);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	//std::string getName();
};
#endif