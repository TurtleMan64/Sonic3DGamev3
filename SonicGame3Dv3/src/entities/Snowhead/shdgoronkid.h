#ifndef SHDGORONKID_H
#define SHDGORONKID_H

class TexturedModel;
class Source;

#include <list>
#include "../entities.h"


class SHD_GoronKid : public Entity
{
private:
	static std::list<TexturedModel*> models;

	int cryTimer;
	Source* crySource;

public:
	static bool found;

	SHD_GoronKid();
	SHD_GoronKid(float x, float y, float z);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif