#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "maniasonicmodel.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/player.h"
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

	std::fprintf(stdout, "Loading mania sonic static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/SonicMania/", "Dash0.obj");
	for (auto newModel : (*newModels)){ ManiaSonicModel::modelDash0.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash1.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash1.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash2.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash2.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash3.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash3.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash4.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash4.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash5.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash5.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash6.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash6.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash7.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash7.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash8.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash8.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash9.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash9.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash10.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash10.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Dash11.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelDash11.push_back(newModel); }
	delete newModels;
	Global::countDelete++;


	newModels = loadObjModel("res/Models/SonicMania/", "Jump.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJump.push_back(newModel); }
	delete newModels;
	Global::countDelete++;


	newModels = loadObjModel("res/Models/SonicMania/", "Jog0.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog0.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog1.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog1.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog2.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog2.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog3.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog3.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog4.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog4.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog5.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog5.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog6.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog6.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog7.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog7.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog8.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog8.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog9.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog9.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog10.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog10.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog11.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog11.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog12.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog12.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog13.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog13.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog14.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog14.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog15.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog15.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog16.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog16.push_back(newModel); }
	delete newModels;
	Global::countDelete++;

	newModels = loadObjModel("res/Models/SonicMania/", "Jog17.obj");
	for (auto newModel : (*newModels)) { ManiaSonicModel::modelJog17.push_back(newModel); }
	delete newModels;
	Global::countDelete++;
}

void ManiaSonicModel::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting mania sonic static models...\n");

	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash0);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash1);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash2);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash3);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash4);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash5);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash6);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash7);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash8);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash9);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash10);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelDash11);

	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJump);


	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog0);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog1);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog2);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog3);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog4);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog5);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog6);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog7);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog8);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog9);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog10);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog11);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog12);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog13);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog14);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog15);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog16);
	ManiaSonicModel::deleteModelHelper(&ManiaSonicModel::modelJog17);

	ManiaSonicModel::models = nullptr;
}


void ManiaSonicModel::deleteModelHelper(std::list<TexturedModel*>* mod)
{
	for (auto model : (*mod))
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	mod->clear();
}