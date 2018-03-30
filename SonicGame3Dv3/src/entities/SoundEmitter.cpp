<<<<<<< HEAD
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
=======
#include "soundemitter.h"
#include "camera.h"
#include "../engineTester/main.h"
#include "../toolbox/vector.h"
#include "../audio/source.h"
#include "../audio/audioplayer.h"

SoundEmitter::SoundEmitter()
{

}

SoundEmitter::SoundEmitter(float x, float y, float z, int buffer)
{
	position.x = x;
	position.y = y;
	position.z = z;
	bufferToPlay = buffer;

	currentSource = nullptr;

	visible = false;
}

void SoundEmitter::step()
{
	Vector3f* camPos = Global::gameCamera->getPosition();
	float xDiff = camPos->x - getX();
	float yDiff = camPos->y - getY();
	float zDiff = camPos->z - getZ();

	if (xDiff*xDiff + yDiff*yDiff + zDiff*zDiff < 500 * 500)
	{
		if (currentSource == nullptr)
		{
			currentSource = AudioPlayer::play(bufferToPlay, getPosition(), 1, true);
		}

		if (currentSource != nullptr)
		{
			currentSource->setPosition(getX(), getY(), getZ());
		}
	}
	else
	{
		if (currentSource != nullptr)
		{
			currentSource->stop();
			currentSource = nullptr;
		}
	}
}

>>>>>>> upstream/master
