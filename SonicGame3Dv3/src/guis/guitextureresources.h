#ifndef GUITEXTURERESOURCES_H
#define GUITEXTURERESOURCES_H

#include "../renderEngine/renderEngine.h"

class GuiTexture;

class GuiTextureResources
{
public:
	static GuiTexture* textureRing;

	static void loadGuiTextures();
};
#endif