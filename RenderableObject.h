#pragma once
#include "Mesh.h"
#include "Common.h"
//A renderable object will have a mesh containing vertex, normal and UV data, as well
//as primitive information and intersection helper function. A renderable object is the obj
// that has a mesh, as well as the information and functions to render it, like VAO or Draw functions

class RenderableObject
{
public:
	// Initializes the mesh
	RenderableObject(Mesh* inputMesh, glm::mat4 inputMat)
	{
		mMesh = inputMesh;
		mModelMat = inputMat;
	}
	void BindMeshVAO()
	{
		mMesh->BindMeshVAO();
	}
	void Draw()
	{
		mMesh->Draw();
	}
	//we are going to use this a ton anyways so i just make it public
	glm::mat4 mModelMat;
private:
	Mesh * mMesh;
};