#include "particle.h"
#include "particletexture.h"
#include "../entities/camera.h"
#include "../toolbox/vector.h"
#include "particlemaster.h"
#include "../engineTester/main.h"

Particle::Particle(ParticleTexture* texture, Vector3f* position, Vector3f* velocity, float gravityEffect,
	int lifeLength, float rotation, float scale, float scaleChange, bool posIsRef)
{
	this->texture = texture;
	if (posIsRef)
	{
		this->positionRef = position;
	}
	else
	{
		this->positionRef = &this->position;
	}
	this->position.x = position->x;
	this->position.y = position->y;
	this->position.z = position->z;
	this->velocity.x = velocity->x;
	this->velocity.y = velocity->y;
	this->velocity.z = velocity->z;
	this->gravityEffect = gravityEffect;
	this->lifeLength = lifeLength;
	this->rotation = rotation;
	this->scale = scale;
	this->scaleChange = scaleChange;
	if (Global::renderParticles)
	{
		ParticleMaster::addParticle(this);
	}
	else
	{
		delete this;
	}
}

void Particle::updateTextureCoordInfo()
{
	float lifeFactor = elapsedTime / (float)(lifeLength);
	int stageCount = texture->getNumberOfRows() * texture->getNumberOfRows();
	float atlasProgression = lifeFactor * stageCount;
	int index1 = (int)atlasProgression;
	int index2 = index1 < stageCount - 1 ? index1 + 1 : index1;
	this->blend = fmodf(atlasProgression, 1); 
	setTextureOffset(&texOffset1, index1);
	setTextureOffset(&texOffset2, index2);
}

void Particle::setTextureOffset(Vector2f* offset, int index)
{
	int column = index % texture->getNumberOfRows();
	int row = index / texture->getNumberOfRows();
	offset->x = (float)column / texture->getNumberOfRows();
	offset->y = (float)row / texture->getNumberOfRows();
}

float Particle::getDistance()
{
	return distance;
}

ParticleTexture* Particle::getTexture()
{
	return texture;
}

Vector3f* Particle::getPosition()
{
	return positionRef;
}

float Particle::getRotation()
{
	return rotation;
}

float Particle::getScale()
{
	return scale;
}

Vector2f* Particle::getTexOffset1()
{
	return &texOffset1;
}

Vector2f* Particle::getTexOffset2()
{
	return &texOffset2;
}

float Particle::getBlend()
{
	return blend;
}

bool Particle::update(Camera* camera)
{
	velocity.y -= gravityEffect;
	scale = fmaxf(0, scale + scaleChange);

	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;

	Vector3f dist(camera->getPosition());
	dist = dist-position;

	distance = dist.lengthSquared();

	updateTextureCoordInfo();
	elapsedTime += 1;
	return elapsedTime < lifeLength;
}
