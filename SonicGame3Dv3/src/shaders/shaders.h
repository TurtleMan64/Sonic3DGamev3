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
	int location_hasTransparency;
	int location_skyColour;
	int location_texOffX;
	int location_texOffY;
	int location_glowAmount;
	int location_fogDensity;
	int location_fogGradient;

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

	void loadTransparency(int transparency);

	void loadGlowAmount(float glowAmount);

	void loadTextureOffsets(float offX, float offY);

	void loadSkyColour(float r, float g, float b);

	void loadFogDensity(float density);

	void loadFogGradient(float gradient);

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