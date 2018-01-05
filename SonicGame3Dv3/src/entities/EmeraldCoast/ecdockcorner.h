#ifndef ECDOCKCORNER_H
#define ECDOCKCORNER_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class EC_DockCorner : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	EC_DockCorner();
	EC_DockCorner(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif