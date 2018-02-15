#include <AL/al.h>
#include <vector>

#include "audioplayer.h"
#include "audiomaster.h"
#include "source.h"
#include "../engineTester/main.h"
#include "../toolbox/vector.h"



float AudioPlayer::soundLevel = 0.1f;
float AudioPlayer::soundLevelBG = 0.1f;
std::vector<Source*> AudioPlayer::sources;
std::vector<ALuint> AudioPlayer::buffers;


void AudioPlayer::loadSoundEffects()
{
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/General/BigDestroy.wav"));      //0
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/General/Dashpad.wav"));         //1
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/General/Goal.wav"));            //2
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/General/ItemCapsule.wav"));     //3
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/General/Ring.wav"));            //4
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/General/Splash.wav"));          //5
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/General/Spring.wav"));          //6
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/General/UnlockSomething.wav")); //7
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/Sonic/Bounce.wav"));            //8
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/Sonic/Death.wav"));             //9
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/Sonic/GetHit.wav"));            //10
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/Sonic/HomingAttack.wav"));      //11
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/Sonic/Jump.wav"));              //12
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/Sonic/Skid.wav"));              //13
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/Sonic/SpindashCharge.wav"));    //14
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/Sonic/SpindashRelease.wav"));   //15
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/Sonic/StompInit.wav"));         //16
	AudioPlayer::buffers.push_back(AudioMaster::loadWAV("res/Audio/Sonic/StompLand.wav"));         //17
}

void AudioPlayer::deleteSources()
{
	for (Source* src : AudioPlayer::sources)
	{
		src->deleteMe();
		delete src;
		Global::countDelete++;
	}
}

void AudioPlayer::deleteBuffers()
{
	for (ALuint buff : AudioPlayer::buffers)
	{
		alDeleteBuffers(1, &buff);
	}
}

void AudioPlayer::createSources()
{
	//First 14 sources are for sound effects
	sources.push_back(new Source(1, 100, 600)); Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	sources.push_back(new Source(1, 100, 600));	Global::countNew++;
	//Last source is dedicated to background music
	sources.push_back(new Source(1, 0, 0));     Global::countNew++;
}

//with position
Source* AudioPlayer::play(int buffer, Vector3f* pos)
{
	return AudioPlayer::play(buffer, pos, 1.0f, false, 0, 0, 0);
}

//with position and pitch
Source* AudioPlayer::play(int buffer, Vector3f* pos, float pitch)
{
	return AudioPlayer::play(buffer, pos, pitch, false, 0, 0, 0);
}

//with position and pitch and loop
Source* AudioPlayer::play(int buffer, Vector3f* pos, float pitch, bool loop)
{
	return AudioPlayer::play(buffer, pos, pitch, loop, 0, 0, 0);
}

//with everything
Source* AudioPlayer::play(int buffer, Vector3f* pos, float pitch, bool loop, float xVel, float yVel, float zVel)
{
	for (int i = 0; i < 14; i++)
	{
		Source* src = AudioPlayer::sources[i];
		if (!src->isPlaying())
		{
			src->setVolume(soundLevel);
			src->setLooping(loop);
			src->setPosition(pos->x, pos->y, pos->z);
			src->setPitch(pitch);
			src->setVelocity(xVel, yVel, zVel);
			src->play(AudioPlayer::buffers[buffer]);
			return src;
		}
	}

	//no sources to play music
	return nullptr;
}

Source* AudioPlayer::playBGM(int buffer)
{
	Source* src = AudioPlayer::sources[14];

	if (!src->isPlaying() || src->getLastPlayedBufferID() != AudioPlayer::buffers[buffer])
	{
		src->setLooping(true);
		src->setVolume(AudioPlayer::soundLevelBG);
		src->play(AudioPlayer::buffers[buffer]);
	}

	return src;
}

Source* AudioPlayer::getSource(int i)
{
	return AudioPlayer::sources[i];
}
