#ifndef HORIZONTALBLURSHADER_H
#define HORIZONTALBLURSHADER_H

#include <glad/glad.h>

class HorizontalBlurShader
{
private:
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	int location_targetWidth;

public:
	HorizontalBlurShader(char* vFile, char* fFile);

	void start();

	void stop();

	void cleanUp();

	void loadTargetWidth(float width);

protected:
	void bindAttributes();

	void bindAttribute(int attribute, char* variableName);

	void getAllUniformLocations();

	int getUniformLocation(char* uniformName);

	void loadFloat(int location, float value);
};

#endif