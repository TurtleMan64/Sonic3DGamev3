#include <glad/glad.h>

#ifndef TEXTURES_H
#define TEXTURES_H
class ModelTexture
{
private:
	GLuint texID;

	float shineDamper;
	float reflectivity;

public:
	ModelTexture();

	ModelTexture(GLuint texID);

	int getID();

	float getShineDamper();

	void setShineDamper(float newShineDamper);

	float getReflectivity();

	void setReflectivity(float newReflectivity);
};
#endif