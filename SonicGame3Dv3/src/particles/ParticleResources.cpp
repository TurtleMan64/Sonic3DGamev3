#include "particleresources.h"
#include "particletexture.h"
#include "../renderEngine/renderEngine.h"
#include "../engineTester/main.h"

ParticleTexture* ParticleResources::textureDust = nullptr;
ParticleTexture* ParticleResources::textureSnowDrop = nullptr;
ParticleTexture* ParticleResources::textureDustCloud = nullptr;
ParticleTexture* ParticleResources::textureSnowball = nullptr;
ParticleTexture* ParticleResources::textureStar = nullptr;
ParticleTexture* ParticleResources::textureSparkleYellow = nullptr;
ParticleTexture* ParticleResources::textureSparkleRed = nullptr;
ParticleTexture* ParticleResources::textureSparkleBlue = nullptr;
ParticleTexture* ParticleResources::textureWaterDrop = nullptr;
ParticleTexture* ParticleResources::textureLightBlueTrail = nullptr;
ParticleTexture* ParticleResources::textureBlueTrail = nullptr;
ParticleTexture* ParticleResources::textureBlackTrail = nullptr;
ParticleTexture* ParticleResources::textureGrayTrail = nullptr;
ParticleTexture* ParticleResources::textureSplash = nullptr;
ParticleTexture* ParticleResources::textureBubble = nullptr;
ParticleTexture* ParticleResources::textureExplosion1 = nullptr;
ParticleTexture* ParticleResources::textureExplosion2 = nullptr;
ParticleTexture* ParticleResources::textureBlackFade = nullptr;
ParticleTexture* ParticleResources::textureTear1 = nullptr;
ParticleTexture* ParticleResources::textureTear2 = nullptr;

void ParticleResources::loadParticles()
{
	textureSnowDrop       = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SnowDropAtlas.png"), 2, 1.0f, 0);
	textureDustCloud      = new ParticleTexture(Loader_loadTexture("res/Models/Particle/41257828.png"), 1, 0.2f, 0);
	textureSnowball       = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Snowball.png"), 1, 0.75f, 0);
	textureStar           = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Star.png"), 1, 1.0f, 0);
	textureSparkleYellow  = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Sparkle.png"), 1, 1.0f, 1);
	textureSparkleRed     = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SparkleRed.png"), 1, 1.0f, 1);
	textureSparkleBlue    = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SparkleBlue.png"), 1, 1.0f, 1);
	textureWaterDrop      = new ParticleTexture(Loader_loadTexture("res/Models/Particle/WaterDrop.png"), 1, 1, 0);
	textureLightBlueTrail = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailLightBlue.png"), 1, 0.1f, 1);
	textureBlueTrail      = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailBlue.png"), 1, 0.1f, 1);
	textureBlackTrail     = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailBlack.png"), 1, 0.1f, 1);
	textureGrayTrail      = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailGray.png"), 1, 0.1f, 1);
	textureDust           = new ParticleTexture(Loader_loadTexture("res/Models/Particle/DustAtlas.png"), 4, 0.2f, 0);
	textureSplash         = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SplashAtlas.png"), 4, 0.6f, 0);
	textureBubble         = new ParticleTexture(Loader_loadTexture("res/Models/Particle/BubbleInverseAtlas.png"), 4, 0.6f, 0);
	textureExplosion1     = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Explosion1Atlas.png"), 4, 0.8f, 0);
	textureExplosion2     = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Explosion2Atlas.png"), 4, 0.8f, 0);
	textureBlackFade      = new ParticleTexture(Loader_loadTexture("res/Models/Particle/BlackFadeAtlas.png"), 2, 1.0f, 0);
	textureTear1          = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Tear1.png"), 1, 1.0f, 0);
	textureTear2          = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Tear2.png"), 1, 1.0f, 0);
	Global::countNew += 20;
}