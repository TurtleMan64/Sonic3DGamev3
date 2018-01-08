#ifndef SPIKEBALL_H
#define SPIKEBALL_H

class TexturedModel;

#include <list>
#include "entities.h"


class Spikeball : public Entity
{
private:
	static std::list<TexturedModel*> models;

	float centerX;
	float centerY;
	float centerZ;

	float radius;
	float angVel;

public:
	Spikeball();
	Spikeball(float x, float y, float z, float radius, float angVel);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif