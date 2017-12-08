#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "../models/models.h"
#include "../entities/entities.h"
#include "../shaders/shaders.h"
#include "../toolbox/matrix.h"

#ifndef RENDERENGINE_H
#define RENDERENGINE_H
//DisplayManager
int createDisplay();
void updateDisplay();
void closeDisplay();
int displayWantsToClose();
GLFWwindow* getWindow();


//Loader
RawModel loadToVAO(std::vector<float>*, std::vector<float>*, std::vector<float>*, std::vector<int>*);
GLuint loadTexture(char*);
GLuint loadTextureWORKS(char*);
void cleanUp();

//Renderer
class Renderer
{
private:
	Matrix4f projectionMatrix;

public:
	Renderer(ShaderProgram*);

	void prepare();

	void render(Entity*, ShaderProgram*);

	void createProjectionMatrix();

};
#endif