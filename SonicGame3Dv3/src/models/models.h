#include <glad/glad.h>

#include "../textures/textures.h"

#ifndef MODELS_H
#define MODELS_H
class RawModel
{
private:
	GLuint vaoID;
	int vertexCount;

public:
	RawModel();

	RawModel(GLuint vaoID, int vertexCount);

	int getVaoID();

	int getVertexCount();

	void deleteMe();
};

class TexturedModel
{
private:
	RawModel rawModel;
	ModelTexture texture;

public:
	TexturedModel(RawModel*, ModelTexture*);

	TexturedModel();

	RawModel* getRawModel();

	ModelTexture* getTexture();

	void deleteMe();
};
#endif