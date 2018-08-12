#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "maniatailsmodel.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../toolbox/maths.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> ManiaTailsModel::modelDash0;
std::list<TexturedModel*> ManiaTailsModel::modelDash1;
std::list<TexturedModel*> ManiaTailsModel::modelDash2;
std::list<TexturedModel*> ManiaTailsModel::modelDash3;
std::list<TexturedModel*> ManiaTailsModel::modelDash4;
std::list<TexturedModel*> ManiaTailsModel::modelDash5;
std::list<TexturedModel*> ManiaTailsModel::modelDash6;
std::list<TexturedModel*> ManiaTailsModel::modelDash7;
std::list<TexturedModel*> ManiaTailsModel::modelDash8;
std::list<TexturedModel*> ManiaTailsModel::modelDash9;
std::list<TexturedModel*> ManiaTailsModel::modelDash10;
std::list<TexturedModel*> ManiaTailsModel::modelDash11;
std::list<TexturedModel*> ManiaTailsModel::modelDash12;
std::list<TexturedModel*> ManiaTailsModel::modelDash13;
std::list<TexturedModel*> ManiaTailsModel::modelDash14;
std::list<TexturedModel*> ManiaTailsModel::modelDash15;
std::list<TexturedModel*> ManiaTailsModel::modelDash16;
std::list<TexturedModel*> ManiaTailsModel::modelDash17;
std::list<TexturedModel*> ManiaTailsModel::modelJump;
std::list<TexturedModel*> ManiaTailsModel::modelJog0;
std::list<TexturedModel*> ManiaTailsModel::modelJog1;
std::list<TexturedModel*> ManiaTailsModel::modelJog2;
std::list<TexturedModel*> ManiaTailsModel::modelJog3;
std::list<TexturedModel*> ManiaTailsModel::modelJog4;
std::list<TexturedModel*> ManiaTailsModel::modelJog5;
std::list<TexturedModel*> ManiaTailsModel::modelJog6;
std::list<TexturedModel*> ManiaTailsModel::modelJog7;
std::list<TexturedModel*> ManiaTailsModel::modelJog8;
std::list<TexturedModel*> ManiaTailsModel::modelJog9;
std::list<TexturedModel*> ManiaTailsModel::modelJog10;
std::list<TexturedModel*> ManiaTailsModel::modelJog11;
std::list<TexturedModel*> ManiaTailsModel::modelJog12;
std::list<TexturedModel*> ManiaTailsModel::modelJog13;
std::list<TexturedModel*> ManiaTailsModel::modelJog14;
std::list<TexturedModel*> ManiaTailsModel::modelJog15;
std::list<TexturedModel*> ManiaTailsModel::modelJog16;
std::list<TexturedModel*> ManiaTailsModel::modelJog17;

ManiaTailsModel::ManiaTailsModel()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 0.355f;
	visible = false;
	models = nullptr;
}

void ManiaTailsModel::step()
{

}

void ManiaTailsModel::animate(int animIndex, float time)
{
	setScale(0.355f);
	switch (animIndex)
	{
		case 1: //run
		{
			int index = (int)(time / 5.55555555f);
			switch (index)
			{
				case 0:  models = &ManiaTailsModel::modelDash0;  break;
				case 1:  models = &ManiaTailsModel::modelDash1;  break;
				case 2:  models = &ManiaTailsModel::modelDash2;  break;
				case 3:  models = &ManiaTailsModel::modelDash3;  break;
				case 4:  models = &ManiaTailsModel::modelDash4;  break;
				case 5:  models = &ManiaTailsModel::modelDash5;  break;
				case 6:  models = &ManiaTailsModel::modelDash6;  break;
				case 7:  models = &ManiaTailsModel::modelDash7;  break;
				case 8:  models = &ManiaTailsModel::modelDash8;  break;
				case 9:  models = &ManiaTailsModel::modelDash9;  break;
				case 10: models = &ManiaTailsModel::modelDash10; break;
				case 11: models = &ManiaTailsModel::modelDash11; break;
				case 12: models = &ManiaTailsModel::modelDash12; break;
				case 13: models = &ManiaTailsModel::modelDash13; break;
				case 14: models = &ManiaTailsModel::modelDash14; break;
				case 15: models = &ManiaTailsModel::modelDash15; break;
				case 16: models = &ManiaTailsModel::modelDash16; break;
				case 17: models = &ManiaTailsModel::modelDash17; break;
				default: break;
			}
			break;
		}

		case 12: //jump
		{
			models = &ManiaTailsModel::modelJump;
			setScale(0.42f);
			break;
		}

		case 15: //jog
		{
			int index = (int)(time / 5.55555555f);
			switch (index)
			{
				case 0:  models = &ManiaTailsModel::modelJog0;  break;
				case 1:  models = &ManiaTailsModel::modelJog1;  break;
				case 2:  models = &ManiaTailsModel::modelJog2;  break;
				case 3:  models = &ManiaTailsModel::modelJog3;  break;
				case 4:  models = &ManiaTailsModel::modelJog4;  break;
				case 5:  models = &ManiaTailsModel::modelJog5;  break;
				case 6:  models = &ManiaTailsModel::modelJog6;  break;
				case 7:  models = &ManiaTailsModel::modelJog7;  break;
				case 8:  models = &ManiaTailsModel::modelJog8;  break;
				case 9:  models = &ManiaTailsModel::modelJog9;  break;
				case 10: models = &ManiaTailsModel::modelJog10; break;
				case 11: models = &ManiaTailsModel::modelJog11; break;
				case 12: models = &ManiaTailsModel::modelJog12; break;
				case 13: models = &ManiaTailsModel::modelJog13; break;
				case 14: models = &ManiaTailsModel::modelJog14; break;
				case 15: models = &ManiaTailsModel::modelJog15; break;
				case 16: models = &ManiaTailsModel::modelJog16; break;
				case 17: models = &ManiaTailsModel::modelJog17; break;
				default: break;
			}
			break;
		}

		default:
			break;
	}
	updateTransformationMatrix();
}

void ManiaTailsModel::setOrientation(float x, float y, float z, float xRot, float yRot, float zRot, float spinRot)
{
	position.x = x;
	position.y = y;
	position.z = z;
	setRotX(xRot);
	setRotY(yRot);
	setRotZ(zRot);
	setRotSpin(spinRot);
}

std::list<TexturedModel*>* ManiaTailsModel::getModels()
{
	return models;
}

void ManiaTailsModel::loadStaticModels()
{
	if (ManiaTailsModel::modelDash0.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading mania sonic static models...\n");
	#endif

	loadObjModel(&ManiaTailsModel::modelDash0 , "res/Models/ManiaTails/", "TailsDash0.obj");
	loadObjModel(&ManiaTailsModel::modelDash1 , "res/Models/ManiaTails/", "TailsDash1.obj");
	loadObjModel(&ManiaTailsModel::modelDash2 , "res/Models/ManiaTails/", "TailsDash2.obj");
	loadObjModel(&ManiaTailsModel::modelDash3 , "res/Models/ManiaTails/", "TailsDash3.obj");
	loadObjModel(&ManiaTailsModel::modelDash4 , "res/Models/ManiaTails/", "TailsDash4.obj");
	loadObjModel(&ManiaTailsModel::modelDash5 , "res/Models/ManiaTails/", "TailsDash5.obj");
	loadObjModel(&ManiaTailsModel::modelDash6 , "res/Models/ManiaTails/", "TailsDash6.obj");
	loadObjModel(&ManiaTailsModel::modelDash7 , "res/Models/ManiaTails/", "TailsDash7.obj");
	loadObjModel(&ManiaTailsModel::modelDash8 , "res/Models/ManiaTails/", "TailsDash8.obj");
	loadObjModel(&ManiaTailsModel::modelDash9 , "res/Models/ManiaTails/", "TailsDash9.obj");
	loadObjModel(&ManiaTailsModel::modelDash10, "res/Models/ManiaTails/", "TailsDash10.obj");
	loadObjModel(&ManiaTailsModel::modelDash11, "res/Models/ManiaTails/", "TailsDash11.obj");
	loadObjModel(&ManiaTailsModel::modelDash12, "res/Models/ManiaTails/", "TailsDash12.obj");
	loadObjModel(&ManiaTailsModel::modelDash13, "res/Models/ManiaTails/", "TailsDash13.obj");
	loadObjModel(&ManiaTailsModel::modelDash14, "res/Models/ManiaTails/", "TailsDash14.obj");
	loadObjModel(&ManiaTailsModel::modelDash15, "res/Models/ManiaTails/", "TailsDash15.obj");
	loadObjModel(&ManiaTailsModel::modelDash16, "res/Models/ManiaTails/", "TailsDash16.obj");
	loadObjModel(&ManiaTailsModel::modelDash17, "res/Models/ManiaTails/", "TailsDash17.obj");
	loadObjModel(&ManiaTailsModel::modelJump  , "res/Models/ManiaTails/", "Jump.obj");
	loadObjModel(&ManiaTailsModel::modelJog0  , "res/Models/ManiaTails/", "TailsJog0.obj");
	loadObjModel(&ManiaTailsModel::modelJog1  , "res/Models/ManiaTails/", "TailsJog1.obj");
	loadObjModel(&ManiaTailsModel::modelJog2  , "res/Models/ManiaTails/", "TailsJog2.obj");
	loadObjModel(&ManiaTailsModel::modelJog3  , "res/Models/ManiaTails/", "TailsJog3.obj");
	loadObjModel(&ManiaTailsModel::modelJog4  , "res/Models/ManiaTails/", "TailsJog4.obj");
	loadObjModel(&ManiaTailsModel::modelJog5  , "res/Models/ManiaTails/", "TailsJog5.obj");
	loadObjModel(&ManiaTailsModel::modelJog6  , "res/Models/ManiaTails/", "TailsJog6.obj");
	loadObjModel(&ManiaTailsModel::modelJog7  , "res/Models/ManiaTails/", "TailsJog7.obj");
	loadObjModel(&ManiaTailsModel::modelJog8  , "res/Models/ManiaTails/", "TailsJog8.obj");
	loadObjModel(&ManiaTailsModel::modelJog9  , "res/Models/ManiaTails/", "TailsJog9.obj");
	loadObjModel(&ManiaTailsModel::modelJog10 , "res/Models/ManiaTails/", "TailsJog10.obj");
	loadObjModel(&ManiaTailsModel::modelJog11 , "res/Models/ManiaTails/", "TailsJog11.obj");
	loadObjModel(&ManiaTailsModel::modelJog12 , "res/Models/ManiaTails/", "TailsJog12.obj");
	loadObjModel(&ManiaTailsModel::modelJog13 , "res/Models/ManiaTails/", "TailsJog13.obj");
	loadObjModel(&ManiaTailsModel::modelJog14 , "res/Models/ManiaTails/", "TailsJog14.obj");
	loadObjModel(&ManiaTailsModel::modelJog15 , "res/Models/ManiaTails/", "TailsJog15.obj");
	loadObjModel(&ManiaTailsModel::modelJog16 , "res/Models/ManiaTails/", "TailsJog16.obj");
	loadObjModel(&ManiaTailsModel::modelJog17 , "res/Models/ManiaTails/", "TailsJog17.obj");

}

void ManiaTailsModel::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting mania sonic static models...\n");
	#endif

	Entity::deleteModels(&ManiaTailsModel::modelDash0);
	Entity::deleteModels(&ManiaTailsModel::modelDash1);
	Entity::deleteModels(&ManiaTailsModel::modelDash2);
	Entity::deleteModels(&ManiaTailsModel::modelDash3);
	Entity::deleteModels(&ManiaTailsModel::modelDash4);
	Entity::deleteModels(&ManiaTailsModel::modelDash5);
	Entity::deleteModels(&ManiaTailsModel::modelDash6);
	Entity::deleteModels(&ManiaTailsModel::modelDash7);
	Entity::deleteModels(&ManiaTailsModel::modelDash8);
	Entity::deleteModels(&ManiaTailsModel::modelDash9);
	Entity::deleteModels(&ManiaTailsModel::modelDash10);
	Entity::deleteModels(&ManiaTailsModel::modelDash11);
	Entity::deleteModels(&ManiaTailsModel::modelDash12);
	Entity::deleteModels(&ManiaTailsModel::modelDash13);
	Entity::deleteModels(&ManiaTailsModel::modelDash14);
	Entity::deleteModels(&ManiaTailsModel::modelDash15);
	Entity::deleteModels(&ManiaTailsModel::modelDash16);
	Entity::deleteModels(&ManiaTailsModel::modelDash17);
	Entity::deleteModels(&ManiaTailsModel::modelJump);
	Entity::deleteModels(&ManiaTailsModel::modelJog0);
	Entity::deleteModels(&ManiaTailsModel::modelJog1);
	Entity::deleteModels(&ManiaTailsModel::modelJog2);
	Entity::deleteModels(&ManiaTailsModel::modelJog3);
	Entity::deleteModels(&ManiaTailsModel::modelJog4);
	Entity::deleteModels(&ManiaTailsModel::modelJog5);
	Entity::deleteModels(&ManiaTailsModel::modelJog6);
	Entity::deleteModels(&ManiaTailsModel::modelJog7);
	Entity::deleteModels(&ManiaTailsModel::modelJog8);
	Entity::deleteModels(&ManiaTailsModel::modelJog9);
	Entity::deleteModels(&ManiaTailsModel::modelJog10);
	Entity::deleteModels(&ManiaTailsModel::modelJog11);
	Entity::deleteModels(&ManiaTailsModel::modelJog12);
	Entity::deleteModels(&ManiaTailsModel::modelJog13);
	Entity::deleteModels(&ManiaTailsModel::modelJog14);
	Entity::deleteModels(&ManiaTailsModel::modelJog15);
	Entity::deleteModels(&ManiaTailsModel::modelJog16);
	Entity::deleteModels(&ManiaTailsModel::modelJog17);
}
