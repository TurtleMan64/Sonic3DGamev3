#ifndef SHIELDGREEN_H
#define SHIELDGREEN_H

class TexturedModel;

#include <list>
#include "entities.h"

class ShieldGreen : public Entity
{
public:
	ShieldGreen();

	void step();

	std::list<TexturedModel*>* getModels();
};
#endif