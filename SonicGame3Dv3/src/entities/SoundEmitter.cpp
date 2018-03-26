#include "soundemitter.h"
#include "../toolbox/vector.h"
#include "../audio/audioplayer.h"
#include "../audio/source.h"

SoundEmitter::SoundEmitter()
{
	this->id = -1;
}

SoundEmitter::SoundEmitter(float x, float y, float z, int id)
{
	position.x = x;
	position.y = y;
	position.z = z;
	this->id = id;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = false;
}

void SoundEmitter::step()
{
	canPlay = false;
	if (soundEmitterSource != nullptr && !soundEmitterSource->isPlaying())
	{
		canPlay = true;
	}
}

void SoundEmitter::play(int sound)
{
	Source* source = nullptr;
	if (canPlay)
	{
		soundEmitterSource = AudioPlayer::play(sound, getPosition());
	}
}

void SoundEmitter::stop()
{
	if (soundEmitterSource != nullptr)
	{
		if (soundEmitterSource->isPlaying())
		{
			soundEmitterSource->stop();
		}
	}
}

int SoundEmitter::getID()
{
	return id;
}

bool SoundEmitter::isSoundEmitter()
{
	return true;
}