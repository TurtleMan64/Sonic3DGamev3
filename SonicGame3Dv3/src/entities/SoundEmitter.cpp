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

