#ifndef OBJLOADER_H
#define OBJLOADER_H

class TexturedModel;

#include <list>
#include <string>


//Both the TexturedModel list AND EACH TexturedModel contained within must be deleted later.
std::list<TexturedModel*>* loadObjModel(std::string filePath, std::string fileName);
#endif