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

public:
	GoalTrigger();
	GoalTrigger(float x, float y, float z, float scale);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif