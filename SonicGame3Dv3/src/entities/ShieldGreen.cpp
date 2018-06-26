#include <glad/glad.h>

#include "entities.h"
#include "../toolbox/vector.h"
#include "shieldgreen.h"
#include "../engineTester/main.h"
#include "../entities/camera.h"
#include "../entities/controllableplayer.h"
#include "../toolbox/maths.h"
#include "../particles/particle.h"
#include "../particles/particleresources.h"

#include <list>
#include <iostream>

ShieldGreen::ShieldGreen()
{
	visible = false;
}

void ShieldGreen::step()
{
	setPosition(Global::gamePlayer->getPosition());
	updateTransformationMatrix();

	Vector3f center = Global::gamePlayer->getCenterPosition();

	for (int i = 0; i < 10; i++)
	{
		Vector3f off = randomPointOnSphere();
		off.scale(8);

		Vector3f pos = center + off;

		off.scale(1/16.0f);
	
		new Particle(ParticleResources::textureSparkleGreen, &pos, &off,
				0, 5, 0, 3, -(3.0f / 5.0f), false);

		off.scale(-16.0f);
		pos = center + off;
		off.scale(1/16.0f);

		new Particle(ParticleResources::textureSparkleGreen, &pos, &off,
				0, 5, 0, 3, -(3.0f / 5.0f), false);
	}
}

std::list<TexturedModel*>* ShieldGreen::getModels()
{
	return nullptr;
}

