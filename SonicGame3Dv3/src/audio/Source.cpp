#include <AL/al.h>

#include "source.h"

Source::Source(float rolloff, float referencedist, float max)
{
	alGenSources(1, &sourceID);
	alSourcef(sourceID, AL_ROLLOFF_FACTOR, rolloff);
	alSourcef(sourceID, AL_REFERENCE_DISTANCE, referencedist);
	alSourcef(sourceID, AL_MAX_DISTANCE, max);

	bufferID = (ALuint)-1;
}

void Source::play(ALuint buffer)
{
	stop();
	alSourcei(sourceID, AL_BUFFER, buffer);
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
	alSourcePlay(sourceID);
}

void Source::stop()
{
	alSourceStop(sourceID);
}

void Source::setVelocity(float x, float y, float z)
{
	//alSource3f(sourceID, AL_VELOCITY, x, y, z);

	ALfloat sourceVel[] = { x, y, z };
	alSourcefv(sourceID, AL_VELOCITY, sourceVel);
}

void Source::setLooping(bool loop)
{
	alSourcei(sourceID, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
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

	//alSource3f(sourceID, AL_POSITION, x, y, z);
}

ALuint Source::getSourceID()
{
	return sourceID;
}

ALuint Source::getLastPlayedBufferID()
{
	return bufferID;
}
