#ifndef COMBINESHADER_H
#define COMBINESHADER_H

#include <glad/glad.h>

class CombineShader
{
private:
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	int location_colourTexture;
	int location_highlightTexture;

public:
	CombineShader(char* vFile, char* fFile);

	void start();

	void stop();

	void cleanUp();

	void connectTextureUnits();

protected:
	void bindAttributes();

	void bindAttribute(int attribute, char* variableName);

	void getAllUniformLocations();

	int getUniformLocation(char* uniformName);

	void loadInt(int location, int value);
};

#endif