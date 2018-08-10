#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "shdgoronkid.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/camera.h"
#include "../../entities/controllableplayer.h"
#include "../../toolbox/maths.h"
#include "../../guis/guimanager.h"
#include "../../audio/audioplayer.h"
#include "../goalsign.h"
#include "../../particles/particletexture.h"
#include "../../particles/particleresources.h"
#include "../../particles/particle.h"
#include "../../audio/source.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> SHD_GoronKid::models;

bool SHD_GoronKid::found = false;

SHD_GoronKid::SHD_GoronKid()
{

}

SHD_GoronKid::SHD_GoronKid(float x, float y, float z)
{
	if (Global::gameIsChaoMode || Global::gameIsRingMode)
	{
		Main_deleteEntity(this);
		return;
	}

	position.x = x;
	position.y = y;
	position.z = z;
	scale = 1.5f;
	rotX = 0;
	rotY = 0;
	rotZ = 0;

	SHD_GoronKid::found = false;

	crySource = nullptr;
	cryTimer = 0;
	visible = true;

	GoalSign::addTrigger();

	updateTransformationMatrix();
}


void SHD_GoronKid::step()
{
	if (SHD_GoronKid::found == false)
	{
		ControllablePlayer* p = Global::gamePlayer;
		float xDiff = p->getX()-getX();
		float zDiff = p->getZ()-getZ();
		float yDiff = p->getY()-getY();
		float mag = sqrtf((xDiff*xDiff)+(zDiff*zDiff)+(yDiff*yDiff));

		cryTimer = (cryTimer+1) % 255;

		const float modelScale = 1.5f;


		if (mag < 1000)
		{
			//std::fprintf(stdout, "here2\n");
			ParticleTexture* tex = ParticleResources::textureTear1;
			if (Maths::random() >= 0.5f)
			{
				tex = ParticleResources::textureTear2;
			}

			Vector3f pos(
				getX() + 1.770f*modelScale,
				getY() + 7.236f*modelScale,
				getZ() + 0.632f*modelScale);

			Vector3f vel(
				0.5f*(Maths::random()-0.5f), 
				1 + 0.5f*(Maths::random()-0.5f),
				0.5f + 0.5f*(Maths::random()-0.5f));

			new Particle(tex, &pos, &vel,
				0.08f, 120, 0, Maths::random()+0.6f, 0, false);

			pos.z = getZ() - 0.632f*modelScale;

			vel.set(
				0.5f*(Maths::random()-0.5f), 
				1 + 0.5f*(Maths::random()-0.5f),
				-0.5f + 0.5f*(Maths::random()-0.5f));

			new Particle(tex, &pos, &vel,
				0.08f, 120, 0, Maths::random()+0.6f, 0, false);

			if (cryTimer == 0)
			{
				int index = (int)(Maths::random()*3);
				crySource = AudioPlayer::play(39+index, getPosition());
			}

			if (mag < 10)
			{
				if (crySource != nullptr && crySource->isPlaying())
				{
					if (crySource->getLastPlayedBufferID() == 39 ||
						crySource->getLastPlayedBufferID() == 40 ||
						crySource->getLastPlayedBufferID() == 41)
					{
						crySource->stop();
					}
				}

				AudioPlayer::play(42, getPosition());

				SHD_GoronKid::found = true;
				visible = false;
				GoalSign::removeTrigger();
			}
		}
	}
}

std::list<TexturedModel*>* SHD_GoronKid::getModels()
{
	return &SHD_GoronKid::models;
}

void SHD_GoronKid::loadStaticModels()
{
	if (SHD_GoronKid::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading SHD_GoronKid static models...\n");
	#endif

	loadObjModel(&SHD_GoronKid::models, "res/Models/Gorons/", "Kid.obj");
}

void SHD_GoronKid::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting SHD_GoronKid static models...\n");
	#endif

	Entity::deleteModels(&SHD_GoronKid::models);
}
