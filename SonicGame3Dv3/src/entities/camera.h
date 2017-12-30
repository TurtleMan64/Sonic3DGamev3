#ifndef CAMERA_H
#define CAMERA_H

#include "../toolbox/vector.h"

class Camera
{
private:
	Vector3f position;
	float pitch;
	float yaw;
	float roll;
	Vector3f fadePosition;

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
};
#endif