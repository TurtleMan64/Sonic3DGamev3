#ifndef ECSTAGETRANSPARENT_H
#define ECSTAGETRANSPARENT_H

class TexturedModel;

#include <list>
#include "../entities.h"


class EC_StageTransparent : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	EC_StageTransparent();

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif