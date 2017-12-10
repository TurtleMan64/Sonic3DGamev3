#include <glad/glad.h>

#ifndef TEXTURES_H
#define TEXTURES_H
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

	int getID();

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