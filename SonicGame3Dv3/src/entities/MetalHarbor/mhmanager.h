#ifndef MHMANAGER_H
#define MHMANAGER_H

class TexturedModel;

#include "../entities.h"
#include <list>


class MH_Manager : public Entity
{
private:
	int timer;
	bool playedBGM;

public:
	MH_Manager();

	void step();

	std::list<TexturedModel*>* getModels();
};
#endif