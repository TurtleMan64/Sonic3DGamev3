#ifndef ENTITIES_H
#define ENTITIES_H

class TexturedModel;

#include <list>
#include "../toolbox/vector.h"


class Entity
{
protected:
	Vector3f position;
	float rotX, rotY, rotZ;
	float scale;
	int visible;

public:
	Entity();
	Entity(Vector3f*, float, float, float, float);

	virtual void step();

	void increasePosition(float, float, float);

	void increaseRotation(float, float, float);

	virtual std::list<TexturedModel*>* getModels();

	Vector3f* getPosition();
	void setPosition(Vector3f*);

	float getRotX();
	void setRotX(float);

	float getRotY();
	void setRotY(float);

	float getRotZ();
	void setRotZ(float);

	float getScale();
	void setScale(float);

	int getVisible();
	void setVisible(int);
};
#endif