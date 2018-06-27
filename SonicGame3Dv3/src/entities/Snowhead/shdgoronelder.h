#ifndef SHDGORONELDER_H
#define SHDGORONELDER_H

class TexturedModel;
class GUIText;

#include <list>
#include "../entities.h"
#include <string>

class SHD_GoronElder : public Entity
{
private:
	static std::list<TexturedModel*> models;
	static GUIText* messageGUI1;
	static GUIText* messageGUI2;

	std::string myMessage1[2];
	std::string myMessage2[2];

public:
	SHD_GoronElder();
	SHD_GoronElder(float x, float y, float z, float rotY, std::string messages);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif