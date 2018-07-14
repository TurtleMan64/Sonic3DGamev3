#ifndef GOALTRIGGER_H
#define GOALTRIGGER_H

class TexturedModel;

#include <list>
#include "entities.h"


class GoalTrigger : public Entity
{
private:
	static std::list<TexturedModel*> models;
    
	float hitboxH;
	float hitboxV;

	int activeTimer;

public:
	bool isActive;

	GoalTrigger();
	GoalTrigger(float x, float y, float z, float scale);

	void step();

	bool isGoalTrigger();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif