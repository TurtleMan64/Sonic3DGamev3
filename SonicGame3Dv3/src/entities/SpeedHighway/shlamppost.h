#ifndef SHLAMPPPOST_H
#define SHLAMPPPOST_H

class TexturedModel;
class Body;

#include <list>
#include "../entities.h"


class SH_Lamppost : public Entity
{
private:
	static std::list<TexturedModel*> models;
	static std::list<TexturedModel*> modelsLight;

	Body* light;

public:
	SH_Lamppost(float x, float y, float z,
				float xRot, float yRot, float zRot);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif