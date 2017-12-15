#ifndef LIGHT_H
#define LIGHT_H

#include "../toolbox/vector.h"


class Light
{
private:
	Vector3f position;
	Vector3f colour;

public:
	Light();

	Vector3f* getPosition();
	void setPosition(Vector3f*);

	Vector3f* getColour();
	void setColour(Vector3f*);
};
#endif