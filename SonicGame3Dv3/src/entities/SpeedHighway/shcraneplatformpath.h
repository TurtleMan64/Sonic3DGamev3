#ifndef SHCRANEPLATFORMPATH_H
#define SHCRANEPLATFORMPATH_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class SH_CranePlatformPath : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

public:
	SH_CranePlatformPath();
	SH_CranePlatformPath(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif
