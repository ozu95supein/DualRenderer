#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include "glm/glm.hpp"
const float PI = 3.141592f;
const float MY_EPSILON = 0.001f;

class Triangle 
{
public:
	Triangle();
	Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
	Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 normal);
	glm::vec3 Get_V0();
	glm::vec3 Get_V1();
	glm::vec3 Get_V2();
	glm::vec3 Get_Normal();

private:
	glm::vec3 mV_0;
	glm::vec3 mV_1;
	glm::vec3 mV_2;
	glm::vec3 mNormal;
};
#endif // !PRIMITIVES_H
