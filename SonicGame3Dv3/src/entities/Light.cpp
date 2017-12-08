#include <glad/glad.h>

#include "../toolbox/vector.h"
#include "light.h"

Light::Light()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	colour.x = 1;
	colour.y = 1;
	colour.z = 1;
}

Vector3f* Light::getPosition()
{
	return &position;
}
void Light::setPosition(Vector3f* newPosition)
{
	colour.x = newPosition->x;
	colour.y = newPosition->y;
	colour.z = newPosition->z;
}

Vector3f* Light::getColour()
{
	return &colour;
}
void Light::setColour(Vector3f* newColour)
{
	colour.x = newColour->x;
	colour.y = newColour->y;
	colour.z = newColour->z;
}
