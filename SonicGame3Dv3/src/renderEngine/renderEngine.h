#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list>
#include <unordered_map>

#include "../models/models.h"
#include "../entities/entities.h"
#include "../shaders/shaders.h"
#include "../toolbox/matrix.h"
#include "../entities/light.h"
#include "../entities/camera.h"

#ifndef RENDERENGINE_H
#define RENDERENGINE_H
//DisplayManager
int createDisplay();
void updateDisplay();
void closeDisplay();
int displayWantsToClose();
GLFWwindow* getWindow();


//Loader
RawModel loadToVAO(std::vector<float>*, std::vector<float>*, std::vector<float>*, std::vector<int>*);
GLuint loadTexture(char*);
GLuint loadTextureWORKS(char*);
void cleanUp();

//Master Rebderer
void Master_render(Light* sun, Camera* camera);

void Master_cleanUp();

void Master_processEntity(Entity* entity);

void Master_init();

void Master_enableCulling();

void Master_disableCulling();

//Renderer
class EntityRenderer
{
private:
	ShaderProgram* shader;

	void prepareTexturedModel(TexturedModel* model);

	void unbindTexturedModel();

	void prepareInstance(Entity* entity);

public:
	EntityRenderer(ShaderProgram* shader, Matrix4f* projectionMatrix);

	void renderOLD(Entity*, ShaderProgram*); //defunct

	void render(std::unordered_map<TexturedModel*, std::list<Entity*>*>* entities);

};
#endif