#ifndef CHAO_H
#define CHAO_H

class TexturedModel;

#include <list>
#include "entities.h"

class Chao : public Entity
{
private:
	static std::list<TexturedModel*> models;

	static float hitboxR;
	static float hitboxV;
	
	bool isFound;

public:
	Chao();
	Chao(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif