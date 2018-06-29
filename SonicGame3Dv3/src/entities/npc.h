#ifndef NPC_H
#define NPC_H

class TexturedModel;
class GUIText;

#include <list>
#include "entities.h"
#include <string>

class NPC : public Entity
{
private:
	static std::list<TexturedModel*> models;
	static GUIText* messageGUI1;
	static GUIText* messageGUI2;

	std::string myMessage1;
	std::string myMessage2;
	bool found;
	int id;

public:
	NPC();
	~NPC();
	NPC(float x, float y, float z, float rotY, int id, std::string message);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif