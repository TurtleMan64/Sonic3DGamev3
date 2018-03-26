#ifndef ENTITIES_H
#define ENTITIES_H

class TexturedModel;

#include <list>
#include "../toolbox/vector.h"
#include "../toolbox/matrix.h"
#include <string>


class Entity
{
protected:
	Vector3f position;
	float rotX, rotY, rotZ, rotSpin;
	float scale;
	bool visible;
	Matrix4f transformationMatrix;

public:
	Entity();
	Entity(Vector3f*, float, float, float, float);

	virtual void step();

	virtual bool isPlayer();

	void increasePosition(float, float, float);

	void increaseRotation(float, float, float);

	virtual std::list<TexturedModel*>* getModels();

	Vector3f* getPosition();
	void setPosition(Vector3f*);
	void setPosition(float newX, float newY, float newZ);

	float getRotX();
	void setRotX(float);

	float getRotY();
	void setRotY(float);

	float getRotZ();
	void setRotZ(float);

	float getRotSpin();
	void setRotSpin(float);

	float getScale();
	void setScale(float);

	bool getVisible();
	void setVisible(bool);

	float getX();

	float getY();

	float getZ();

	void setX(float newX);

	void setY(float newY);

	void setZ(float newZ);

	Matrix4f* getTransformationMatrix();

	void updateTransformationMatrix();

	virtual std::string getName();

	virtual bool canLightdashOn();

	virtual bool canHomingAttackOn();
	
	virtual bool isPoint();

	virtual bool isSoundEmitter();
};
#endif