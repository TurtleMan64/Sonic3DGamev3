#include <glad/glad.h>

#include "../entities.h"
#include "../controllableplayer.h"
#include "mhmanager.h"
#include "../../engineTester/main.h"
#include "../../audio/audioplayer.h"

#include <list>

MH_Manager::MH_Manager()
{
	visible = false;
	playedBGM = false;
	timer   = 100;
}

void MH_Manager::step()
{
	if (timer == 100)
	{
		if (Global::gamePlayer->getPosition()->y > 1500)
		{
			timer--;
		}
	}
	else if (timer > 0)
	{
		timer--;
		AudioPlayer::setBGMVolume(timer/100.0f);
	}
	else if (!playedBGM && Global::gamePlayer->getyVel() < -1)
	{
		playedBGM = true;
		AudioPlayer::stopBGM();
		AudioPlayer::playBGMWithIntro(2, 3);
	}
}

std::list<TexturedModel*>* MH_Manager::getModels()
{
	return nullptr;
}
