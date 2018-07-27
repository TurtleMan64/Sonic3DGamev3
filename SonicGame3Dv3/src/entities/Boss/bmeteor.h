#ifndef BMETEOR_H
#define BMETEOR_H

class TexturedModel;

#include <list>
#include "../entities.h"


class B_Meteor : public Entity
{
private:
	static std::list<TexturedModel*> models;
	float xVel;
	float yVel;
	float zVel;
	int timer;

public:
	B_Meteor();
	B_Meteor(float x, float y, float z, float velX, float velY, float velZ);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif