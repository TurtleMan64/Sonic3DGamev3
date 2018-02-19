#ifndef ECSHARK_H
#define ECSHARK_H

class TexturedModel;

#include <list>
#include "../entities.h"


class EC_Shark : public Entity
{
private:
	static std::list<TexturedModel*> models;

	float initX;
	float initY;
	float initZ;

	float xVel;
	float yVel;
	float zVel;

	int seeTimer;

	bool inWaterPrevious;

public:
	EC_Shark();
	EC_Shark(float x, float y, float z);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif