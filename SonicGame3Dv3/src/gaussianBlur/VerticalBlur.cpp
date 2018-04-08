#include <glad/glad.h>

#include "verticalblur.h"
#include "verticalblurshader.h"
#include "../postProcessing/imagerenderer.h"
#include "../engineTester/main.h"

VerticalBlur::VerticalBlur(int targetFboWidth, int targetFboHeight)
{
	shader = new VerticalBlurShader("res/Shaders/gaussianBlur/verticalBlurVertex.txt", "res/Shaders/gaussianBlur/blurFragment.txt"); Global::countNew++;
	shader->start();
	shader->loadTargetHeight((float)targetFboHeight);
	shader->stop();
	renderer = new ImageRenderer(targetFboWidth, targetFboHeight); Global::countNew++;
}

void VerticalBlur::render(GLuint texture)
{
	shader->start();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	renderer->renderQuad();
	shader->stop();
}

int VerticalBlur::getOutputTexture()
{
	return renderer->getOutputTexture();
}

void VerticalBlur::cleanUp()
{
	renderer->cleanUp();
	shader->cleanUp();
	delete shader; Global::countDelete++;
	delete renderer; Global::countDelete++;
}
