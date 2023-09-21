#pragma once
#include "Triangle.h"
class Mesh {
public:
	Mesh(std::vector<Triangle>& inputTriangles)
	{
		mMeshTriangles = inputTriangles;
		mTriangleNumber = mMeshTriangles.size();
		int number = inputTriangles.size() * 3;
		//convert the triangles into one giant vector array of floats
		for (int i = 0; i <mTriangleNumber; i++)
		{
			mMeshData.push_back(mMeshTriangles[i].Get_V0().position.x);
			mMeshData.push_back(mMeshTriangles[i].Get_V0().position.y);
			mMeshData.push_back(mMeshTriangles[i].Get_V0().position.z);
			mMeshData.push_back(mMeshTriangles[i].Get_V0().normal.x);
			mMeshData.push_back(mMeshTriangles[i].Get_V0().normal.y);
			mMeshData.push_back(mMeshTriangles[i].Get_V0().normal.z);
			mMeshData.push_back(mMeshTriangles[i].Get_V0().texUV.x);
			mMeshData.push_back(mMeshTriangles[i].Get_V0().texUV.y);
			
			mMeshData.push_back(mMeshTriangles[i].Get_V1().position.x);
			mMeshData.push_back(mMeshTriangles[i].Get_V1().position.y);
			mMeshData.push_back(mMeshTriangles[i].Get_V1().position.z);
			mMeshData.push_back(mMeshTriangles[i].Get_V1().normal.x);
			mMeshData.push_back(mMeshTriangles[i].Get_V1().normal.y);
			mMeshData.push_back(mMeshTriangles[i].Get_V1().normal.z);
			mMeshData.push_back(mMeshTriangles[i].Get_V1().texUV.x);
			mMeshData.push_back(mMeshTriangles[i].Get_V1().texUV.y);
			
			mMeshData.push_back(mMeshTriangles[i].Get_V2().position.x);
			mMeshData.push_back(mMeshTriangles[i].Get_V2().position.y);
			mMeshData.push_back(mMeshTriangles[i].Get_V2().position.z);
			mMeshData.push_back(mMeshTriangles[i].Get_V2().normal.x);
			mMeshData.push_back(mMeshTriangles[i].Get_V2().normal.y);
			mMeshData.push_back(mMeshTriangles[i].Get_V2().normal.z);
			mMeshData.push_back(mMeshTriangles[i].Get_V2().texUV.x);
			mMeshData.push_back(mMeshTriangles[i].Get_V2().texUV.y);
		}
		//Initialize OpenGl
		glGenVertexArrays(1, &mMeshVAO);
		glGenBuffers(1, &mMeshVBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(mMeshVAO);

		glBindBuffer(GL_ARRAY_BUFFER, mMeshVBO);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * mMeshData.size()), mMeshData.data(), GL_STATIC_DRAW);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		//texture uv attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(0);
		//unbind for now
		glBindVertexArray(0);

	}
	~Mesh()
	{
		mMeshTriangles.clear();
		mMeshData.clear();
		glDeleteVertexArrays(1, &mMeshVAO);
		glDeleteBuffers(1, &mMeshVBO);
	}
	//debug functions
	unsigned int GetTriangleNumber()
	{
		return mTriangleNumber;
	}
	unsigned int GetSizeOfMeshData()
	{
		//this should be equal to the number of floats in mesh data which is the number of meshtriangles times 24
		return mMeshData.size();
	}
private:
	//This is saved for ease of access and later raycast construction
	std::vector<Triangle> mMeshTriangles;
	unsigned int mTriangleNumber;
	//an array of floats, this will have the following format:
	// | vetex 1                          | vertex 2
	// | x | y | z | nx | ny | nz | u | v | x | y | z | nx | ny | nz | u | v |.... |
	std::vector<float> mMeshData;
	//VAO/VBO stuff
	GLuint mMeshVAO;
	GLuint mMeshVBO;
};