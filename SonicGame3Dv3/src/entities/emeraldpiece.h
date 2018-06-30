#ifndef EMERALDPIECE_H
#define EMERALDPIECE_H

class TexturedModel;

#include <list>
#include "entities.h"

class EmeraldPiece : public Entity
{
private:
	static std::list<TexturedModel*> models;

	static float hitboxH;
	static float hitboxV;
	
	int pieceNumber; //1, 2 or 3

	bool isDiggable;
	float digSizeX;
	float digSizeY;
	float digSizeZ;

public:
	EmeraldPiece();
	EmeraldPiece(
		float x, float y, float z, 
		int pieceNumber, int isDiggable, 
		float digSizeX, float digSizeY, float digSizeZ);

	void step();

	bool isEmeraldPiece();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
	
	int getPieceNumber();
};
#endif