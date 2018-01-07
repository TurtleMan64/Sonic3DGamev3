#ifndef ECPALMTREE_H
#define ECPALMTREE_H

class TexturedModel;

#include <list>
#include "../entities.h"


class EC_Palmtree : public Entity
{
private:
	static std::list<TexturedModel*> models;

public:
	EC_Palmtree();
	EC_Palmtree(float x, float y, float z, float rotX, float rotY, float rotZ, float scale);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif