#ifndef KILLBOX_H
#define KILLBOX_H

#include <list>
#include "entities.h"


class KillBox : public Entity
{
private:
	float x2;
	float y2;
	float z2;

public:
	KillBox();
	KillBox(float x1, float y1, float z1,
		    float x2, float y2, float z2);

	void step();
};
#endif