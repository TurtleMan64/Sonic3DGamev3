#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

class Source;

#include "entities.h"

class SoundEmitter : public Entity
{
private:
	int bufferToPlay;
	Source* currentSource;

public:
	SoundEmitter();
	SoundEmitter(float x, float y, float z, int buffer);

	void step();
};
#endif