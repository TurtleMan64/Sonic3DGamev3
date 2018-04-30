#ifndef GUITEXTURE_H
#define GUITEXTURE_H

#include <glad/glad.h>
#include "../toolbox/vector.h"

class GuiTexture
{
private:
	GLuint textureID;
	Vector2f position;
	Vector2f scale;

public:
	//position is (0,0) = top left of screen, (1,1) is bottom right
	//Note that the image is drawn with its CENTER at position
	GuiTexture(GLuint textureID, Vector2f* position, Vector2f* scale);

	//position is (0,0) = top left of screen, (1,1) is bottom right
	//Note that the image is drawn with its CENTER at position
	GuiTexture(GLuint textureID, float posX, float posY, float scaleX, float scaleY);

	GLuint getTexture();

	Vector2f* getPosition();

	Vector2f* getScale();
};

#endif