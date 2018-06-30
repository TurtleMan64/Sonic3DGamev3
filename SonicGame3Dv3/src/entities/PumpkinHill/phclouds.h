#ifndef PHCLOUDS_H
#define PHCLOUDS_H

class TexturedModel;

#include <list>
#include "../entities.h"

class PH_Clouds : public Entity
{
private:
	static std::list<TexturedModel*> models;

	float spinSpeed;

public:
	PH_Clouds(float y, float spinSpeed);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif