#ifndef AUDIOMASTER_H
#define AUDIOMASTER_H

class Vector3f;

#include <AL/al.h>
#include <AL/alc.h>

class AudioMaster
{
private:
	static ALCdevice* device;
	static ALCcontext* context;

public:
	static void init();

	static void updateListenerData(Vector3f* pos, Vector3f* vel, float camYaw, float camPitch);

	static ALuint loadWAV(const char* fileName);

	static ALuint loadOGG(const char* fileName);
	
	static void cleanUp();
};
#endif