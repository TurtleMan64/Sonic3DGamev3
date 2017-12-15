#ifndef MODELDATA_H
#define MODELDATA_H

#include <vector>

class ModelData
{
private:
	std::vector<float> vertices;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	std::vector<int> indices;
	float furthestPoint;

public:

	ModelData(std::vector<float>* vertices, std::vector<float>* textureCoords, std::vector<float>* normals, std::vector<int>* indices, float furthestPoint);

	std::vector<float>* getVertices();

	std::vector<float>* getTextureCoords();

	std::vector<float>* getNormals();

	std::vector<int>* getIndices();

	float getFurthestPoint();

};
#endif