#include <glad/glad.h>

#include "../entities/entities.h"
#include "../entities/camera.h"

#ifndef MAIN_H
#define MAIN_H
void Main_addEntity(Entity* entityToAdd);
void Main_deleteEntity(Entity* entityToDelete);
void Main_deleteAllEntites();

class Global
{
public:
	static Camera* gameCamera;
};
#endif