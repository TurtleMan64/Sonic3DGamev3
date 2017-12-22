#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "keyframe.h"


class Animation
{
public:
	std::vector<Keyframe> keyframes;

	Animation();

	void addKeyframe(float time, float x, float y, float z,
			float xRot, float yRot, float zRot, float scale);

	void addKeyframe(float time, float xRot, float yRot, float zRot, float scale);
};
#endif