#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "../toolbox/vector.h"
#include "../toolbox/matrix.h"
#include "../entities/camera.h"
#include "../toolbox/maths.h"
#include "shaders.h"

float matrixBuffer[16];

GLuint loadShader(char*, int);

ShaderProgram::ShaderProgram(char* vertexFile, char* fragmentFile)
{
	vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	bindAttributes();
	glLinkProgram(programID);
	glValidateProgram(programID);
	getAllUniformLocations();
}

void ShaderProgram::start()
{
	glUseProgram(programID); //std::fprintf(stdout, "using shader id = %d\n", programID);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}

void ShaderProgram::loadTransformationMatrix(Matrix4f* matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}

void ShaderProgram::loadProjectionMatrix(Matrix4f* projection)
{
	loadMatrix(location_projectionMatrix, projection);
}

void ShaderProgram::loadViewMatrix(Camera* cam)
{
	Matrix4f viewMatrix;
	createViewMatrix(&viewMatrix, cam);
	loadMatrix(location_viewMatrix, &viewMatrix);
}

void ShaderProgram::loadLight(Light* light)
{
	loadVector(location_lightPosition, light->getPosition());
	loadVector(location_lightColour, light->getColour());
}

void ShaderProgram::loadShineVariables(float damper, float reflectivity)
{
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflectivity);
}

void ShaderProgram::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

void ShaderProgram::bindAttribute(int attribute, char* variableName)
{
	glBindAttribLocation(programID, attribute, variableName);
}

void ShaderProgram::getAllUniformLocations()
{
	location_transformationMatrix = getUniformLocation("transformationMatrix");
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_lightPosition = getUniformLocation("lightPosition");
	location_lightColour = getUniformLocation("lightColour");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
}

int ShaderProgram::getUniformLocation(char* uniformName)
{
	return glGetUniformLocation(programID, uniformName);
}

void ShaderProgram::loadFloat(int location, float value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadVector(int location, Vector3f* vect)
{
	glUniform3f(location, vect->x, vect->y, vect->z);
}

void ShaderProgram::loadBoolean(int location, float value)
{
	glUniform1f(location, round(value));
}

void ShaderProgram::loadMatrix(int location, Matrix4f* matrix)
{
	matrix->store(matrixBuffer);
	glUniformMatrix4fv(location, 1, GL_FALSE, matrixBuffer);
}

GLuint loadShader(char* fileName, int type)
{
	std::ifstream sourceFile;
	sourceFile.open(fileName);
	std::string filetext;

	if (sourceFile.is_open())
	{
		while (!sourceFile.eof())
		{
			std::string line;
			getline(sourceFile, line);
			filetext.append(line + "\n");
		}

		sourceFile.close();
	}
	else
	{
		std::fprintf(stdout, "Error: Could not find shader file '%s'\n", fileName);
		sourceFile.close();
		return 0;
	}

	//std::fprintf(stdout, "%s\n", filetext.c_str());
	unsigned int id = glCreateShader(type);
	const char* src = filetext.c_str();
	const int len = filetext.size();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	//std::fprintf(stdout, "shader = %d\n", id);
	return id;
}