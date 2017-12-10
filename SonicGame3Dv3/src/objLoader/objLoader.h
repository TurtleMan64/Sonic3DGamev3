#include <glad/glad.h>

#include "../textures/textures.h"
#include "../models/models.h"
#include "modeldata.h"


#ifndef OBJLOADER_H
#define OBJLOADER_H
RawModel loadObjModelOLD(char* fileName);
RawModel loadObjModel(char* fileName);
RawModel loadACM(char* fileName);
#endif