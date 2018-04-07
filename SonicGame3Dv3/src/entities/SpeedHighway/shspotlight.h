#ifndef SHSPOTLIGHT_H
#define SHSPOTLIGHT_H

class TexturedModel;
class Body;

#include <list>
#include "../entities.h"


class SH_Spotlight : public Entity
{
private:
	static std::list<TexturedModel*> models;
	static std::list<TexturedModel*> modelsLight;

	Body* light;

	float initRotZ;
	int timer;

public:
	SH_Spotlight(float x, float y, float z,
				float xRot, float yRot, float zRot);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif