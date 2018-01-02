#ifndef ECFLATWATER_H
#define ECFLATWATER_H

class TexturedModel;

#include <list>
#include "../entities.h"


class EC_FlatWater : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	EC_FlatWater();

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	std::string getName();
};
#endif