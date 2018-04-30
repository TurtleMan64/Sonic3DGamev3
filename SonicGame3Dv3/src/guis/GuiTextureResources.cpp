#include "guitextureresources.h"
#include "guitexture.h"
#include "../renderEngine/renderEngine.h"
#include "../engineTester/main.h"

GuiTexture* GuiTextureResources::textureRing = nullptr;

void GuiTextureResources::loadGuiTextures()
{
	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;

	float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension
	float py = 1.0f/(SCR_HEIGHT); //1 pixel in y dimension

	textureRing          = new GuiTexture(Loader_loadTexture("res/Images/Ring.png"), 32*px, 67*py, 32*px, 32*py);

	Global::countNew += 1;
}