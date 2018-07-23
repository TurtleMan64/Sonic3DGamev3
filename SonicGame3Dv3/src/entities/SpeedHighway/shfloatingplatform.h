#ifndef SHFLOATINGPLATFORM_H
#define SHFLOATINGPLATFORM_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class SH_FloatingPlatform : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	SH_FloatingPlatform();
	SH_FloatingPlatform(float x, float y, float z, float rotY, float scale);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif