#include "guitextureresources.h"
#include "guitexture.h"
#include "../renderEngine/renderEngine.h"
#include "../engineTester/main.h"

GuiTexture* GuiTextureResources::textureRing        = nullptr;
GuiTexture* GuiTextureResources::textureBlueLine    = nullptr;
GuiTexture* GuiTextureResources::textureRankDisplay = nullptr;

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

float aspectRatioFactor = SCR_HEIGHT / SCR_WIDTH;

void GuiTextureResources::loadGuiTextures()
{
	printf("%f\n", aspectRatioFactor);
	float safeZone = 0.05f;

	float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension
	float py = 1.0f/(SCR_HEIGHT); //1 pixel in y dimension

	const float w = 0.02f * 16.0f / 9.0f * SCR_HEIGHT / SCR_WIDTH; //width of a single text character
	
	INCR_NEW textureRing        = new GuiTexture(Loader::loadTexture("res/Images/RingHD.png"),     safeZone + w, safeZone + 0.12f, 2*w, 2*w * (float) SCR_WIDTH / (float) SCR_HEIGHT, 0 );
	INCR_NEW textureBlueLine    = new GuiTexture(Loader::loadTexture("res/Images/BlueLine.png"), 0.5f, 0.5f, 10*16*px, 10*128*py, 29.5f);
	INCR_NEW textureRankDisplay = new GuiTexture(0, 0.5f, 0.8f, .15f * SCR_HEIGHT / SCR_WIDTH, 0.15f, 0);
}