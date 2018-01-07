#ifndef ECUMBRELLA_H
#define ECUMBRELLA_H

class TexturedModel;

#include <list>
#include "../entities.h"


class EC_Umbrella : public Entity
{
private:
	static std::list<TexturedModel*> models1;
	static std::list<TexturedModel*> models2;

	int type;

public:
	EC_Umbrella();
	EC_Umbrella(float x, float y, float z, float rotX, float rotY, float rotZ, float type);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif