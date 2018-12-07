#include "emeraldmanager.h"
#include "entities.h"
#include "emeraldpiece.h"
#include "../engineTester/main.h"
#include "../guis/guimanager.h"
#include "../toolbox/maths.h"
#include "../audio/audioplayer.h"
#include "../engineTester/main.h"
#include "../entities/controllableplayer.h"
#include "../toolbox/vector.h"
#include "../entities/camera.h"
#include "../guis/guirenderer.h"
#include "../guis/guitextureresources.h"
#include "../guis/guitexture.h"

#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>

EmeraldPiece* EmeraldManager::piece1 = nullptr;
EmeraldPiece* EmeraldManager::piece2 = nullptr;
EmeraldPiece* EmeraldManager::piece3 = nullptr;
int EmeraldManager::piecesRemaining = 3;
int EmeraldManager::pingTimer1 = 0;
int EmeraldManager::pingTimer2 = 0;
int EmeraldManager::pingTimer3 = 0;

GLuint EmeraldManager::radarGreyID   = 0;
GLuint EmeraldManager::radarBlueID   = 0;
GLuint EmeraldManager::radarGreenID  = 0;
GLuint EmeraldManager::radarYellowID = 0;
GLuint EmeraldManager::radarRedID    = 0;

GuiTexture* EmeraldManager::radar1 = nullptr;
GuiTexture* EmeraldManager::radar2 = nullptr;
GuiTexture* EmeraldManager::radar3 = nullptr;

EmeraldManager::~EmeraldManager()
{
	if (EmeraldManager::radar1 != nullptr)
	{
		GuiManager::removeGui(EmeraldManager::radar1);
		delete EmeraldManager::radar1; INCR_DEL
		EmeraldManager::radar1 = nullptr;
	}
	if (EmeraldManager::radar2 != nullptr)
	{
		GuiManager::removeGui(EmeraldManager::radar2);
		delete EmeraldManager::radar2; INCR_DEL
		EmeraldManager::radar2 = nullptr;
	}
	if (EmeraldManager::radar3 != nullptr)
	{
		GuiManager::removeGui(EmeraldManager::radar3);
		delete EmeraldManager::radar3; INCR_DEL
		EmeraldManager::radar3 = nullptr;
	}

	Loader::deleteTexture(EmeraldManager::radarGreyID);
	Loader::deleteTexture(EmeraldManager::radarBlueID);
	Loader::deleteTexture(EmeraldManager::radarGreenID);
	Loader::deleteTexture(EmeraldManager::radarYellowID);
	Loader::deleteTexture(EmeraldManager::radarRedID);
	
	EmeraldManager::radarGreyID   = 0;
	EmeraldManager::radarBlueID   = 0;
	EmeraldManager::radarGreenID  = 0;
	EmeraldManager::radarYellowID = 0;
	EmeraldManager::radarRedID    = 0;
}

EmeraldManager::EmeraldManager()
{
	//Load images of radar
	EmeraldManager::radarGreyID   = Loader::loadTexture("res/Images/TreasureHunting/RadarGrey.png");
	EmeraldManager::radarBlueID   = Loader::loadTexture("res/Images/TreasureHunting/RadarBlue.png");
	EmeraldManager::radarGreenID  = Loader::loadTexture("res/Images/TreasureHunting/RadarGreen.png");
	EmeraldManager::radarYellowID = Loader::loadTexture("res/Images/TreasureHunting/RadarYellow.png");
	EmeraldManager::radarRedID    = Loader::loadTexture("res/Images/TreasureHunting/RadarRed.png");

	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;

	float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension
	float py = 1.0f/(SCR_HEIGHT); //1 pixel in y dimension

	//Create Radar gui textures
	EmeraldManager::radar1 = new GuiTexture(EmeraldManager::radarGreyID, 0.5f-48*px, 1-32*py, 32*px, 32*py, 0); INCR_NEW
	EmeraldManager::radar2 = new GuiTexture(EmeraldManager::radarGreyID, 0.5f,       1-32*py, 32*px, 32*py, 0); INCR_NEW
	EmeraldManager::radar3 = new GuiTexture(EmeraldManager::radarGreyID, 0.5f+48*px, 1-32*py, 32*px, 32*py, 0); INCR_NEW
	GuiManager::addGuiToRender(EmeraldManager::radar1);
	GuiManager::addGuiToRender(EmeraldManager::radar2);
	GuiManager::addGuiToRender(EmeraldManager::radar3);

	std::vector<EmeraldPiece*> piece1List;
	std::vector<EmeraldPiece*> piece2List;
	std::vector<EmeraldPiece*> piece3List;

	int totalPieces = 0;
	EmeraldManager::pingTimer1 = 0;
	EmeraldManager::pingTimer2 = 0;
	EmeraldManager::pingTimer3 = 0;
	EmeraldManager::piece1 = nullptr;
	EmeraldManager::piece2 = nullptr;
	EmeraldManager::piece3 = nullptr;

	visible = false;

	extern std::list<Entity*> gameEntitiesPass2ToAdd;

	for (Entity* e : gameEntitiesPass2ToAdd)
	{
		if (e->isEmeraldPiece()) 
		{
			EmeraldPiece* piece = (EmeraldPiece*)e;
			if (Global::gameIsNormalMode)
			{
				if (piece->isHardModePiece())
				{
					Main_deleteEntityPass2(piece);
				}
				else
				{
					totalPieces++;
					switch (piece->getPieceNumber())
					{
						case 1:  piece1List.push_back(piece); break;
						case 2:  piece2List.push_back(piece); break;
						default: piece3List.push_back(piece); break;
					}
				}
			}
			else if (Global::gameIsHardMode)
			{
				if (piece->isHardModePiece())
				{
					totalPieces++;
				}
				else
				{
					Main_deleteEntityPass2(piece);
				}
			}
		}
	}

	if (Global::gameIsHardMode)
	{
		EmeraldManager::piecesRemaining = totalPieces;

		EmeraldManager::radar1->setVisible(false);
		EmeraldManager::radar2->setVisible(false);
		EmeraldManager::radar3->setVisible(false);
	}
	else if (Global::gameIsNormalMode)
	{
		//Pick a random p1
		EmeraldManager::piece1 = piece1List[(int)(Maths::random()*piece1List.size())];
		Vector3f p1Loc(EmeraldManager::piece1->getPosition());

		//Calculate distances from p1 to p2
		std::vector<float> distTo2;
		for (EmeraldPiece* piece : piece2List)
		{
			Vector3f p2Loc(piece->getPosition());
			Vector3f diff = p1Loc - p2Loc;
			float dist = diff.lengthSquared();

			distTo2.push_back(dist);
		}

		//Get the minimum distance needed to be a valid p2
		std::sort(distTo2.begin(), distTo2.end());
		float minDist = distTo2[distTo2.size()/2];

		//Generate valid p2's
		std::vector<EmeraldPiece*> validP2s;
		for (EmeraldPiece* piece : piece2List)
		{
			Vector3f p2Loc(piece->getPosition());
			Vector3f diff = p1Loc - p2Loc;
			float dist = diff.lengthSquared();

			if (dist >= minDist)
			{
				validP2s.push_back(piece);
			}
		}

		//Pick a random p2
		EmeraldManager::piece2 = validP2s[(int)(Maths::random()*validP2s.size())];
		Vector3f p2Loc(EmeraldManager::piece2->getPosition());
		Vector3f diff = p1Loc - p2Loc;

		//Calculate cross products to p3's
		std::vector<float> crossProducts;
		for (EmeraldPiece* piece : piece3List)
		{
			float cp = (diff.cross(piece->getPosition())).lengthSquared();

			crossProducts.push_back(cp);
		}

		//Get the minimum area needed to be a valid p3
		std::sort(crossProducts.begin(), crossProducts.end());
		float minCP = crossProducts[crossProducts.size()/2];

		//Generate valid p3's
		std::vector<EmeraldPiece*> validP3s;
		for (EmeraldPiece* piece : piece3List)
		{
			float cp = (diff.cross(piece->getPosition())).lengthSquared();

			if (cp >= minCP)
			{
				validP3s.push_back(piece);
			}
		}

		//Pick a random p3
		EmeraldManager::piece3 = validP3s[(int)(Maths::random()*validP3s.size())];

		EmeraldManager::piecesRemaining = 3;

		//Delete all the other pieces
		for (EmeraldPiece* piece : piece1List)
		{
			if (piece != EmeraldManager::piece1)
			{
				Main_deleteEntityPass2(piece);
			}
		}
		for (EmeraldPiece* piece : piece2List)
		{
			if (piece != EmeraldManager::piece2)
			{
				Main_deleteEntityPass2(piece);
			}
		}
		for (EmeraldPiece* piece : piece3List)
		{
			if (piece != EmeraldManager::piece3)
			{
				Main_deleteEntityPass2(piece);
			}
		}
	}
	else
	{
		for (Entity* e : gameEntitiesPass2ToAdd)
		{
			if (e->isEmeraldPiece()) 
			{
				EmeraldPiece* piece = (EmeraldPiece*)e;
				Main_deleteEntityPass2(piece);
			}
		}

		EmeraldManager::radar1->setVisible(false);
		EmeraldManager::radar2->setVisible(false);
		EmeraldManager::radar3->setVisible(false);
	}
}

void EmeraldManager::updatePiece(EmeraldPiece* piece, int* pingTimer, GuiTexture* radar, EmeraldPiece* closestPiece)
{
	if (piece == nullptr)
	{
		radar->setVisible(false);
		return;
	}
	radar->setTexture(EmeraldManager::radarGreyID);
	radar->setScale(1);

	Vector3f pieceLoc(piece->getPosition());
	Vector3f playerLoc(Global::gamePlayer->getPosition());
	float distToPiece =  (pieceLoc-playerLoc).length();

	if (*pingTimer == 1 && piece == closestPiece)
	{
			//Play the sound in the direction to the piece from the camera
			Vector3f diff(piece->getPosition());
			diff = diff - Global::gameCamera->getPosition();
			diff.scale(0.25f);

			Vector3f pingPosition(Global::gameCamera->getPosition());
			pingPosition = pingPosition + diff;

			AudioPlayer::play(34, &pingPosition);
	}
	*pingTimer = std::max(0, *pingTimer-1);

	if (distToPiece >= 600 && distToPiece < 1000)
	{
		if (*pingTimer == 0)
		{
			*pingTimer = 60;
		}
		radar->setTexture(EmeraldManager::radarBlueID);
		radar->setScale(1+0.5f*(*pingTimer/60.0f));
	}
	else if (distToPiece >= 200 && distToPiece < 600)
	{
		if (*pingTimer == 0)
		{
			*pingTimer = 30;
		}
		radar->setTexture(EmeraldManager::radarGreenID);
		radar->setScale(1+0.5f*(*pingTimer/30.0f));
	}
	else if (distToPiece >= 50 && distToPiece < 200)
	{
		if (*pingTimer == 0)
		{
			*pingTimer = 15;
		}
		radar->setTexture(EmeraldManager::radarYellowID);
		radar->setScale(1+0.5f*(*pingTimer/15.0f));
	}
	else if (distToPiece >= 0 && distToPiece < 50)
	{
		if (*pingTimer == 0)
		{
			*pingTimer = 12;
		}
		radar->setTexture(EmeraldManager::radarRedID);
		radar->setScale(1+0.5f*(*pingTimer/12.0f));
	}
}

void EmeraldManager::step()
{
	if (Global::gameIsChaoMode || Global::gameIsRingMode)
	{
		return;
	}
	EmeraldPiece* closestPiece = EmeraldManager::getClosestPiece();
	EmeraldManager::updatePiece(EmeraldManager::piece1, &EmeraldManager::pingTimer1, EmeraldManager::radar1, closestPiece);
	EmeraldManager::updatePiece(EmeraldManager::piece2, &EmeraldManager::pingTimer2, EmeraldManager::radar2, closestPiece);
	EmeraldManager::updatePiece(EmeraldManager::piece3, &EmeraldManager::pingTimer3, EmeraldManager::radar3, closestPiece);
}

EmeraldPiece* EmeraldManager::getClosestPiece()
{
	EmeraldPiece* pieceToReturn = nullptr;
	float closestDist = 1000000000.0f;

	if (EmeraldManager::piece1 != nullptr)
	{
		Vector3f pieceLoc(EmeraldManager::piece1->getPosition());
		Vector3f playerLoc(Global::gamePlayer->getPosition());
		float distToPiece =  (pieceLoc-playerLoc).length();
		if (distToPiece < closestDist)
		{
			pieceToReturn = EmeraldManager::piece1;
			closestDist = distToPiece;
		}
	}
	if (EmeraldManager::piece2 != nullptr)
	{
		Vector3f pieceLoc(EmeraldManager::piece2->getPosition());
		Vector3f playerLoc(Global::gamePlayer->getPosition());
		float distToPiece =  (pieceLoc-playerLoc).length();
		if (distToPiece < closestDist)
		{
			pieceToReturn = EmeraldManager::piece2;
			closestDist = distToPiece;
		}
	}
	if (EmeraldManager::piece3 != nullptr)
	{
		Vector3f pieceLoc(EmeraldManager::piece3->getPosition());
		Vector3f playerLoc(Global::gamePlayer->getPosition());
		float distToPiece =  (pieceLoc-playerLoc).length();
		if (distToPiece < closestDist)
		{
			pieceToReturn = EmeraldManager::piece3;
			closestDist = distToPiece;
		}
	}
	return pieceToReturn;
}

void EmeraldManager::collectPiece(EmeraldPiece* collectedPiece)
{
	if (collectedPiece == EmeraldManager::piece1)
	{
		EmeraldManager::piece1 = nullptr;
	}
	else if (collectedPiece == EmeraldManager::piece2)
	{
		EmeraldManager::piece2 = nullptr;
	}
	else if (collectedPiece == EmeraldManager::piece3)
	{
		EmeraldManager::piece3 = nullptr;
	}

	EmeraldManager::piecesRemaining--;

	if (EmeraldManager::piecesRemaining <= 0)
	{
		GuiManager::stopTimer();

		Global::finishStageTimer = 0;
	}
}
