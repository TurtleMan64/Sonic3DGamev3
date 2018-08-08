#include <glad/glad.h>
#include <list>
#include "fontrenderer.h"
#include "../fontMeshCreator/fonttype.h"
#include "../fontMeshCreator/guitext.h"
#include "fontshader.h"
#include "../engineTester/main.h"


FontRenderer::FontRenderer()
{
	shader = new FontShader("res/Shaders/fontRendering/fontVertex.txt", "res/Shaders/fontRendering/fontFragment.txt");
	INCR_NEW
}


void FontRenderer::render(std::unordered_map<FontType*, std::list<GUIText*>>* texts)
{
	prepare();
	for (auto kv : (*texts))
	{
		FontType* font = kv.first;
		std::list<GUIText*> listOfTexts = kv.second;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, font->getTextureAtlas());
		for (GUIText* text : listOfTexts)
		{
			if (text->isVisible())
			{
				renderText(text);
			}
		}
	}
	endRendering();
}

void FontRenderer::cleanUp()
{
	shader->cleanUp();
}

void FontRenderer::prepare()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	shader->start();
}

void FontRenderer::renderText(GUIText* text)
{
	glBindVertexArray(text->getMesh());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	shader->loadColour(text->getColour());
	shader->loadTranslation(text->getPosition());
	glDrawArrays(GL_TRIANGLES, 0, text->getVertexCount());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

void FontRenderer::endRendering()
{
	shader->stop();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}
