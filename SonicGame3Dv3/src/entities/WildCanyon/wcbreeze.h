#ifndef WCBREEZE_H
#define WCBREEZE_H

class TexturedModel;

#include "../entities.h"
#include <list>


class WC_Breeze : public Entity
{
private:
	float radiusSquared;
	float height;

public:
	WC_Breeze(float x, float y, float z,
			  float radius, float height);

	void step();

	std::list<TexturedModel*>* getModels();
};
#endif