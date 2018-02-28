#ifndef TEXTMASTER_H
#define TEXTMASTER_H

class FontType;
class GUIText;
class FontRenderer;
class Matrix4f;

#include <list>

#include <unordered_map>

class TextMaster
{
private:
	static std::unordered_map<FontType*, std::list<GUIText*>> texts;
	static FontRenderer* renderer;

	TextMaster();

public:
	static void init();

	static void render();

	static void loadText(GUIText* text);

	static void removeText(GUIText* text);

	static void cleanUp();
};

#endif