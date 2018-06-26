#ifndef GHSUNFLOWER_H
#define GHSUNFLOWER_H

class TexturedModel;
class Body;

#include <list>
#include "../entities.h"


class GH_Sunflower : public Entity
{
private:
	static std::list<TexturedModel*> modelsTop;
	static std::list<TexturedModel*> modelsTop2;
	static std::list<TexturedModel*> modelsBase;

	Body* petals;

public:
	GH_Sunflower();
	GH_Sunflower(float x, float y, float z, float rotY, float scale);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif