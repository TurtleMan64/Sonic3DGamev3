#include <AL/al.h>

#include "source.h"
#include "../engineTester/main.h"

Source::Source(float rolloff, float referencedist, float max)
{
	alGenSources(1, &sourceID);
	alSourcef(sourceID, AL_ROLLOFF_FACTOR, rolloff);
	alSourcef(sourceID, AL_REFERENCE_DISTANCE, referencedist);
	alSourcef(sourceID, AL_MAX_DISTANCE, max);

	//Background music shouldn't pan in 3D space
	if (rolloff == 0)
	{
		alSourcei(sourceID, AL_SOURCE_RELATIVE, AL_TRUE);
	}

	bufferID = (ALuint)-1;
}

void Source::play(ALuint buffer)
{
	stop();
	//alGetError();
	alSourcei(sourceID, AL_BUFFER, buffer); Global::checkErrorAL("source play");
	bufferID = buffer;
	continuePlaying();
}

void Source::deleteMe()
{
	stop();
	alDeleteSources(1, &sourceID);
}

void Source::pause()
{
	alSourcePause(sourceID);
}

void Source::continuePlaying()
{
	//alGetError();
	alSourcePlay(sourceID); Global::checkErrorAL("source continue playing");
}

void Source::stop()
{
	//if (this->isPlaying())
	{
		//This generates an AL_INVALID_OPERATION sometimes and I have no idea why.
		//Supposedly can only generate this error due to "There is no current context."
		//alGetError();
		alSourceStop(sourceID); Global::checkErrorAL("source stop");
	}
}

void Source::setVelocity(float x, float y, float z)
{
	ALfloat sourceVel[] = { x, y, z };
	alSourcefv(sourceID, AL_VELOCITY, sourceVel);
}

void Source::setLooping(bool loop)
{
	//alGetError();
	alSourcei(sourceID, AL_LOOPING, loop ? AL_TRUE : AL_FALSE); Global::checkErrorAL("source setLooping");
}

bool Source::isPlaying()
{
	ALint value;
	alGetSourcei(sourceID, AL_SOURCE_STATE, &value);
	return value == AL_PLAYING;
}

void Source::setVolume(float volume)
{
	alSourcef(sourceID, AL_GAIN, volume);
}

void Source::setPitch(float pitch)
{
	alSourcef(sourceID, AL_PITCH, pitch);
}

void Source::setPosition(float x, float y, float z)
{
	ALfloat sourcePos[] = { x, y, z };
	alSourcefv(sourceID, AL_POSITION, sourcePos);
}

ALuint Source::getSourceID()
{
	return sourceID;
}

ALuint Source::getLastPlayedBufferID()
{
	return bufferID;
}
