#ifndef TPFLATWATER_H
#define TPFLATWATER_H

class TexturedModel;

#include <list>
#include "../entities.h"
#include "../../toolbox/vector.h"


class TP_FlatWater : public Entity
{
private:
	static std::list<TexturedModel*> models;
	static Vector2f v1;
	static Vector2f v2;
	static Vector2f v3;
	static Vector2f v4;
	static Vector2f v5;
	static Vector2f v6;

	static Vector2f b1;
	static Vector2f b2;
	static Vector2f b3;
	static Vector2f b4;
	static Vector2f b5;
	static Vector2f b6;

public:
	TP_FlatWater();

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	std::string getName();
};
#endif