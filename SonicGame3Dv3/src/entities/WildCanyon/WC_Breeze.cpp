#include <glad/glad.h>

#include "../entities.h"
#include "wcbreeze.h"
#include "../../particles/particleresources.h"
#include "../../particles/particle.h"
#include "../../engineTester/main.h"
#include "../controllableplayer.h"
#include "../../toolbox/maths.h"

#include <list>

WC_Breeze::WC_Breeze(float x, float y, float z,
			         float radius, float height)
{
	position.x = x;
	position.y = y;
	position.z = z;
	radiusSquared = radius*radius;
	this->height = height;
	scale = 1;
	visible = false;
}

void WC_Breeze::step()
{
	Vector3f* posPlayer = Global::gamePlayer->getPosition();

	float xDiff = posPlayer->x - position.x;
	float zDiff = posPlayer->z - position.z;


	float distH = xDiff*xDiff + zDiff*zDiff;

	if (distH <= radiusSquared)
	{
		if (posPlayer->y >= position.y)
		{
			if (posPlayer->y < position.y+height)
			{
				float playerYVel = Global::gamePlayer->getyVel();
				if (playerYVel < -1.0f)
				{
					Global::gamePlayer->setyVel(playerYVel*0.85f);
				}
				else
				{
					if (playerYVel < 5.0f)
					{
						Global::gamePlayer->setyVel(playerYVel+0.2f);
					}
				}
				Global::gamePlayer->setxVelAir(Global::gamePlayer->getXVelAir()*0.98f);
				Global::gamePlayer->setzVelAir(Global::gamePlayer->getZVelAir()*0.98f);
			}
		}
	}

	float rad = sqrtf(radiusSquared);

	Vector3f pos(
		getX() + rad*(Maths::random() - 0.5f),
		getY(),
		getZ() + rad*(Maths::random() - 0.5f));

	Vector3f vel(0, 5.5f, 0);

	new Particle(ParticleResources::textureDust, &pos, &vel,
		0, (int)(height/2.0f), 0, 3 * Maths::random() + 3, 0, false);
}

std::list<TexturedModel*>* WC_Breeze::getModels()
{
	return nullptr;
}
