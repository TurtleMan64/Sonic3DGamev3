#include <AL/al.h>
#include <vector>
#include <fstream>

#include "audioplayer.h"
#include "audiomaster.h"
#include "source.h"
#include "../engineTester/main.h"
#include "../toolbox/vector.h"
#include "../toolbox/split.h"



float AudioPlayer::soundLevelSE = 0.5f;
float AudioPlayer::soundLevelBGM = 0.4f;
std::vector<Source*> AudioPlayer::sources;
std::vector<ALuint> AudioPlayer::buffersSE;
std::vector<ALuint> AudioPlayer::buffersBGM;


void AudioPlayer::loadSoundEffects()
{
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/General/BigDestroy.wav"));      //0
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/General/Dashpad.wav"));         //1
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/General/Goal.wav"));            //2
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/General/ItemCapsule.wav"));     //3
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/General/Ring.wav"));            //4
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/General/Splash.wav"));          //5
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/General/Spring.wav"));          //6
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/General/UnlockSomething.wav")); //7
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/Bounce.wav"));            //8
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/Death.wav"));             //9
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/GetHit.wav"));            //10
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/HomingAttack.wav"));      //11
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/Jump.wav"));              //12
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/Skid.wav"));              //13
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/SpindashCharge.wav"));    //14
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/SpindashRelease.wav"));   //15
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/StompInit.wav"));         //16
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/StompLand.wav"));         //17
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/Sonic/CantStick.wav"));         //18
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/General/DockBreak.wav"));       //19
}

void AudioPlayer::loadBGM(char* fileName)
{
	AudioPlayer::buffersBGM.push_back(AudioMaster::loadWAV(fileName));
}

void AudioPlayer::deleteSources()
{
	for (Source* src : AudioPlayer::sources)
	{
		src->deleteMe();
		delete src;
		Global::countDelete++;
	}
	AudioPlayer::sources.clear();
}

void AudioPlayer::deleteBuffersSE()
{
	for (ALuint buff : AudioPlayer::buffersSE)
	{
		alDeleteBuffers(1, &buff);
	}
	AudioPlayer::buffersSE.clear();
}

void AudioPlayer::deleteBuffersBGM()
{
	Source* src = AudioPlayer::sources[14];
	src->stop();

	for (ALuint buff : AudioPlayer::buffersBGM)
	{
		alDeleteBuffers(1, &buff);
	}
	AudioPlayer::buffersBGM.clear();
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
	sources.push_back(new Source(0, 0, 0));     Global::countNew++;
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
			src->setVolume(soundLevelSE);
			src->setLooping(loop);
			src->setPosition(pos->x, pos->y, pos->z);
			src->setPitch(pitch);
			src->setVelocity(xVel, yVel, zVel);
			src->play(AudioPlayer::buffersSE[buffer]);
			return src;
		}
	}

	//no sources to play music
	return nullptr;
}

Source* AudioPlayer::playBGM(int buffer)
{
	Source* src = AudioPlayer::sources[14];

	if (buffer >= (int)AudioPlayer::buffersBGM.size())
	{
		return src;
	}

	if (!src->isPlaying() || src->getLastPlayedBufferID() != AudioPlayer::buffersBGM[buffer])
	{
		src->setLooping(true);
		src->setVolume(AudioPlayer::soundLevelBGM);
		src->play(AudioPlayer::buffersBGM[buffer]);
	}

	return src;
}

Source* AudioPlayer::getSource(int i)
{
	return AudioPlayer::sources[i];
}

void AudioPlayer::loadSettings()
{
	std::ifstream file("Settings/AudioSettings.ini");
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file 'Settings/AudioSettings.ini'\n");
		file.close();
	}
	else
	{
		std::string line;

		while (!file.eof())
		{
			getline(file, line);

			char lineBuf[512]; //Buffer to copy line into
			memset(lineBuf, 0, 512);
			memcpy(lineBuf, line.c_str(), line.size());

			int splitLength = 0;
			char** lineSplit = split(lineBuf, ' ', &splitLength);

			if (splitLength == 2)
			{
				if (strcmp(lineSplit[0], "SFX_Volume ") == 0)
				{
					AudioPlayer::soundLevelSE = std::stof(lineSplit[1], nullptr);
					AudioPlayer::soundLevelSE = fmaxf(0.0f, fminf(AudioPlayer::soundLevelSE, 1.0f));
				}
				else if (strcmp(lineSplit[0], "Music_Volume ") == 0)
				{
					AudioPlayer::soundLevelBGM = std::stof(lineSplit[1], nullptr);
					AudioPlayer::soundLevelBGM = fmaxf(0.0f, fminf(AudioPlayer::soundLevelBGM, 1.0f));
				}
			}

			free(lineSplit);
		}
		file.close();
	}
}