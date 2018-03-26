#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

class Source;

#include "entities.h"

class SoundEmitter : public Entity
{
private:
	int id;
	Source* soundEmitterSource;
	bool canPlay = false;
	
public:
	SoundEmitter();
	SoundEmitter(float x, float y, float z, int id);

	void step();

	void play(int sound);

	void stop();

	int getID();

	bool isSoundEmitter();
};
#endif