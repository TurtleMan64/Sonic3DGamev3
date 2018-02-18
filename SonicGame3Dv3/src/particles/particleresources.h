#ifndef PARTICLERESOURCES_H
#define PARTICLERESOURCES_H

#include "../renderEngine/renderEngine.h"

class ParticleTexture;

class ParticleResources
{
public:
	static ParticleTexture* textureDust;
	static ParticleTexture* textureSnowDrop;
	static ParticleTexture* textureDustCloud;
	static ParticleTexture* textureSnowball;
	static ParticleTexture* textureStar;
	static ParticleTexture* textureSparkleYellow;
	static ParticleTexture* textureSparkleRed;
	static ParticleTexture* textureSparkleBlue;
	static ParticleTexture* textureWaterDrop;
	static ParticleTexture* textureLightBlueTrail;
	static ParticleTexture* textureBlueTrail;
	static ParticleTexture* textureBlackTrail;
	static ParticleTexture* textureGrayTrail;
	static ParticleTexture* texturePinkTrail;
	static ParticleTexture* textureDarkGreenTrail;
	static ParticleTexture* textureSplash;
	static ParticleTexture* textureBubble;
	static ParticleTexture* textureExplosion1;
	static ParticleTexture* textureExplosion2;
	static ParticleTexture* textureBlackFade;
	static ParticleTexture* textureTear1;
	static ParticleTexture* textureTear2;

	static void loadParticles();
};
#endif