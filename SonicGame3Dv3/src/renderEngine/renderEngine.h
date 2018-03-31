#ifndef RENDERENGINE_H
#define RENDERENGINE_H

class ShaderProgram;
class Entity;
class Matrix4f;
class Light;
class Camera;
class ShadowMapMasterRenderer;
class ShadowMapMasterRenderer2;

#include <unordered_map>

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
//for water
RawModel Loader_loadToVAO(std::vector<float>* positions, int dimensions);
GLuint Loader_loadTexture(char* filename);
GLuint Loader_loadTextureWORKS(char* filename);
void Loader_cleanUp();
void Loader_deleteVAO(GLuint vaoID);
void Loader_deleteVBO(GLuint vboID);
void Loader_deleteTexture(GLuint texID);
void Loader_deleteTexturedModels(std::list<TexturedModel*>* tm);
void Loader_printInfo();
GLuint Loader_loadShader(char* file, int shaderType);

//Master Renderer
void Master_render(Camera* camera, float clipX, float clipY, float clipZ, float clipW);

void Master_cleanUp();

void Master_processEntity(Entity* entity);
void Master_processEntityPass2(Entity* entity);
void Master_processTransparentEntity(Entity* entity);

void Master_clearEntities();
void Master_clearEntitiesPass2();
void Master_clearTransparentEntities();

void Master_init();

void Master_enableCulling();

void Master_disableCulling();

void Master_makeProjectionMatrix();

Matrix4f* Master_getProjectionMatrix();

float Master_getVFOV();

float Master_getNearPlane();

float Master_getFarPlane();

GLuint Master_getShadowMapTexture();

ShadowMapMasterRenderer* Master_getShadowRenderer();

GLuint Master_getShadowMapTexture2();

ShadowMapMasterRenderer2* Master_getShadowRenderer2();

void Master_renderShadowMaps(Light* sun);

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

	void render(Entity*);

	void renderNEW(std::unordered_map<TexturedModel*, std::list<Entity*>>* entities, Matrix4f* toShadowSpaceFar, Matrix4f* toShadowSpaceClose);

	void updateProjectionMatrix(Matrix4f* projectionMatrix);

};
#endif