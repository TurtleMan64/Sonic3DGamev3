#ifndef SHLAMPPPOST_H
#define SHLAMPPPOST_H

class TexturedModel;

#include <list>
#include "../entities.h"


class SH_Lamppost : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	SH_Lamppost(float x, float y, float z,
				float xRot, float yRot, float zRot);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif