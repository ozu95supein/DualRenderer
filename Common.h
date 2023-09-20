#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include<GLFW/glfw3.h>

#include<vector>
#include<iostream>
// Structure to standardize the vertices used in the meshes
//color will be stored and handled by the material class
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
	Vertex(glm::vec3 iposition, glm::vec3 inormal, glm::vec2 itexUV) : position(iposition), normal(inormal), texUV(itexUV) {}
};