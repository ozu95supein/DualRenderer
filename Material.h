#pragma once
#include "Primitive.h"
enum MaterialType
{
	E_DIFFUSE = 0,
	E_METALLIC = 1,
	E_SPECULAR = 2,
	E_LIGHT = 3,
	E_DIELECTRIC = 4
};
//the material class will have its info accessed regularly, so I will leave it public
class Material
{
public:
	glm::vec3 mColor;
	MaterialType mType;
	float mSpecularRough;
	float mIndexOfRefaction;
	glm::vec3 mAttenuationFactor;

	Material();
	Material(MaterialType t, glm::vec3 color, float specRough, float index);
	//More functions to follow in the future
};