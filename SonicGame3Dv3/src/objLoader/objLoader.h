#ifndef OBJLOADER_H
#define OBJLOADER_H

class TexturedModel;
class CollisionModel;

#include <list>
#include <string>


//Each TexturedModel contained within 'models' must be deleted later.
void loadObjModel(std::list<TexturedModel*>* models, std::string filePath, std::string fileName);

//Each TexturedModel contained within 'models' must be deleted later.
void loadObjModelWithMTL(std::list<TexturedModel*>* models, std::string filePath, std::string fileNameOBJ, std::string fileNameMTL);

//The CollisionModel returned must be deleted later.
CollisionModel* loadCollisionModel(std::string filePath, std::string fileName);
#endif