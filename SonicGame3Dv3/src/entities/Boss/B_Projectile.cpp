#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "bprojectile.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../controllableplayer.h"
#include "../../particles/particle.h"
#include "../../particles/particleresources.h"

#include <list>
#include <iostream>

B_Projectile::B_Projectile()
{
	
}

B_Projectile::B_Projectile(float x, float y, float z, float velX, float velY, float velZ)
{
	position.x = x;
	position.y = y;
	position.z = z;
	xVel = velX;
	yVel = velY;
	zVel = velZ;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	tracking = true;
	timer = 0;
	visible = false;

	speed = sqrtf(xVel*xVel + yVel*yVel + zVel*zVel);
}

void B_Projectile::step()
{
	Vector3f toPlayer = position - Global::gamePlayer->getCenterPosition();
	float distToPlayerSquared = toPlayer.lengthSquared();

	if (tracking)
	{
		if (toPlayer.lengthSquared() < 20*20 || toPlayer.x < 0)
		{
			tracking = false;
		}

		toPlayer.normalize();
		toPlayer.scale(-0.25f);
		Vector3f dir(xVel, yVel, zVel);
		dir = dir + toPlayer;
		dir.normalize();
		dir.scale(speed);

		xVel = dir.x;
		yVel = dir.y;
		zVel = dir.z;
	}
	else
	{
		timer++;

		if (timer > 360)
		{
			Main_deleteEntity(this);
			return;
		}
	}

	if (distToPlayerSquared < 5*5)
	{
		Global::gamePlayer->takeDamage(getPosition());
	}

	increasePosition(xVel, yVel, zVel);

	//int count = 2;

	//while (count != 0)
	//{
		//Vector3f off = randomPointOnSphere();
		//
		//off.scale(4);
		//Vector3f pos(position.x+off.x, position.y+off.y, position.z+off.z);
		//off.scale(1/4.0f);
		//new Particle(ParticleResources::textureSparkleYellow, &pos, &off,
		//		0, 5, 0, 3, -(3.0f / 5.0f), false);
		//
		//off.scale(-4);
		//pos.set(position.x+off.x, position.y+off.y, position.z+off.z);
		//off.scale(1/4.0f);
		//new Particle(ParticleResources::textureSparkleWhite, &pos, &off,
		//		0, 5, 0, 3, -(3.0f / 5.0f), false);

		//count--;
	//}

	Vector3f vels(xVel, yVel, zVel);
	new Particle(ParticleResources::textureSparkleYellow, &position, &vels,
			0, 5, 0, 3, -(3.0f / 5.0f), false);
}

std::list<TexturedModel*>* B_Projectile::getModels()
{
	return nullptr;
}
