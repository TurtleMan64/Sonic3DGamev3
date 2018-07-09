#ifndef MOTOBUG_H
#define MOTOBUG_H

class TexturedModel;
class Triangle3D;

#include <list>
#include "entities.h"


class MotoBug : public Entity
{
private:
	static std::list<TexturedModel*> models;

	Triangle3D* triCol;
	float xVel;
	float yVel;
	float zVel;
	int furyTimer;
	int furyTimerMax;
	bool inAir;
	int clock;
	float animIndex;

	static float colHorizontal;
	static float colVertical;

	void applyFriction(float frictionToApply);

	void moveMeSlow();

	void moveMe();

public:
	MotoBug();
	MotoBug(float x, float y, float z);

	void step();

	void die();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	bool canHomingAttackOn();

	Vector3f getHomingCenter();

	bool isEnemy();
};
#endif