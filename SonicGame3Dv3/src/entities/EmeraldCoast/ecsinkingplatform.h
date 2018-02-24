#ifndef ECSINKINGPLATFORM_H
#define ECSINKINGPLATFORM_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class EC_SinkingPlatform : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;
	float surfaceHeight;

public:
	EC_SinkingPlatform();
	EC_SinkingPlatform(float x, float y, float z);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif