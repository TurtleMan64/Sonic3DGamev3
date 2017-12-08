#include <glad/glad.h>

#include "../models/models.h"
#include "../toolbox/vector.h"

#ifndef ENTITIES_H
#define ENTITIES_H
class Entity
{
private:
	TexturedModel model;
	Vector3f position;
	float rotX, rotY, rotZ;
	float scale;

public:
	Entity();
	Entity(TexturedModel*, Vector3f*, float, float, float, float);

	void increasePosition(float, float, float);

	void increaseRotation(float, float, float);

	TexturedModel* getModel();
	void setModel(TexturedModel*);

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
};
#endif