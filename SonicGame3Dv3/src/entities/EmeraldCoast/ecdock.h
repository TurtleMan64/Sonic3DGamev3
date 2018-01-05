#ifndef ECDOCK_H
#define ECDOCK_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class EC_Dock : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	EC_Dock();
	EC_Dock(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif