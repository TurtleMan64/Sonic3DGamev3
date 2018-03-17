#ifndef SHELEVATORPLATFORMPATH_H
#define SHELEVATORPLATFORMPATH_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class SH_ElevatorPlatformPath : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	SH_ElevatorPlatformPath();
	SH_ElevatorPlatformPath(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif
