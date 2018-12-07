#include "particleresources.h"
#include "particletexture.h"
#include "../renderEngine/renderEngine.h"
#include "../engineTester/main.h"

ParticleTexture* ParticleResources::textureDust = nullptr;
ParticleTexture* ParticleResources::textureDirt = nullptr;
ParticleTexture* ParticleResources::textureSnowDrop = nullptr;
ParticleTexture* ParticleResources::textureDustCloud = nullptr;
ParticleTexture* ParticleResources::textureSnowball = nullptr;
ParticleTexture* ParticleResources::textureStar = nullptr;
ParticleTexture* ParticleResources::textureSparkleYellow = nullptr;
ParticleTexture* ParticleResources::textureSparkleGreen = nullptr;
ParticleTexture* ParticleResources::textureSparkleRed = nullptr;
ParticleTexture* ParticleResources::textureSparkleBlue = nullptr;
ParticleTexture* ParticleResources::textureSparkleLightBlue = nullptr;
ParticleTexture* ParticleResources::textureSparkleWhite = nullptr;
ParticleTexture* ParticleResources::textureWaterDrop = nullptr;
ParticleTexture* ParticleResources::textureLightBlueTrail = nullptr;
ParticleTexture* ParticleResources::textureBlueTrail = nullptr;
ParticleTexture* ParticleResources::textureBlackTrail = nullptr;
ParticleTexture* ParticleResources::textureGrayTrail = nullptr;
ParticleTexture* ParticleResources::texturePinkTrail = nullptr;
ParticleTexture* ParticleResources::textureDarkGreenTrail = nullptr;
ParticleTexture* ParticleResources::textureOrangeTrail = nullptr;
ParticleTexture* ParticleResources::textureRedTrail = nullptr;
ParticleTexture* ParticleResources::textureSplash = nullptr;
ParticleTexture* ParticleResources::textureBubble = nullptr;
ParticleTexture* ParticleResources::textureExplosion1 = nullptr;
ParticleTexture* ParticleResources::textureExplosion2 = nullptr;
ParticleTexture* ParticleResources::textureExplosion3 = nullptr;
ParticleTexture* ParticleResources::textureBlackFade = nullptr;
ParticleTexture* ParticleResources::textureBlackFadeOut = nullptr;
ParticleTexture* ParticleResources::textureTear1 = nullptr;
ParticleTexture* ParticleResources::textureTear2 = nullptr;
ParticleTexture* ParticleResources::textureWhiteFadeOutAndIn = nullptr;
ParticleTexture* ParticleResources::textureBlackFadeOutAndIn = nullptr;
ParticleTexture* ParticleResources::textureInWater = nullptr;
ParticleTexture* ParticleResources::textureBlueLine = nullptr;

void ParticleResources::loadParticles()
{
	INCR_NEW textureSnowDrop          = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SnowDropAtlas.png"), 2, 1.0f, 0);
	INCR_NEW textureDustCloud         = new ParticleTexture(Loader::loadTexture("res/Models/Particle/DustCloud.png"), 1, 0.2f, 0);
	INCR_NEW textureSnowball          = new ParticleTexture(Loader::loadTexture("res/Models/Particle/Snowball.png"), 1, 0.75f, 0);
	INCR_NEW textureStar              = new ParticleTexture(Loader::loadTexture("res/Models/Particle/Star.png"), 1, 1.0f, 0);
	INCR_NEW textureSparkleYellow     = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SparkleYellow.png"), 1, 1.0f, 1);
	INCR_NEW textureSparkleGreen      = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SparkleGreen.png"), 1, 1.0f, 1);
	INCR_NEW textureSparkleRed        = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SparkleRed.png"), 1, 1.0f, 1);
	INCR_NEW textureSparkleBlue       = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SparkleBlue.png"), 1, 1.0f, 1);
	INCR_NEW textureSparkleLightBlue  = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SparkleLightBlue.png"), 1, 1.0f, 1);
	INCR_NEW textureSparkleWhite      = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SparkleWhite.png"), 1, 1.0f, 1);
	INCR_NEW textureWaterDrop         = new ParticleTexture(Loader::loadTexture("res/Models/Particle/WaterDrop.png"), 1, 1, 0);
	INCR_NEW textureLightBlueTrail    = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SpTrailLightBlue.png"), 1, 0.1f, 1);
	INCR_NEW textureBlueTrail         = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SpTrailBlue.png"), 1, 0.1f, 1);
	INCR_NEW textureBlackTrail        = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SpTrailBlack.png"), 1, 0.1f, 1);
	INCR_NEW textureGrayTrail         = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SpTrailGray.png"), 1, 0.1f, 1);
	INCR_NEW texturePinkTrail         = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SpTrailPink.png"), 1, 0.1f, 1);
	INCR_NEW textureDarkGreenTrail    = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SpTrailDarkGreen.png"), 1, 0.1f, 1);
	INCR_NEW textureOrangeTrail       = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SpTrailOrange.png"), 1, 0.3f, 1);
	INCR_NEW textureRedTrail          = new ParticleTexture(Loader::loadTexture("res/Models/Particle/SpTrailRed.png"), 1, 0.3f, 1);
	INCR_NEW textureDust              = new ParticleTexture(Loader::loadTexture("res/Models/Particle/DustAtlas.png"), 4, 0.2f, 0);
	INCR_NEW textureDirt              = new ParticleTexture(Loader::loadTexture("res/Models/Particle/DirtAtlas.png"), 4, 0.75f, 0);
	INCR_NEW textureSplash            = new ParticleTexture(Loader::loadTextureNoInterpolation("res/Models/Particle/SplashAtlas.png"), 4, 0.6f, 0);
	INCR_NEW textureBubble            = new ParticleTexture(Loader::loadTextureNoInterpolation("res/Models/Particle/BubbleInverseAtlas.png"), 4, 0.6f, 0);
	INCR_NEW textureExplosion1        = new ParticleTexture(Loader::loadTextureNoInterpolation("res/Models/Particle/Explosion1Atlas.png"), 4, 0.8f, 0);
	INCR_NEW textureExplosion2        = new ParticleTexture(Loader::loadTextureNoInterpolation("res/Models/Particle/Explosion2Atlas.png"), 4, 0.8f, 0);
	INCR_NEW textureExplosion3        = new ParticleTexture(Loader::loadTexture("res/Models/Particle/Explosion3Atlas.png"), 4, 0.8f, 0);
	INCR_NEW textureBlackFade         = new ParticleTexture(Loader::loadTexture("res/Models/Particle/BlackFadeAtlas.png"), 2, 1.0f, 0);
	INCR_NEW textureBlackFadeOut      = new ParticleTexture(Loader::loadTexture("res/Models/Particle/BlackFadeOutAtlas.png"), 2, 1.0f, 0);
	INCR_NEW textureTear1             = new ParticleTexture(Loader::loadTexture("res/Models/Particle/Tear1.png"), 1, 1.0f, 0);
	INCR_NEW textureTear2             = new ParticleTexture(Loader::loadTexture("res/Models/Particle/Tear2.png"), 1, 1.0f, 0);
	INCR_NEW textureWhiteFadeOutAndIn = new ParticleTexture(Loader::loadTexture("res/Models/Particle/WhiteFadeOutAndInAtlas.png"), 2, 1.0f, 0);
	INCR_NEW textureBlackFadeOutAndIn = new ParticleTexture(Loader::loadTexture("res/Models/Particle/BlackFadeOutAndInAtlas.png"), 2, 1.0f, 0);
	INCR_NEW textureInWater           = new ParticleTexture(Loader::loadTexture("res/Models/Particle/InWater.png"), 1, 0.1f, 1);
	INCR_NEW textureBlueLine          = new ParticleTexture(Loader::loadTexture("res/Models/Particle/BlueLine.png"), 1, 1.0f, 1);
}