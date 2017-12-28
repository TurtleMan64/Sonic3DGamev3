#include "guitext.h"
#include "../renderEngine/renderEngine.h"
#include "../fontRendering/textmaster.h"

GUIText::GUIText(std::string text, float fontSize, FontType* font, Vector2f* position, float maxLineLength,
	bool centered, bool visible)
{
	this->colour.set(1, 1, 1);
	this->centerText = false;
	this->textString.assign(text);
	this->fontSize = fontSize;
	this->font = font;
	this->position.set(position);
	this->lineMaxSize = maxLineLength;
	this->centerText = centered;
	this->visible = visible;
	TextMaster::loadText(this);
}

void GUIText::deleteMe()
{
	TextMaster::removeText(this);
	for (int vboID : textMeshVbos)
	{
		Loader_deleteVBO(vboID);
	}
	Loader_deleteVAO(textMeshVao);
}

FontType* GUIText::getFont()
{
	return font;
}

void GUIText::setColour(float r, float g, float b)
{
	colour.set(r, g, b);
}

Vector3f* GUIText::getColour()
{
	return &colour;
}

int GUIText::getNumberOfLines()
{
	return numberOfLines;
}

Vector2f* GUIText::getPosition()
{
	return &position;
}

void GUIText::setPosition(Vector2f* newPos)
{
	position.set(newPos);
}

void GUIText::setVisibility(bool newVisible)
{
	visible = newVisible;
}

bool GUIText::isVisible()
{
	return visible;
}

int GUIText::getMesh()
{
	return textMeshVao;
}

void GUIText::setMeshInfo(int vao, std::vector<int>* vbos, int verticesCount)
{
	this->textMeshVao = vao;
	for (int vbo : (*vbos))
	{
		this->textMeshVbos.push_back(vbo);
	}
	this->vertexCount = verticesCount;
}

int GUIText::getVertexCount()
{
	return vertexCount;
}

float GUIText::getFontSize()
{
	return fontSize;
}

void GUIText::setNumberOfLines(int number)
{
	numberOfLines = number;
}

bool GUIText::isCentered()
{
	return centerText;
}

float GUIText::getMaxLineSize()
{
	return lineMaxSize;
}

std::string* GUIText::getTextString()
{
	return &textString;
}
