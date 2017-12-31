#ifndef RENDERENGINE_H
#define RENDERENGINE_H

class ShaderProgram;
class Entity;
class Matrix4f;
class Light;
class Camera;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list>
#include <unordered_map>
#include "../models/models.h"


//DisplayManager
int createDisplay();
void updateDisplay();
void closeDisplay();
int displayWantsToClose();
GLFWwindow* getWindow();


//Loader
RawModel Loader_loadToVAO(std::vector<float>* positions, std::vector<float>* textureCoords, std::vector<float>* normals, std::vector<int>* indices);
//for text
//returns a std::vector<int> where the first entry is the vao and the rest are vbos
std::vector<int> Loader_loadToVAO(std::vector<float>* positions, std::vector<float>* textureCoords);
GLuint Loader_loadTexture(char* filename);
GLuint Loader_loadTextureWORKS(char* filename);
void Loader_cleanUp();
void Loader_deleteVAO(GLuint vaoID);
void Loader_deleteVBO(GLuint vboID);
void Loader_deleteTexture(GLuint texID);
void Loader_deleteTexturedModels(std::list<TexturedModel*>* tm);
void Loader_printInfo();

//Master Rebderer
void Master_render(Camera* camera);

void Master_cleanUp();

void Master_processEntity(Entity* entity);

void Master_clearEntities();

void Master_init();

void Master_enableCulling();

void Master_disableCulling();

void Master_makeProjectionMatrix();

//Renderer
class EntityRenderer
{
private:
	float clockTime;

	ShaderProgram* shader;

	void prepareTexturedModel(TexturedModel* model);

	void unbindTexturedModel();

	void prepareInstance(Entity* entity);

public:
	EntityRenderer(ShaderProgram* shader, Matrix4f* projectionMatrix);

	void render(Entity*, ShaderProgram*);

	void renderNEW(std::unordered_map<TexturedModel*, std::list<Entity*>>* entities);

	void updateProjectionMatrix(Matrix4f* projectionMatrix);

};
#endif