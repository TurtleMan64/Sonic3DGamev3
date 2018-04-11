#include "killbox.h"
#include "playersonic.h"
#include "../engineTester/main.h"

#include <algorithm>


KillBox::KillBox()
{

}

KillBox::KillBox(float x1, float y1, float z1,
	             float x2, float y2, float z2)
{
	position.x = std::min(x1, x2);
	position.y = std::min(y1, y2);
	position.z = std::min(z1, z2);

	this->x2   = std::max(x1, x2);
	this->y2   = std::max(y1, y2);
	this->z2   = std::max(z1, z2);

	scale = 1;
	visible = false;
}

void KillBox::step()
{
	if (Global::gamePlayer->getX() > getX() && Global::gamePlayer->getX() < x2 &&
		Global::gamePlayer->getZ() > getZ() && Global::gamePlayer->getZ() < z2 &&
		Global::gamePlayer->getY() > getY() && Global::gamePlayer->getY() < y2)
	{
		Global::gamePlayer->die();
	}
}
