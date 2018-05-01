#ifndef EMERALDMANAGER_H
#define EMERALDMANAGER_H

class EmeraldPiece;
class GuiTexture;

#include "entities.h"
#include <glad/glad.h>

class EmeraldManager : public Entity
{
private:
	static EmeraldPiece* piece1;
	static EmeraldPiece* piece2;
	static EmeraldPiece* piece3;
	static int piecesRemaining;
	static int pingTimer;
	static bool hardMode;

	static GLuint radarGreyID;
	static GLuint radarBlueID;
	static GLuint radarGreenID;
	static GLuint radarYellowID;
	static GLuint radarRedID;

	static GuiTexture* radar1;
	static GuiTexture* radar2;
	static GuiTexture* radar3;

	static float calcDistToNextPiece();

	static EmeraldPiece* getNextPiece();

	//Updates radar and returns the current piece radar
	static GuiTexture* updateRadar();

public:
	EmeraldManager();
	EmeraldManager(int hardMode);
	~EmeraldManager();

	void step();
	
	static void collectPiece(EmeraldPiece* collectedPiece);
};
#endif