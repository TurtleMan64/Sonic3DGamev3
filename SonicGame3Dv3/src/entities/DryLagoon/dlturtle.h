#ifndef DLTURTLE_H
#define DLTURTLE_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../collideableobject.h"


class DL_Turtle : public CollideableObject
{
private:
	static std::list<TexturedModel*> models;
	static CollisionModel* cmOriginal;

	//target values
	float xt;
	float yt;
	float zt;
	float camYt;

	int warpTimer;
	const int warpTimerMax = 60;

public:
	DL_Turtle();
	DL_Turtle(float x, float y, float z, float rotY, 
			  float xt, float yt, float zt, float camYt);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif