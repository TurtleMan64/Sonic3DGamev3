#ifndef ECSEAGULL_H
#define ECSEAGULL_H

class TexturedModel;

#include <list>
#include "../entities.h"


class EC_Seagull : public Entity
{
private:
	static std::list<TexturedModel*> models;

	float centerX;
	float centerY;
	float centerZ;

	float prevX;
	float prevY;
	float prevZ;

	float flyAngle;
	float flyAngleDelta;

	float flyRadiusBase;
	float flyRadiusAmplitude;
	float flyRadiusDelta;
	float flyRadiusProgression;

	float flyHeightBase;
	float flyHeightAmplitude;
	float flyHeightDelta;
	float flyHeightProgression;

	int soundTimer;

public:
	EC_Seagull();
	EC_Seagull(
		float x, float y, float z,
		float startAngle,
		float flySpeed,
		float flyRadiusBase,
		float flyRadiusAmplitude,
		float flyRadiusChange,
		float flyHeightAmplitude,
		float flyHeightDelta);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif