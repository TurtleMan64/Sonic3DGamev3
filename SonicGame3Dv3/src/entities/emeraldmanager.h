#ifndef EMERALDMANAGER_H
#define EMERALDMANAGER_H

class EmeraldPiece;

#include "entities.h"

class EmeraldManager : public Entity
{
private:
	static EmeraldPiece* piece1;
	static EmeraldPiece* piece2;
	static EmeraldPiece* piece3;
	static int piecesRemaining;
	static int pingTimer;

public:
	EmeraldManager();
	EmeraldManager(int hardMode);

	void step();

	float calcDistToNextPiece();
	
	static void collectPiece(EmeraldPiece* collectedPiece);
};
#endif