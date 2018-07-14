#ifndef GOALSIGN_H
#define GOALSIGN_H

class TexturedModel;

#include <list>
#include "entities.h"


class GoalSign : public Entity
{
private:
	static std::list<TexturedModel*> models;

	static int triggersRemaining;
	static int lapsRemaining;

	static float hitboxR;
	static float hitboxV;

	float rotateSpeed;

public:
	GoalSign();
	GoalSign(float x, float y, float z, int lapCount);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	static void addTrigger();

	static void removeTrigger();
};
#endif