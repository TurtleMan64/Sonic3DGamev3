#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "maniaknucklesmodel.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/playerknuckles.h"
#include "../toolbox/maths.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*>* ManiaKnucklesModel::models;

std::list<TexturedModel*> ManiaKnucklesModel::modelDash0;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash1;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash2;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash3;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash4;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash5;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash6;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash7;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash8;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash9;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash10;
std::list<TexturedModel*> ManiaKnucklesModel::modelDash11;
std::list<TexturedModel*> ManiaKnucklesModel::modelJump;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog0;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog1;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog2;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog3;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog4;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog5;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog6;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog7;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog8;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog9;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog10;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog11;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog12;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog13;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog14;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog15;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog16;
std::list<TexturedModel*> ManiaKnucklesModel::modelJog17;

ManiaKnucklesModel::ManiaKnucklesModel()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 0.33f;
	visible = false;
	ManiaKnucklesModel::models = nullptr;
}

void ManiaKnucklesModel::step()
{

}

void ManiaKnucklesModel::animate(int animIndex, float time)
{
	setScale(0.33f);
	switch (animIndex)
	{
		case 1: //run
		{
			int index = (int)(time / 8.3333333f);
			switch (index)
			{
				case 0:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash0;  break;
				case 1:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash1;  break;
				case 2:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash2;  break;
				case 3:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash3;  break;
				case 4:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash4;  break;
				case 5:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash5;  break;
				case 6:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash6;  break;
				case 7:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash7;  break;
				case 8:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash8;  break;
				case 9:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash9;  break;
				case 10: ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash10; break;
				case 11: ManiaKnucklesModel::models = &ManiaKnucklesModel::modelDash11; break;
				default: break;
			}
			break;
		}

		case 12: //jump
		{
			ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJump;
			setScale(0.40f);
			break;
		}

		case 15: //jog
		{
			int index = (int)(time / 5.55555555f);
			switch (index)
			{
				case 0:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog0;  break;
				case 1:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog1;  break;
				case 2:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog2;  break;
				case 3:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog3;  break;
				case 4:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog4;  break;
				case 5:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog5;  break;
				case 6:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog6;  break;
				case 7:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog7;  break;
				case 8:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog8;  break;
				case 9:  ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog9;  break;
				case 10: ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog10; break;
				case 11: ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog11; break;
				case 12: ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog12; break;
				case 13: ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog13; break;
				case 14: ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog14; break;
				case 15: ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog15; break;
				case 16: ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog16; break;
				case 17: ManiaKnucklesModel::models = &ManiaKnucklesModel::modelJog17; break;
				default: break;
			}
			break;
		}

		default:
			break;
	}
	updateTransformationMatrix();
}

void ManiaKnucklesModel::setOrientation(float x, float y, float z, float xRot, float yRot, float zRot, float spinRot)
{
	position.x = x;
	position.y = y;
	position.z = z;
	setRotX(xRot);
	setRotY(yRot);
	setRotZ(zRot);
	setRotSpin(spinRot);
}

std::list<TexturedModel*>* ManiaKnucklesModel::getModels()
{
	return ManiaKnucklesModel::models;
}

void ManiaKnucklesModel::loadStaticModels()
{
	if (ManiaKnucklesModel::modelDash0.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading mania knuckles static models...\n");
	#endif

	loadObjModel(&ManiaKnucklesModel::modelDash0 , "res/Models/ManiaKnuckles/", "KnuxDash0.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash1 , "res/Models/ManiaKnuckles/", "KnuxDash1.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash2 , "res/Models/ManiaKnuckles/", "KnuxDash2.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash3 , "res/Models/ManiaKnuckles/", "KnuxDash3.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash4 , "res/Models/ManiaKnuckles/", "KnuxDash4.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash5 , "res/Models/ManiaKnuckles/", "KnuxDash5.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash6 , "res/Models/ManiaKnuckles/", "KnuxDash6.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash7 , "res/Models/ManiaKnuckles/", "KnuxDash7.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash8 , "res/Models/ManiaKnuckles/", "KnuxDash8.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash9 , "res/Models/ManiaKnuckles/", "KnuxDash9.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash10, "res/Models/ManiaKnuckles/", "KnuxDash10.obj");
	loadObjModel(&ManiaKnucklesModel::modelDash11, "res/Models/ManiaKnuckles/", "KnuxDash11.obj");
	loadObjModel(&ManiaKnucklesModel::modelJump  , "res/Models/ManiaKnuckles/", "KnuxJump.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog0  , "res/Models/ManiaKnuckles/", "KnuxJog0.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog1  , "res/Models/ManiaKnuckles/", "KnuxJog1.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog2  , "res/Models/ManiaKnuckles/", "KnuxJog2.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog3  , "res/Models/ManiaKnuckles/", "KnuxJog3.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog4  , "res/Models/ManiaKnuckles/", "KnuxJog4.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog5  , "res/Models/ManiaKnuckles/", "KnuxJog5.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog6  , "res/Models/ManiaKnuckles/", "KnuxJog6.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog7  , "res/Models/ManiaKnuckles/", "KnuxJog7.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog8  , "res/Models/ManiaKnuckles/", "KnuxJog8.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog9  , "res/Models/ManiaKnuckles/", "KnuxJog9.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog10 , "res/Models/ManiaKnuckles/", "KnuxJog10.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog11 , "res/Models/ManiaKnuckles/", "KnuxJog11.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog12 , "res/Models/ManiaKnuckles/", "KnuxJog12.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog13 , "res/Models/ManiaKnuckles/", "KnuxJog13.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog14 , "res/Models/ManiaKnuckles/", "KnuxJog14.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog15 , "res/Models/ManiaKnuckles/", "KnuxJog15.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog16 , "res/Models/ManiaKnuckles/", "KnuxJog16.obj");
	loadObjModel(&ManiaKnucklesModel::modelJog17 , "res/Models/ManiaKnuckles/", "KnuxJog17.obj");

}

void ManiaKnucklesModel::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting mania knuckles static models...\n");
	#endif

	Entity::deleteModels(&ManiaKnucklesModel::modelDash0);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash1);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash2);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash3);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash4);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash5);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash6);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash7);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash8);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash9);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash10);
	Entity::deleteModels(&ManiaKnucklesModel::modelDash11);
	Entity::deleteModels(&ManiaKnucklesModel::modelJump);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog0);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog1);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog2);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog3);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog4);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog5);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog6);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog7);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog8);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog9);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog10);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog11);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog12);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog13);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog14);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog15);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog16);
	Entity::deleteModels(&ManiaKnucklesModel::modelJog17);

	ManiaKnucklesModel::models = nullptr;
}
