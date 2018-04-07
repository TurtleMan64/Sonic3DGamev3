#ifndef SHCONE_H
#define SHCONE_H

class TexturedModel;

#include <list>
#include "../entities.h"


class SH_Cone : public Entity
{
private:
	static std::list<TexturedModel*> modelsA;
	static std::list<TexturedModel*> modelsB;

	int coneKind;

public:
	SH_Cone(float x, float y, float z,
	float xRot, float yRot, float zRot, int kind);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif