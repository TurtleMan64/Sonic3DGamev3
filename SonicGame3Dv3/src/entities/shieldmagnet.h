#ifndef SHIELDMAGNET_H
#define SHIELDMAGNET_H

class TexturedModel;

#include <list>
#include "entities.h"

class ShieldMagnet : public Entity
{
public:
	ShieldMagnet();

	void step();

	std::list<TexturedModel*>* getModels();
};
#endif