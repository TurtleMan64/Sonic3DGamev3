#ifndef MHGIANTROCKET_H
#define MHGIANTROCKET_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class MH_GiantRocket : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	MH_GiantRocket();
	MH_GiantRocket(float x, float y, float z);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif
