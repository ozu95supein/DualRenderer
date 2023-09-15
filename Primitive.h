#pragma once
#include"Common.h"
// Structure to standardize the vertices used in the meshes
//color will be stored and handled by the material class
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
	Vertex(glm::vec3 iposition, glm::vec3 inormal, glm::vec2 itexUV) : position(iposition), normal(inormal), texUV(itexUV) {}
};
class Triangle {
public:
	Triangle();
	Triangle(Vertex iv0, Vertex iv1, Vertex iv2) : mV0(iv0), mV1(iv1), mV2(iv2) {}
private:
	Vertex mV0;
	Vertex mV1;
	Vertex mV2;
};
