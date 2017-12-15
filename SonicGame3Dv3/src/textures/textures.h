#ifndef TEXTURES_H
#define TEXTURES_H

#include <glad/glad.h>


class ModelTexture
{
private:
	GLuint texID;

	float shineDamper;
	float reflectivity;
	int hasTransparency;
	int useFakeLighting;

public:
	ModelTexture();

	ModelTexture(GLuint texID);

	GLuint getID();
	void setID(GLuint newID);

	float getShineDamper();
	void setShineDamper(float newShineDamper);

	float getReflectivity();
	void setReflectivity(float newReflectivity);

	int getHasTransparency();
	void setHasTransparency(int newHasTransparency);

	int getUsesFakeLighting();
	void setUsesFakeLighting(int newUsesFakeLighting);

	void deleteMe();
};
#endif