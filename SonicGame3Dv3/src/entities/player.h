#include <glad/glad.h>

#include "../models/models.h"
#include "../toolbox/vector.h"
#include "entities.h"

#include <list>

#ifndef PLAYER_H
#define PLAYER_H
class Player : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	Player();
	Player(float, float, float);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif