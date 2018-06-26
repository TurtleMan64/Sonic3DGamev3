#include <glad/glad.h>

#include "entities.h"
#include "../toolbox/vector.h"
#include "shieldmagnet.h"
#include "../engineTester/main.h"
#include "../entities/camera.h"
#include "../entities/controllableplayer.h"
#include "../toolbox/maths.h"
#include "../particles/particle.h"
#include "../particles/particleresources.h"

#include <list>
#include <iostream>


ShieldMagnet::ShieldMagnet()
{
	visible = false;
}

void ShieldMagnet::step()
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
	
		new Particle(ParticleResources::textureSparkleLightBlue, &pos, &off,
				0, 5, 0, 3, -(3.0f / 5.0f), false);

		off.scale(-16.0f);
		pos = center + off;
		off.scale(1/16.0f);

		new Particle(ParticleResources::textureSparkleWhite, &pos, &off,
				0, 5, 0, 3, -(3.0f / 5.0f), false);
	}
}

std::list<TexturedModel*>* ShieldMagnet::getModels()
{
	return nullptr;
}
