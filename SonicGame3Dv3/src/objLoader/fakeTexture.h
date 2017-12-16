#ifndef FAKETEXTURE_H
#define FAKETEXTURE_H

#include <string>

class FakeTexture
{
public:
	std::string name;
	char type;
	int sound;
	char particle;

	FakeTexture();
};
#endif