#ifndef SHSTAGETRANSPARENT_H
#define SHSTAGETRANSPARENT_H

class TexturedModel;

#include <list>
#include "../entities.h"


class SH_StageTransparent : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	SH_StageTransparent();

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif