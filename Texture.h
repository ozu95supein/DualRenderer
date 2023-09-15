#pragma once
#include "Common.h"
class Texture
{
public:
	Texture() : mID(0), mType(NULL), mUnit(0){}
private:
	GLuint mID;
	const char* mType;
	GLuint mUnit;
};