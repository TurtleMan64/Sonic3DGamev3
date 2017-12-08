#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderEngine.h"
#include "../entities/entities.h"
#include "../shaders/shaders.h"
#include "../toolbox/matrix.h"
#include "../toolbox/vector.h"
#include "../toolbox/maths.h"

#include <iostream>

const float FOV = 70;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 1000;

Renderer::Renderer(ShaderProgram* shader)
{
	createProjectionMatrix();
	shader->start();
	shader->loadProjectionMatrix(&projectionMatrix);
	shader->stop();
}

void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Entity* entity, ShaderProgram* shader)
{
	TexturedModel* texturedModel = entity->getModel();
	RawModel* model = (*texturedModel).getRawModel();
	glBindVertexArray((*model).getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	Matrix4f transformationMatrix;
	createTransformationMatrix(&transformationMatrix, entity->getPosition(), entity->getRotX(), entity->getRotY(), entity->getRotZ(), entity->getScale());
	shader->loadTransformationMatrix(&transformationMatrix);
	ModelTexture* texture = texturedModel->getTexture();
	shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (*(*texturedModel).getTexture()).getID());
	glDrawElements(GL_TRIANGLES, (*model).getVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}


void Renderer::createProjectionMatrix()
{
	int displayWidth;
	int displayHeight;
	glfwGetWindowSize(getWindow(), &displayWidth, &displayHeight);
	float aspectRatio = (float)displayWidth / (float)displayHeight;
	float y_scale = (float)((1.0f / tan(toRadians(FOV / 2.0f))) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = FAR_PLANE - NEAR_PLANE;

	projectionMatrix.m00 = x_scale;
	projectionMatrix.m11 = y_scale;
	projectionMatrix.m22 = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
	projectionMatrix.m23 = -1;
	projectionMatrix.m32 = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
	projectionMatrix.m33 = 0;
}
