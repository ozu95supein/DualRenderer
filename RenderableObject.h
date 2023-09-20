#pragma once
#include "Mesh.h"
#include "Common.h"
#include "VAO.h"
//A renderable object will have a mesh containing vertex, normal and UV data, as well
//as primitive information and intersection helper function. A renderable object is the obj
// that has a mesh, as well as the information and functions to render it, like VAO or Draw functions

class RenderableObject
{
public:
	RenderableObject();
	// Initializes the mesh
	RenderableObject(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, Material mat, std::vector <Texture>& textures);

private:
	Mesh mMesh;
	VAO mVAO;
};