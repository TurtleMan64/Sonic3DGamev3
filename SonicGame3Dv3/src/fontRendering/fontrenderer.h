#ifndef FONTRENDERER_H
#define FONTRENDERER_H

class FontType;
class GUIText;
class FontShader;

#include <unordered_map>

class FontRenderer
{
private:
	FontShader* shader;

	void prepare();

	void renderText(GUIText* text);

	void endRendering();

public:
	FontRenderer();

	void render(std::unordered_map<FontType*, std::list<GUIText*>>* texts);

	void cleanUp();
};

#endif