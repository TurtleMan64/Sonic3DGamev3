#ifndef SHDSTAGETRANSPARENT_H
#define SHDSTAGETRANSPARENT_H

class TexturedModel;

#include <list>
#include "../entities.h"


class SHD_StageTransparent : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	SHD_StageTransparent();

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif