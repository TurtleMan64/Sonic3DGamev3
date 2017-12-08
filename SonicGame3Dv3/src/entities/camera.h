#include <glad/glad.h>

#include "../models/models.h"
#include "../toolbox/vector.h"

#ifndef CAMERA_H
#define CAMERA_H
class Camera
{
private:
	Vector3f position;
	float pitch;
	float yaw;
	float roll;

public:
	Camera();

	void move();

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