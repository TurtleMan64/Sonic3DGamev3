#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "maniasonicmodel.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../toolbox/maths.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*>* ManiaSonicModel::models;

std::list<TexturedModel*> ManiaSonicModel::modelDash0;
std::list<TexturedModel*> ManiaSonicModel::modelDash1;
std::list<TexturedModel*> ManiaSonicModel::modelDash2;
std::list<TexturedModel*> ManiaSonicModel::modelDash3;
std::list<TexturedModel*> ManiaSonicModel::modelDash4;
std::list<TexturedModel*> ManiaSonicModel::modelDash5;
std::list<TexturedModel*> ManiaSonicModel::modelDash6;
std::list<TexturedModel*> ManiaSonicModel::modelDash7;
std::list<TexturedModel*> ManiaSonicModel::modelDash8;
std::list<TexturedModel*> ManiaSonicModel::modelDash9;
std::list<TexturedModel*> ManiaSonicModel::modelDash10;
std::list<TexturedModel*> ManiaSonicModel::modelDash11;
std::list<TexturedModel*> ManiaSonicModel::modelJump;
std::list<TexturedModel*> ManiaSonicModel::modelJog0;
std::list<TexturedModel*> ManiaSonicModel::modelJog1;
std::list<TexturedModel*> ManiaSonicModel::modelJog2;
std::list<TexturedModel*> ManiaSonicModel::modelJog3;
std::list<TexturedModel*> ManiaSonicModel::modelJog4;
std::list<TexturedModel*> ManiaSonicModel::modelJog5;
std::list<TexturedModel*> ManiaSonicModel::modelJog6;
std::list<TexturedModel*> ManiaSonicModel::modelJog7;
std::list<TexturedModel*> ManiaSonicModel::modelJog8;
std::list<TexturedModel*> ManiaSonicModel::modelJog9;
std::list<TexturedModel*> ManiaSonicModel::modelJog10;
std::list<TexturedModel*> ManiaSonicModel::modelJog11;
std::list<TexturedModel*> ManiaSonicModel::modelJog12;
std::list<TexturedModel*> ManiaSonicModel::modelJog13;
std::list<TexturedModel*> ManiaSonicModel::modelJog14;
std::list<TexturedModel*> ManiaSonicModel::modelJog15;
std::list<TexturedModel*> ManiaSonicModel::modelJog16;
std::list<TexturedModel*> ManiaSonicModel::modelJog17;

ManiaSonicModel::ManiaSonicModel()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->scale = 0.33f;
	this->visible = false;
	ManiaSonicModel::models = nullptr;
}

void ManiaSonicModel::step()
{

}

void ManiaSonicModel::animate(int animIndex, float time)
{
	setScale(0.33f);
	switch (animIndex)
	{
		case 1: //run
		{
			int index = (int)(time / 8.3333333f);
			switch (index)
			{
				case 0:  ManiaSonicModel::models = &ManiaSonicModel::modelDash0;  break;
				case 1:  ManiaSonicModel::models = &ManiaSonicModel::modelDash1;  break;
				case 2:  ManiaSonicModel::models = &ManiaSonicModel::modelDash2;  break;
				case 3:  ManiaSonicModel::models = &ManiaSonicModel::modelDash3;  break;
				case 4:  ManiaSonicModel::models = &ManiaSonicModel::modelDash4;  break;
				case 5:  ManiaSonicModel::models = &ManiaSonicModel::modelDash5;  break;
				case 6:  ManiaSonicModel::models = &ManiaSonicModel::modelDash6;  break;
				case 7:  ManiaSonicModel::models = &ManiaSonicModel::modelDash7;  break;
				case 8:  ManiaSonicModel::models = &ManiaSonicModel::modelDash8;  break;
				case 9:  ManiaSonicModel::models = &ManiaSonicModel::modelDash9;  break;
				case 10: ManiaSonicModel::models = &ManiaSonicModel::modelDash10; break;
				case 11: ManiaSonicModel::models = &ManiaSonicModel::modelDash11; break;
				default: break;
			}
			break;
		}

		case 12: //jump
		{
			ManiaSonicModel::models = &ManiaSonicModel::modelJump;
			setScale(0.40f);
			break;
		}

		case 15: //jog
		{
			int index = (int)(time / 5.55555555f);
			switch (index)
			{
				case 0:  ManiaSonicModel::models = &ManiaSonicModel::modelJog0;  break;
				case 1:  ManiaSonicModel::models = &ManiaSonicModel::modelJog1;  break;
				case 2:  ManiaSonicModel::models = &ManiaSonicModel::modelJog2;  break;
				case 3:  ManiaSonicModel::models = &ManiaSonicModel::modelJog3;  break;
				case 4:  ManiaSonicModel::models = &ManiaSonicModel::modelJog4;  break;
				case 5:  ManiaSonicModel::models = &ManiaSonicModel::modelJog5;  break;
				case 6:  ManiaSonicModel::models = &ManiaSonicModel::modelJog6;  break;
				case 7:  ManiaSonicModel::models = &ManiaSonicModel::modelJog7;  break;
				case 8:  ManiaSonicModel::models = &ManiaSonicModel::modelJog8;  break;
				case 9:  ManiaSonicModel::models = &ManiaSonicModel::modelJog9;  break;
				case 10: ManiaSonicModel::models = &ManiaSonicModel::modelJog10; break;
				case 11: ManiaSonicModel::models = &ManiaSonicModel::modelJog11; break;
				case 12: ManiaSonicModel::models = &ManiaSonicModel::modelJog12; break;
				case 13: ManiaSonicModel::models = &ManiaSonicModel::modelJog13; break;
				case 14: ManiaSonicModel::models = &ManiaSonicModel::modelJog14; break;
				case 15: ManiaSonicModel::models = &ManiaSonicModel::modelJog15; break;
				case 16: ManiaSonicModel::models = &ManiaSonicModel::modelJog16; break;
				case 17: ManiaSonicModel::models = &ManiaSonicModel::modelJog17; break;
				default: break;
			}
			break;
		}

		default:
			break;
	}
	updateTransformationMatrix();
}

void ManiaSonicModel::setOrientation(float x, float y, float z, float xRot, float yRot, float zRot, float spinRot)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	setRotX(xRot);
	setRotY(yRot);
	setRotZ(zRot);
	setRotSpin(spinRot);
}

std::list<TexturedModel*>* ManiaSonicModel::getModels()
{
	return ManiaSonicModel::models;
}

void ManiaSonicModel::loadStaticModels()
{
	if (ManiaSonicModel::modelDash0.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading mania sonic static models...\n");
	#endif

	loadObjModel(&ManiaSonicModel::modelDash0 , "res/Models/ManiaSonic/", "Dash0.obj");
	loadObjModel(&ManiaSonicModel::modelDash1 , "res/Models/ManiaSonic/", "Dash1.obj");
	loadObjModel(&ManiaSonicModel::modelDash2 , "res/Models/ManiaSonic/", "Dash2.obj");
	loadObjModel(&ManiaSonicModel::modelDash3 , "res/Models/ManiaSonic/", "Dash3.obj");
	loadObjModel(&ManiaSonicModel::modelDash4 , "res/Models/ManiaSonic/", "Dash4.obj");
	loadObjModel(&ManiaSonicModel::modelDash5 , "res/Models/ManiaSonic/", "Dash5.obj");
	loadObjModel(&ManiaSonicModel::modelDash6 , "res/Models/ManiaSonic/", "Dash6.obj");
	loadObjModel(&ManiaSonicModel::modelDash7 , "res/Models/ManiaSonic/", "Dash7.obj");
	loadObjModel(&ManiaSonicModel::modelDash8 , "res/Models/ManiaSonic/", "Dash8.obj");
	loadObjModel(&ManiaSonicModel::modelDash9 , "res/Models/ManiaSonic/", "Dash9.obj");
	loadObjModel(&ManiaSonicModel::modelDash10, "res/Models/ManiaSonic/", "Dash10.obj");
	loadObjModel(&ManiaSonicModel::modelDash11, "res/Models/ManiaSonic/", "Dash11.obj");
	loadObjModel(&ManiaSonicModel::modelJump  , "res/Models/ManiaSonic/", "Jump.obj");
	loadObjModel(&ManiaSonicModel::modelJog0  , "res/Models/ManiaSonic/", "Jog0.obj");
	loadObjModel(&ManiaSonicModel::modelJog1  , "res/Models/ManiaSonic/", "Jog1.obj");
	loadObjModel(&ManiaSonicModel::modelJog2  , "res/Models/ManiaSonic/", "Jog2.obj");
	loadObjModel(&ManiaSonicModel::modelJog3  , "res/Models/ManiaSonic/", "Jog3.obj");
	loadObjModel(&ManiaSonicModel::modelJog4  , "res/Models/ManiaSonic/", "Jog4.obj");
	loadObjModel(&ManiaSonicModel::modelJog5  , "res/Models/ManiaSonic/", "Jog5.obj");
	loadObjModel(&ManiaSonicModel::modelJog6  , "res/Models/ManiaSonic/", "Jog6.obj");
	loadObjModel(&ManiaSonicModel::modelJog7  , "res/Models/ManiaSonic/", "Jog7.obj");
	loadObjModel(&ManiaSonicModel::modelJog8  , "res/Models/ManiaSonic/", "Jog8.obj");
	loadObjModel(&ManiaSonicModel::modelJog9  , "res/Models/ManiaSonic/", "Jog9.obj");
	loadObjModel(&ManiaSonicModel::modelJog10 , "res/Models/ManiaSonic/", "Jog10.obj");
	loadObjModel(&ManiaSonicModel::modelJog11 , "res/Models/ManiaSonic/", "Jog11.obj");
	loadObjModel(&ManiaSonicModel::modelJog12 , "res/Models/ManiaSonic/", "Jog12.obj");
	loadObjModel(&ManiaSonicModel::modelJog13 , "res/Models/ManiaSonic/", "Jog13.obj");
	loadObjModel(&ManiaSonicModel::modelJog14 , "res/Models/ManiaSonic/", "Jog14.obj");
	loadObjModel(&ManiaSonicModel::modelJog15 , "res/Models/ManiaSonic/", "Jog15.obj");
	loadObjModel(&ManiaSonicModel::modelJog16 , "res/Models/ManiaSonic/", "Jog16.obj");
	loadObjModel(&ManiaSonicModel::modelJog17 , "res/Models/ManiaSonic/", "Jog17.obj");

}

void ManiaSonicModel::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting mania sonic static models...\n");
	#endif

	Entity::deleteModels(&ManiaSonicModel::modelDash0);
	Entity::deleteModels(&ManiaSonicModel::modelDash1);
	Entity::deleteModels(&ManiaSonicModel::modelDash2);
	Entity::deleteModels(&ManiaSonicModel::modelDash3);
	Entity::deleteModels(&ManiaSonicModel::modelDash4);
	Entity::deleteModels(&ManiaSonicModel::modelDash5);
	Entity::deleteModels(&ManiaSonicModel::modelDash6);
	Entity::deleteModels(&ManiaSonicModel::modelDash7);
	Entity::deleteModels(&ManiaSonicModel::modelDash8);
	Entity::deleteModels(&ManiaSonicModel::modelDash9);
	Entity::deleteModels(&ManiaSonicModel::modelDash10);
	Entity::deleteModels(&ManiaSonicModel::modelDash11);
	Entity::deleteModels(&ManiaSonicModel::modelJump);
	Entity::deleteModels(&ManiaSonicModel::modelJog0);
	Entity::deleteModels(&ManiaSonicModel::modelJog1);
	Entity::deleteModels(&ManiaSonicModel::modelJog2);
	Entity::deleteModels(&ManiaSonicModel::modelJog3);
	Entity::deleteModels(&ManiaSonicModel::modelJog4);
	Entity::deleteModels(&ManiaSonicModel::modelJog5);
	Entity::deleteModels(&ManiaSonicModel::modelJog6);
	Entity::deleteModels(&ManiaSonicModel::modelJog7);
	Entity::deleteModels(&ManiaSonicModel::modelJog8);
	Entity::deleteModels(&ManiaSonicModel::modelJog9);
	Entity::deleteModels(&ManiaSonicModel::modelJog10);
	Entity::deleteModels(&ManiaSonicModel::modelJog11);
	Entity::deleteModels(&ManiaSonicModel::modelJog12);
	Entity::deleteModels(&ManiaSonicModel::modelJog13);
	Entity::deleteModels(&ManiaSonicModel::modelJog14);
	Entity::deleteModels(&ManiaSonicModel::modelJog15);
	Entity::deleteModels(&ManiaSonicModel::modelJog16);
	Entity::deleteModels(&ManiaSonicModel::modelJog17);

	ManiaSonicModel::models = nullptr;
}
