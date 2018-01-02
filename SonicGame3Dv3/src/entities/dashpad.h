#ifndef DASHPAD_H
#define DASHPAD_H

class TexturedModel;

#include <list>
#include "entities.h"


class Dashpad : public Entity
{
private:
	static std::list<TexturedModel*> models;

	float power;
	float hitRadius;
	int cooldownTimer;
	const static int cooldownTimerMax;

public:
	Dashpad();
	Dashpad(float x, float y, float z, float rotY, float rotZ, float myPower);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif