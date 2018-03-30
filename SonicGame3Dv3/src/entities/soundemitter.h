<<<<<<< HEAD
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
=======
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
>>>>>>> upstream/master
#endif