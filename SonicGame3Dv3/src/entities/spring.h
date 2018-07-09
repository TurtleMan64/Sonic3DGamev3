#ifndef SRING_H
#define SRING_H

class TexturedModel;

#include <list>
#include "entities.h"


class Spring : public Entity
{
private:
	static std::list<TexturedModel*> models;

	float springPower;
	float springRadius;
	int cooldownTimer;
	int cooldownTimerMax;

public:
	Spring();
	Spring(float x, float y, float z, float rotY, float rotZ, float myPower, int cooldownMax);

	void step();

	float getSpringPower();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	std::string getName();

	bool canHomingAttackOn();

	Vector3f getHomingCenter();
};
#endif