#ifndef BPROJECTILE_H
#define BPROJECTILE_H

class TexturedModel;

#include <list>
#include "../entities.h"


class B_Projectile : public Entity
{
private:
	float xVel;
	float yVel;
	float zVel;
	bool tracking;
	int timer;
	float speed;

public:
	B_Projectile();
	B_Projectile(float x, float y, float z, float velX, float velY, float velZ);

	void step();

	std::list<TexturedModel*>* getModels();
};
#endif