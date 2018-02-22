#ifndef TPFLOATINGPAD_H
#define TPFLOATINGPAD_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class TP_FloatingPad : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;
	float origHeight;

public:
	TP_FloatingPad();
	TP_FloatingPad(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif