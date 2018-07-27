#ifndef BMANAGER_H
#define BMANAGER_H

class TexturedModel;
class B_Earth;
class B_MetalSonic;

#include <list>
#include "../entities.h"

class B_Manager : public Entity
{
private:
	int timer = 0;
	int platformCount = 0;
	B_Earth* theEarth = nullptr;
	B_MetalSonic* theBoss = nullptr;

public:
	B_Manager();

	void step();

	std::list<TexturedModel*>* getModels();
};
#endif