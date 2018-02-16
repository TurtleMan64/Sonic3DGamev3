#ifndef ECDOLPHIN_H
#define ECDOLPHIN_H

class TexturedModel;

#include <list>
#include "../entities.h"


class EC_Dolphin : public Entity
{
private:
	static std::list<TexturedModel*> models;

	float triggerX;
	float triggerY;
	float triggerZ;

	float triggerRadius;

	int triggerTimer;

	float yVel;
	float hSpd;

	bool inWaterPrevious;

public:
	EC_Dolphin();
	EC_Dolphin(float x, float y, float z,
		float rotY,
		float triggerX, float triggerY, float triggerZ,
		float triggerRadius);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif