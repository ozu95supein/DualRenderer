#pragma once
#include "Primitive.h"
#include "Material.h"
#include "Texture.h"
#include <vector>
class Mesh {
public:
	Mesh() {}
	Mesh(std::vector<Triangle*> primitives, Material mat, Texture mMeshTexture, Texture mMeshNormalMap, Texture mMeshSpecularMap);
private:
	//this will just be an array of triangles for now
	std::vector<Triangle*> mObjPrimitives;
	// Every Mesh will have 1 material, default or otherwose, may be ignored if there are textures
	Material mMeshMaterial;
	//multiple textures for multiple different parts of the shader
	Texture mMeshTexture;
	Texture mMeshNormalMap;
	Texture mMeshSpecularMap;
};