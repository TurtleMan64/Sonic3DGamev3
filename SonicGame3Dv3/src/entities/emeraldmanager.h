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
	static int pingTimer1;
	static int pingTimer2;
	static int pingTimer3;

	static GLuint radarGreyID;
	static GLuint radarBlueID;
	static GLuint radarGreenID;
	static GLuint radarYellowID;
	static GLuint radarRedID;

	static GuiTexture* radar1;
	static GuiTexture* radar2;
	static GuiTexture* radar3;

	static EmeraldPiece* getClosestPiece();

	static void updatePiece(EmeraldPiece* piece, int* pingTimer, GuiTexture* radar, EmeraldPiece* closestPiece);

public:
	EmeraldManager();
	~EmeraldManager();

	void step();
	
	static void collectPiece(EmeraldPiece* collectedPiece);
};
#endif