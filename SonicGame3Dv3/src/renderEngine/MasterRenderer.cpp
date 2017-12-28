#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../entities/light.h"
#include "../entities/camera.h"
#include "../shaders/shaders.h"
#include "../entities/entities.h"
#include "../models/models.h"
#include "renderEngine.h"
#include "../toolbox/maths.h"
#include "../toolbox/matrix.h"
#include "../engineTester/main.h"
#include "skymanager.h"

#include <iostream>
#include <list>
#include <unordered_map>
#include <stdexcept>

ShaderProgram* shader;
EntityRenderer* renderer;

std::unordered_map<TexturedModel*, std::list<Entity*>> entitiesMap;
std::list<Entity*> entitiesList;

Matrix4f* projectionMatrix;

const float FOV = 50;
const float NEAR_PLANE = 0.5f;
const float FAR_PLANE = 15000;

float RED = 0.9f;
float GREEN = 0.95f;
float BLUE = 1.0f;

void prepare();

void Master_init()
{
	shader = new ShaderProgram("res/Shaders/entity/vertexShader.txt", "res/Shaders/entity/fragmentShader.txt");
	Global::countNew++;
	projectionMatrix = new Matrix4f();
	Global::countNew++;
	renderer = new EntityRenderer(shader, projectionMatrix);
	Master_makeProjectionMatrix();
	Global::countNew++;

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Master_render(Camera* camera)
{
	prepare();
	shader->start();
	RED = SkyManager::getFogRed();
	GREEN = SkyManager::getFogGreen();
	BLUE = SkyManager::getFogBlue();
	shader->loadSkyColour(RED, GREEN, BLUE);
	shader->loadLight(Global::gameLightSun);
	shader->loadViewMatrix(camera);

	renderer->renderNEW(&entitiesMap);
	//for (Entity* entry : entitiesList)
	//{
		//renderer->render(entry, shader);
	//}

	shader->stop();
}

void Master_processEntity(Entity* entity)
{
	if (entity->getVisible() == false)
	{
		return;
	}
	//entitiesList.push_back(entity);


	//new idea (scrap this).
	//just have a render function in the entity class where the entity can decide to call the render function with its model if it wants to. yeah just do that. and go back to old render method here

	std::list<TexturedModel*>* modellist = entity->getModels();
	for (TexturedModel* entityModel : (*modellist))
	{
		//3 ways, not sure which is best
		//try
		//{
			//std::list<Entity*>* list = entitiesMap.at(entityModel);
		//}
		//catch (const std::out_of_range& oor)
		//{

		//}

		//not sure if find or count is going to be faster - it doesnt specify if count stops once it finds one
		//int count = entitiesMap.count(entityModel);
		//if (count == 0)
		{
			//make new list, add to map
			//std::list<Entity*> newList;
			//newList.push_back(entity);
			//entitiesMap.insert(std::pair<TexturedModel*, std::list<Entity*>>(entityModel, newList));
		}
		//else
		{
			//add to list
			//std::list<Entity*>* list = &entitiesMap.at(entityModel);
			//list->push_back(entity);
		}

		//std::unordered_map<TexturedModel*, std::list<Entity*>>::iterator iterator = entitiesMap.find(entityModel);
		//if (iterator == entitiesMap.end())
		//{
			// not found
		//}
		//else
		//{
			// found
			//iterator->second->push_back(entity);
		//}

		std::list<Entity*>* list = &entitiesMap[entityModel];
		list->push_back(entity);
	}
}

void Master_clearEntities()
{
	//entitiesList.clear();

	//i need to call delete on all the lists
	//for (auto entry : entitiesMap)
	//{
		//entry.second->clear();
		//delete entry.first;
	//}
	entitiesMap.clear();
}

void prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(RED, GREEN, BLUE, 1);
}

void Master_cleanUp()
{
	shader->cleanUp();
	delete shader;
	Global::countDelete++;
	delete renderer;
	Global::countDelete++;
	delete projectionMatrix;
	Global::countDelete++;
}

void Master_enableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Master_disableCulling()
{
	glDisable(GL_CULL_FACE);
}

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

void Master_makeProjectionMatrix()
{
	int displayWidth;
	int displayHeight;
	glfwGetWindowSize(getWindow(), &displayWidth, &displayHeight);

	float aspectRatio = (float)displayWidth / (float)displayHeight;
	float y_scale = (float)((1.0f / tan(toRadians(FOV / 2.0f))));
	float x_scale = y_scale / aspectRatio;
	float frustum_length = FAR_PLANE - NEAR_PLANE;

	projectionMatrix->m00 = x_scale;
	projectionMatrix->m11 = y_scale;
	projectionMatrix->m22 = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
	projectionMatrix->m23 = -1;
	projectionMatrix->m32 = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
	projectionMatrix->m33 = 0;

	renderer->updateProjectionMatrix(projectionMatrix);
}
