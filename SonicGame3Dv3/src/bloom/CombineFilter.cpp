#include <glad/glad.h>

#include "../engineTester/main.h"
#include "combinefilter.h"
#include "combineshader.h"
#include "../postProcessing/imagerenderer.h"

CombineFilter::CombineFilter()
{
	shader = new CombineShader("res/Shaders/bloom/simpleVertex.txt", "res/Shaders/bloom/combineFragment.txt"); Global::countNew++;
	shader->start();
	shader->connectTextureUnits();
	shader->stop();
	renderer = new ImageRenderer; Global::countNew++;
}

void CombineFilter::render(GLuint colourTexture, GLuint highlightTexture)
{
	shader->start();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colourTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, highlightTexture);
	renderer->renderQuad();
	shader->stop();
}

void CombineFilter::cleanUp()
{
	renderer->cleanUp();
	shader->cleanUp();
	delete shader; Global::countDelete++;
	delete renderer; Global::countDelete++;
}
