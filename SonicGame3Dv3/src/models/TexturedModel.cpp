#include <glad/glad.h>

#include "models.h"
#include "../textures/textures.h"

TexturedModel::TexturedModel()
{

}

TexturedModel::TexturedModel(RawModel* model, ModelTexture* texture)
{
	memcpy(&this->rawModel, model, sizeof(RawModel));
	memcpy(&this->texture, texture, sizeof(ModelTexture));
}

RawModel* TexturedModel::getRawModel()
{
	return &rawModel;
}

ModelTexture* TexturedModel::getTexture()
{
	return &texture;
}

void TexturedModel::deleteMe()
{
	rawModel.deleteMe();
	texture.deleteMe();
}