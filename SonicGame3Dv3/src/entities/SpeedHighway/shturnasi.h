#ifndef SHTURNASI_H
#define SHTURNASI_H

class TexturedModel;
class Body;

#include <list>
#include "../entities.h"


class SH_TurnAsi : public Entity
{
private:
	static std::list<TexturedModel*> modelsFork;
	static std::list<TexturedModel*> modelsBucket;

	Body* bucket;

	float storedSonicSpeed;

public:
	SH_TurnAsi();
	SH_TurnAsi(float x, float y, float z, float yRot);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif