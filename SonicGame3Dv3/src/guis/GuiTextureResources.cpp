#include "guitextureresources.h"
#include "guitexture.h"
#include "../renderEngine/renderEngine.h"
#include "../engineTester/main.h"

GuiTexture* GuiTextureResources::textureRing        = nullptr;
GuiTexture* GuiTextureResources::textureBlueLine    = nullptr;
GuiTexture* GuiTextureResources::textureRankDisplay = nullptr;

void GuiTextureResources::loadGuiTextures()
{
	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;

	float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension
	float py = 1.0f/(SCR_HEIGHT); //1 pixel in y dimension

	textureRing        = new GuiTexture(Loader_loadTexture("res/Images/Ring.png"),     32*px, 67*py,  32*px, 32*py, 0 );
	textureBlueLine    = new GuiTexture(Loader_loadTexture("res/Images/BlueLine.png"), 0.5f, 0.5f, 10*16*px, 10*128*py, 29.5f);
	textureRankDisplay = new GuiTexture(0, 0.5f, 0.8f, 128*px, 128*py, 0);

	Global::countNew += 3;
}