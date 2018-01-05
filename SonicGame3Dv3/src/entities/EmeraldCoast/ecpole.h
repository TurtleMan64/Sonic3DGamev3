#ifndef ECPOLE_H
#define ECPOLE_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class EC_Pole : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	EC_Pole();
	EC_Pole(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif