#ifndef LOWQUALITYWATER_H
#define LOWQUALITYWATER_H

class TexturedModel;

#include <list>
#include "entities.h"
#include <string>


class LowQualityWater : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	LowQualityWater();

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	std::string getName();
};
#endif