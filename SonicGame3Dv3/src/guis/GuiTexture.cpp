#include "guitexture.h"

#include <glad/glad.h>
#include "../toolbox/vector.h"

GuiTexture::GuiTexture(GLuint textureID, Vector2f* position, Vector2f* scale)
{
	this->textureID = textureID;
	this->position.x = (position->x*2.0f)-1;
	this->position.y = -((position->y*2.0f)-1);
	this->scale.set(scale);
}

GuiTexture::GuiTexture(GLuint textureID, float posX, float posY, float scaleX, float scaleY)
{
	this->textureID = textureID;
	this->position.x = (posX*2.0f)-1;
	this->position.y = -((posY*2.0f)-1);
	this->scale.x = scaleX;
	this->scale.y = scaleY;
}

GLuint GuiTexture::getTexture()
{
	return textureID;
}

Vector2f* GuiTexture::getPosition()
{
	return &position;
}

Vector2f* GuiTexture::getScale()
{
	return &scale;
}
