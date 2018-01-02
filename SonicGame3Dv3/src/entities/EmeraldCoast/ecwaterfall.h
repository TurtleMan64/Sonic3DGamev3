#ifndef ECWATERFALL_H
#define ECWATERFALL_H

class TexturedModel;

#include <list>
#include "../entities.h"


class EC_Waterfall : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	EC_Waterfall();
	EC_Waterfall(float x, float y, float z, float rotY, float rotZ);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif