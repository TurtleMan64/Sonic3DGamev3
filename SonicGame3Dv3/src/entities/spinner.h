#ifndef SPINNER_H
#define SPINNER_H

class TexturedModel;
class Body;

#include <list>
#include "entities.h"


class Spinner : public Entity
{
private:
	static std::list<TexturedModel*> modelsBody;
	static std::list<TexturedModel*> modelsBlades;

	Body* blades;
	static float colHorizontal;
	static float colVertical;

public:
	Spinner();
	Spinner(float x, float y, float z);

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