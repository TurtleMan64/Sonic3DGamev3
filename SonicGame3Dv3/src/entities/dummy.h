#ifndef DUMMY_H
#define DUMMY_H

class Vector3f;
class TexturedModel;

#include <list>
#include <vector>


class Body : public Entity
{
private:
	std::list<TexturedModel*>* myModels;

public:


	Body(std::list<TexturedModel*>* models);

	void step();

	void update(float time);

	void setBaseOrientation(Vector3f* basePosition, float rotX, float rotY, float rotZ, float rotS);

	void setBaseOrientation(float baseX, float baseY, float baseZ, float rotX, float rotY, float rotZ, float rotS);

	std::list<TexturedModel*>* getModels();

	void setModels(std::list<TexturedModel*>* newModels);
};
#endif