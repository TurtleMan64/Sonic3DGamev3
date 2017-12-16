#ifndef OBJLOADER_H
#define OBJLOADER_H

class TexturedModel;
class CollisionModel;

#include <list>
#include <string>


//Both the TexturedModel list AND EACH TexturedModel contained within must be deleted later.
std::list<TexturedModel*>* loadObjModel(std::string filePath, std::string fileName);

//The CollisionModel returned must be deleted later.
CollisionModel* loadCollisionModel(std::string filePath, std::string fileName);
#endif