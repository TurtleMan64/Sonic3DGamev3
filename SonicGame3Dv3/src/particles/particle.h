#ifndef PARTICLE_H
#define PARTICLE_H

class ParticleTexture;
class Camera;

#include "../toolbox/vector.h"

class Particle
{
private:
	Vector3f position;
	Vector3f* positionRef;
	Vector3f velocity;
	float gravityEffect;
	int lifeLength;
	float rotation;
	float scaleX;
	float scaleXChange;
	float scaleY;
	float scaleYChange;
	float distance;
	ParticleTexture* texture;
	Vector2f texOffset1;
	Vector2f texOffset2;
	float blend;
	int elapsedTime = 0;

	void updateTextureCoordInfo();

	void setTextureOffset(Vector2f* offset, int index);

public:
	Particle(ParticleTexture* texture, Vector3f* position, Vector3f* velocity, float gravityEffect,
		int lifeLength, float rotation, float scale, float scaleChange, bool posIsRef);

	Particle(ParticleTexture* texture, Vector3f* position, Vector3f* velocity, float gravityEffect,
		int lifeLength, float rotation, float scaleX, float scaleXChange, float scaleY, float scaleYChange, 
		bool posIsRef);

	float getDistance();

	ParticleTexture* getTexture();

	Vector3f* getPosition();

	float getRotation();

	float getScaleX();

	float getScaleY();

	Vector2f* getTexOffset1();

	Vector2f* getTexOffset2();

	float getBlend();

	bool update(Camera* camera);
};
#endif