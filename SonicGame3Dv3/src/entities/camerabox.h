#ifndef CAMERABOX_H
#define CAMERABOX_H

#include <list>
#include "entities.h"

class TexturedModel;

class CameraBox : public Entity
{
private:
	static std::list<TexturedModel*> models;

	float p1X;
	float p1Y;
	float p1Z;
	float p2X;
	float p2Y;
	float p2Z;

	float panSpeed;

	int flags;

	float camTargetYaw;
	float camTargetPitch;

	float scaleX;
	float scaleY;
	float scaleZ;

	float sinT;
	float cosT;

public:
	CameraBox();
	CameraBox(
		float rotationY, float panSpeed,
		float x, float y, float z,
		float scaleX, float scaleY, float scaleZ,
		float p1X, float p1Y, float p1Z,
		float p2X, float p2Y, float p2Z,
		int flags);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif