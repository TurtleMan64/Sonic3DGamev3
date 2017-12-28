#ifndef STAGE_H
#define STAGE_H

class TexturedModel;

#include <list>
#include "entities.h"
#include <string>


class Stage : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	Stage();

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadModels(char* folder, char* name);

	static void deleteModels();
};
#endif