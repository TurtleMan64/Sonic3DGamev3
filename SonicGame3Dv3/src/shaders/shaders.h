#ifndef SHADERS_H
#define SHADERS_H

class Matrix4f;
class Camera;
class Light;
class Vector3f;

#include <glad/glad.h>


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
	int location_useFakeLighting;
	int location_skyColour;

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

	void loadFakeLighting(int fakeLighting);

	void loadSkyColour(float r, float g, float b);

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