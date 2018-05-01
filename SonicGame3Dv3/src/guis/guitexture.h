#ifndef GUITEXTURE_H
#define GUITEXTURE_H

#include <glad/glad.h>
#include "../toolbox/vector.h"

class GuiTexture
{
private:
	GLuint textureID;
	Vector2f position;
	Vector2f sizeRaw;
	Vector2f sizeScaled;
	float scale;
	bool visible;

public:
	//position is (0,0) = top left of screen, (1,1) is bottom right
	//Note that the image is drawn with its CENTER at position
	GuiTexture(GLuint textureID, Vector2f* position, Vector2f* size);

	//position is (0,0) = top left of screen, (1,1) is bottom right
	//Note that the image is drawn with its CENTER at position
	GuiTexture(GLuint textureID, float posX, float posY, float sizeX, float sizeY);

	GLuint getTexture();

	void setTexture(GLuint newTextureID);

	Vector2f* getPosition();

	Vector2f* getSizeRaw();

	Vector2f* getSizeScaled();

	void setX(float newX);

	void setY(float newY);

	bool getVisible();

	void setVisible(bool newVisible);

	float getScale();

	void setScale(float newScale);
};

#endif