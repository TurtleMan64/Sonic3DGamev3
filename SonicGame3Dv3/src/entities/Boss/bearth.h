#ifndef BEARTH_H
#define BEARTH_H

class TexturedModel;

#include <list>
#include "../entities.h"


class B_Earth : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	B_Earth();

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif