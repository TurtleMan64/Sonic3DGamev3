#ifndef ECCHAIR_H
#define ECCHAIR_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class EC_Chair : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	EC_Chair();
	EC_Chair(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif