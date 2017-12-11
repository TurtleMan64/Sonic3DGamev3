#include <glad/glad.h>
#include <list>
#include <string>

#include "../textures/textures.h"
#include "../models/models.h"
#include "modeldata.h"


#ifndef OBJLOADER_H
#define OBJLOADER_H
//RawModel loadObjModelOLD(char* fileName);
//RawModel loadObjModelOG(char* fileName);

//Both the TexturedModel list AND EACH TexturedModel contained within must be deleted later.
std::list<TexturedModel*>* loadObjModel(std::string filePath, std::string fileName);
#endif