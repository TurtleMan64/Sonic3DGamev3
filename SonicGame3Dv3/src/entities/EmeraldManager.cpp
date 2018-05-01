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
int EmeraldManager::pingTimer = 0;
bool EmeraldManager::hardMode = false;

GLuint EmeraldManager::radarGreyID   = 0;
GLuint EmeraldManager::radarBlueID   = 0;
GLuint EmeraldManager::radarGreenID  = 0;
GLuint EmeraldManager::radarYellowID = 0;
GLuint EmeraldManager::radarRedID    = 0;

GuiTexture* EmeraldManager::radar1 = nullptr;
GuiTexture* EmeraldManager::radar2 = nullptr;
GuiTexture* EmeraldManager::radar3 = nullptr;

EmeraldManager::EmeraldManager()
{
	
}

EmeraldManager::~EmeraldManager()
{
	if (EmeraldManager::radar1 != nullptr)
	{
		GuiManager::removeGui(EmeraldManager::radar1);
		delete EmeraldManager::radar1; Global::countDelete++;
		EmeraldManager::radar1 = nullptr;
	}
	if (EmeraldManager::radar2 != nullptr)
	{
		GuiManager::removeGui(EmeraldManager::radar2);
		delete EmeraldManager::radar2; Global::countDelete++;
		EmeraldManager::radar2 = nullptr;
	}
	if (EmeraldManager::radar3 != nullptr)
	{
		GuiManager::removeGui(EmeraldManager::radar3);
		delete EmeraldManager::radar3; Global::countDelete++;
		EmeraldManager::radar3 = nullptr;
	}

	Loader_deleteTexture(EmeraldManager::radarGreyID);
	Loader_deleteTexture(EmeraldManager::radarBlueID);
	Loader_deleteTexture(EmeraldManager::radarGreenID);
	Loader_deleteTexture(EmeraldManager::radarYellowID);
	Loader_deleteTexture(EmeraldManager::radarRedID);
	
	EmeraldManager::radarGreyID   = 0;
	EmeraldManager::radarBlueID   = 0;
	EmeraldManager::radarGreenID  = 0;
	EmeraldManager::radarYellowID = 0;
	EmeraldManager::radarRedID    = 0;
}

EmeraldManager::EmeraldManager(int doHardMode)
{
	//Load images of radar
	EmeraldManager::radarGreyID   = Loader_loadTexture("res/Images/RadarGrey.png");
	EmeraldManager::radarBlueID   = Loader_loadTexture("res/Images/RadarBlue.png");
	EmeraldManager::radarGreenID  = Loader_loadTexture("res/Images/RadarGreen.png");
	EmeraldManager::radarYellowID = Loader_loadTexture("res/Images/RadarYellow.png");
	EmeraldManager::radarRedID    = Loader_loadTexture("res/Images/RadarRed.png");

	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;

	float px = 1.0f/(SCR_WIDTH);  //1 pixel in x dimension
	float py = 1.0f/(SCR_HEIGHT); //1 pixel in y dimension

	//Create Radar gui textures
	EmeraldManager::radar1 = new GuiTexture(EmeraldManager::radarGreyID, 0.5f-48*px, 1-32*py, 32*px, 32*py); Global::countNew++;
	EmeraldManager::radar2 = new GuiTexture(EmeraldManager::radarGreyID, 0.5f,       1-32*py, 32*px, 32*py); Global::countNew++;
	EmeraldManager::radar3 = new GuiTexture(EmeraldManager::radarGreyID, 0.5f+48*px, 1-32*py, 32*px, 32*py); Global::countNew++;
	GuiManager::addGuiToRender(EmeraldManager::radar1);
	GuiManager::addGuiToRender(EmeraldManager::radar2);
	GuiManager::addGuiToRender(EmeraldManager::radar3);

	std::vector<EmeraldPiece*> piece1List;
	std::vector<EmeraldPiece*> piece2List;
	std::vector<EmeraldPiece*> piece3List;

	int totalPieces = 0;
	EmeraldManager::pingTimer = 0;
	EmeraldManager::piece1 = nullptr;
	EmeraldManager::piece2 = nullptr;
	EmeraldManager::piece3 = nullptr;

	visible = false;

	extern std::unordered_map<Entity*, Entity*> gameEntitiesPass2;

	for (auto e : gameEntitiesPass2)
	{
		if (e.first->isEmeraldPiece()) 
		{
			EmeraldPiece* piece = (EmeraldPiece*)e.first;
			totalPieces++;
			switch (piece->getPieceNumber())
			{
			case 1:
				piece1List.push_back(piece);
				break;

			case 2:
				piece2List.push_back(piece);
				break;

			default:
				piece3List.push_back(piece);
				break;
			}
		}
	}

	if (doHardMode != 0)
	{
		EmeraldManager::piecesRemaining = totalPieces;
		EmeraldManager::hardMode = true;
	}
	else
	{
		EmeraldManager::hardMode = false;

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
}

void EmeraldManager::step()
{
	//make ping sounds, update radar
	GuiTexture* nextRadar = EmeraldManager::updateRadar();
	if (nextRadar != nullptr)
	{
		nextRadar->setTexture(EmeraldManager::radarGreyID);
	}

	float distToPiece = EmeraldManager::calcDistToNextPiece();

	if (EmeraldManager::pingTimer == 1)
	{
		EmeraldPiece* nextPiece = EmeraldManager::getNextPiece();
		if (nextPiece != nullptr)
		{
			//Play the sound in the direction to the piece from the camera
			Vector3f diff(nextPiece->getPosition());
			diff = diff - Global::gameCamera->getPosition();
			diff.scale(0.25f);

			Vector3f pingPosition(Global::gameCamera->getPosition());
			pingPosition = pingPosition + diff;

			AudioPlayer::play(34, &pingPosition);
		}
	}
	EmeraldManager::pingTimer = std::max(0, EmeraldManager::pingTimer-1);

	if (distToPiece >= 600 && distToPiece < 1000)
	{
		if (EmeraldManager::pingTimer == 0)
		{
			EmeraldManager::pingTimer = 60;
		}
		if (nextRadar != nullptr)
		{
			nextRadar->setTexture(EmeraldManager::radarBlueID);
			nextRadar->setScale(1+0.5f*(EmeraldManager::pingTimer/60.0f));
		}
	}
	else if (distToPiece >= 200 && distToPiece < 600)
	{
		if (EmeraldManager::pingTimer == 0)
		{
			EmeraldManager::pingTimer = 30;
		}
		if (nextRadar != nullptr)
		{
			nextRadar->setTexture(EmeraldManager::radarGreenID);
			nextRadar->setScale(1+0.5f*(EmeraldManager::pingTimer/30.0f));
		}
	}
	else if (distToPiece >= 50 && distToPiece < 200)
	{
		if (EmeraldManager::pingTimer == 0)
		{
			EmeraldManager::pingTimer = 15;
		}
		if (nextRadar != nullptr)
		{
			nextRadar->setTexture(EmeraldManager::radarYellowID);
			nextRadar->setScale(1+0.5f*(EmeraldManager::pingTimer/15.0f));
		}
	}
	else if (distToPiece >= 0 && distToPiece < 50)
	{
		if (EmeraldManager::pingTimer == 0)
		{
			EmeraldManager::pingTimer = 12;
		}
		if (nextRadar != nullptr)
		{
			nextRadar->setTexture(EmeraldManager::radarRedID);
			nextRadar->setScale(1+0.5f*(EmeraldManager::pingTimer/12.0f));
		}
	}
}

EmeraldPiece* EmeraldManager::getNextPiece()
{
	if (EmeraldManager::piece1 != nullptr)
	{
		return EmeraldManager::piece1;
	}
	else if (EmeraldManager::piece2 != nullptr)
	{
		return EmeraldManager::piece2;
	}

	return EmeraldManager::piece3;
}

float EmeraldManager::calcDistToNextPiece()
{
	EmeraldPiece* nextPiece = EmeraldManager::getNextPiece();
	if (nextPiece != nullptr)
	{
		Vector3f pieceLoc(nextPiece->getPosition());
		Vector3f playerLoc(Global::gamePlayer->getPosition());
		return (pieceLoc-playerLoc).length();
	}
	return 1000000.0f;
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

GuiTexture* EmeraldManager::updateRadar()
{
	if (EmeraldManager::piece1 == nullptr)
	{
		EmeraldManager::radar1->setVisible(false);
	}
	if (EmeraldManager::piece2 == nullptr)
	{
		EmeraldManager::radar2->setVisible(false);
	}
	if (EmeraldManager::piece3 == nullptr)
	{
		EmeraldManager::radar3->setVisible(false);
	}

	if (EmeraldManager::piece1 != nullptr)
	{
		return EmeraldManager::radar1;
	}
	else if (EmeraldManager::piece2 != nullptr)
	{
		return EmeraldManager::radar2;
	}

	return EmeraldManager::radar3;
}