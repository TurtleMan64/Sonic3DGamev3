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
int AudioPlayer::bgmTimer = 0;
ALuint AudioPlayer::bgmIntro;
ALuint AudioPlayer::bgmLoop;


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
	AudioPlayer::buffersSE.push_back(AudioMaster::loadWAV("res/Audio/General/Seagull.wav"));         //20
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

Source* AudioPlayer::playBGM(int bufferLoop)
{
	AudioPlayer::bgmTimer = 0;

	Source* src = AudioPlayer::sources[14];
	src->stop();
	src->setLooping(false);
	//alGetError();
	alSourcei(src->getSourceID(), AL_BUFFER, AL_NONE); Global::checkErrorAL("playBGM 154");

	src->setLooping(true);
	src->setVolume(AudioPlayer::soundLevelBGM);

	//fprintf(stdout, "size = %d\n", (int)AudioPlayer::buffersBGM.size());

	if (bufferLoop >= (int)AudioPlayer::buffersBGM.size() || bufferLoop < 0)
	{
		return src;
	}

	AudioPlayer::bgmIntro = AL_NONE;
	AudioPlayer::bgmLoop = AudioPlayer::buffersBGM[bufferLoop];

	src->play(AudioPlayer::bgmLoop);

	return src;
}

Source* AudioPlayer::playBGMWithIntro(int bufferIntro, int bufferLoop)
{
	AudioPlayer::bgmTimer = 3000; //Intro must be less than 50 seconds, Loop must be at least 50 seconds

	Source* src = AudioPlayer::sources[14];
	src->stop();
	src->setVolume(AudioPlayer::soundLevelBGM);
	src->setLooping(false);

	//alGetError();
	alSourcei(src->getSourceID(), AL_BUFFER, AL_NONE); Global::checkErrorAL("playBGMWithIntro 184"); //Get rid of queued buffers 

	if (bufferIntro >= (int)AudioPlayer::buffersBGM.size() ||
		bufferLoop  >= (int)AudioPlayer::buffersBGM.size() ||
		bufferIntro < 0 ||
		bufferLoop  < 0)
	{
		return src;
	}

	AudioPlayer::bgmIntro = AudioPlayer::buffersBGM[bufferIntro];
	AudioPlayer::bgmLoop  = AudioPlayer::buffersBGM[bufferLoop];

	//alGetError();
	alSourceQueueBuffers(src->getSourceID(), 1, &AudioPlayer::bgmIntro); Global::checkErrorAL("playBGMWithIntro 198");
	//alGetError();
	alSourceQueueBuffers(src->getSourceID(), 1, &AudioPlayer::bgmLoop);  Global::checkErrorAL("playBGMWithIntro 200");

	//alGetError();
	alSourcePlay(src->getSourceID()); Global::checkErrorAL("playBGMWithIntro 203");

	//if (!src->isPlaying() || src->getLastPlayedBufferID() != AudioPlayer::buffersBGM[buffer])
	{
		//src->setLooping(true);
		//src->setVolume(AudioPlayer::soundLevelBGM);
		//src->play(AudioPlayer::buffersBGM[buffer]);
	}

	return src;
}

//Gets rid of the intro buffer, so that just the loop buffer loops
void AudioPlayer::refreshBGM()
{
	if (AudioPlayer::bgmTimer > 0)
	{
		AudioPlayer::bgmTimer--;

		Source* src = AudioPlayer::sources[14];

		if (AudioPlayer::bgmTimer == 0 && AudioPlayer::bgmIntro != AL_NONE)
		{
			//alGetError();
			alSourceUnqueueBuffers(src->getSourceID(), 1, &AudioPlayer::bgmIntro); Global::checkErrorAL("refreshBGM 227");
			AudioPlayer::bgmIntro = AL_NONE;
			src->setLooping(true);
		}

		ALint num;
		//alGetError();
		alGetSourceiv(src->getSourceID(), AL_BUFFERS_QUEUED, &num); Global::checkErrorAL("refreshBGM 234");

		//fprintf(stdout, "%d\n", num);
	}
}

void AudioPlayer::stopBGM()
{
	AudioPlayer::bgmTimer = 0;
	Source* src = AudioPlayer::sources[14];
	src->stop();
	src->setLooping(false);

	//alGetError();
	alSourcei(src->getSourceID(), AL_BUFFER, AL_NONE); Global::checkErrorAL("stopBGM 248"); //Get rid of queued buffers 

	AudioPlayer::bgmIntro = AL_NONE;
	AudioPlayer::bgmLoop = AL_NONE;
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
				if (strcmp(lineSplit[0], "SFX_Volume") == 0)
				{
					AudioPlayer::soundLevelSE = std::stof(lineSplit[1], nullptr);
					AudioPlayer::soundLevelSE = fmaxf(0.0f, fminf(AudioPlayer::soundLevelSE, 1.0f));
				}
				else if (strcmp(lineSplit[0], "Music_Volume") == 0)
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