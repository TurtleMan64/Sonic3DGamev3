#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "../toolbox/vector.h"
#include "../toolbox/matrix.h"
#include "../entities/camera.h"
#include "../entities/light.h"

#ifndef SHADERS_H
#define SHADERS_H

class ShaderProgram
{
private:
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	int location_transformationMatrix;
	int location_projectionMatrix;
	int location_viewMatrix;
	int location_lightPosition;
	int location_lightColour;
	int location_shineDamper;
	int location_reflectivity;

public:
	ShaderProgram(char*, char*);

	void start();

	void stop();

	void cleanUp();

	void loadTransformationMatrix(Matrix4f*);

	void loadProjectionMatrix(Matrix4f*);

	void loadViewMatrix(Camera*);

	void loadLight(Light*);

	void loadShineVariables(float damper, float reflectivity);

protected:
	void bindAttributes();

	void bindAttribute(int, char*);

	void getAllUniformLocations();

	int getUniformLocation(char*);

	void loadFloat(int, float);

	void loadVector(int, Vector3f*);

	void loadBoolean(int, float);

	void loadMatrix(int, Matrix4f*);
};

#endif