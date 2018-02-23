#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <AL/al.h>
#include <vector>

class Source;
class Vector3f;

class AudioPlayer
{
private:
	static float soundLevel;
	static float soundLevelBG;
	static std::vector<Source*> sources;
	static std::vector<ALuint> buffersSE;
	static std::vector<ALuint> buffersBGM;

public:
	static void loadSoundEffects();

	static void loadBGM(char* fileName);

	static void deleteSources();

	static void deleteBuffersSE();

	static void deleteBuffersBGM();

	static void createSources();

	//with position
	static Source* play(int buffer, Vector3f* pos);

	//with position and pitch
	static Source* play(int buffer, Vector3f* pos, float pitch);

	//with position and pitch and loop
	static Source* play(int buffer, Vector3f* pos, float pitch, bool loop);

	//with everything
	static Source* play(int buffer, Vector3f* pos, float pitch, bool loop, float xVel, float yVel, float zVel);

	static Source* playBGM(int buffer);

	static Source* getSource(int i);
};
#endif