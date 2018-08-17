#ifndef MHPATHDIAGONAL_H
#define MHPATHDIAGONAL_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class MH_PathDiagonal : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	MH_PathDiagonal();
	MH_PathDiagonal(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif
