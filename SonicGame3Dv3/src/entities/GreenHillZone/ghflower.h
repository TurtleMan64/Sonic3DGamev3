#ifndef GHFLOWER_H
#define GHFLOWER_H

class TexturedModel;
class Body;

#include <list>
#include "../entities.h"


class GH_Flower : public Entity
{
private:
	static std::list<TexturedModel*> modelsTop;
	static std::list<TexturedModel*> modelsBase;

	Body* petals;

public:
	GH_Flower();
	GH_Flower(float x, float y, float z, float rotY, float scale);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif