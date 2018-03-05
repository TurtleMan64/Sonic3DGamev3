#ifndef ECBIGROCK_H
#define ECBIGROCK_H

class TexturedModel;

#include <list>
#include "../entities.h"


class EC_BigRock : public Entity
{
private:
	static std::list<TexturedModel*> modelsA;
	static std::list<TexturedModel*> modelsB;
	int kind;
	float baseYrot;

public:
	EC_BigRock();
	EC_BigRock(float x, float y, float z, float rotX, float rotY, float rotZ, float scale, int kind);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif