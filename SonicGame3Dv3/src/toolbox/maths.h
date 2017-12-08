#include <math.h>

#include "matrix.h"
#include "vector.h"
#include "../entities/camera.h"

#ifndef MATHS_H
#define MATHS_H


float toRadians(float);

float toDegrees(float);

/*
** Blank Matrix4f should have already been created. This function does not allocate any memory to matrix.
*/

void createTransformationMatrix(Matrix4f*, Vector3f*, float, float, float, float);


void createViewMatrix(Matrix4f*, Camera*);

#endif