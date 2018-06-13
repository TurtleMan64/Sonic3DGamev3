#ifndef CAMERA_H
#define CAMERA_H

#include "../toolbox/vector.h"

class Camera
{
private:
	Vector3f position;
	Vector3f prevPos;
	float pitch;
	float yaw;
	float roll;
	Vector3f fadePosition1;
	Vector3f fadePosition2;

public:
	Camera();

	void refresh();

	Vector3f* getPosition();
	void setPosition(Vector3f*);

	float getPitch();
	void setPitch(float);

	float getYaw();
	void setYaw(float);

	float getRoll();
	void setRoll(float);

	void invertPitch();

	Vector3f calcVelocity();

	Vector3f* getFadePosition1();

	Vector3f* getFadePosition2();
};
#endif