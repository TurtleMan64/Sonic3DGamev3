#ifndef POINT_H
#define POINT_H

#include <list>
#include "entities.h"

class Point : public Entity
{
protected:
	int id;
public:
	Point();
	Point(float x, float y, float z, int id);

	int getid();

	bool isPoint();
};
#endif