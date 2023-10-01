#pragma once
#include "Common.h"
class Triangle
{
public:
	Triangle(){};
	Triangle(Vertex v0, Vertex v1, Vertex v2) : mV0(v0), mV1(v1), mV2(v2) {}
	//this is when the input vertices only have position data, meaning we have to set normals to face normals, and use a devault UV value
	Triangle(Vertex v0, Vertex v1, Vertex v2, bool onlyPositions, glm::vec2 defaultUV) : mV0(v0), mV1(v1), mV2(v2)
	{
		glm::vec3 dir1 = v1.position - v0.position;
		glm::vec3 dir2 = v2.position - v0.position;
		glm::vec3 n = glm::normalize(glm::cross(dir1, dir2));
		mV0.normal = n;
		mV1.normal = n;
		mV2.normal = n;
		mV0.texUV = defaultUV;
		mV1.texUV = defaultUV;
		mV2.texUV = defaultUV;
	}

	Vertex Get_V0()
	{
		return mV0;
	}
	Vertex Get_V1()
	{
		return mV1;
	}
	Vertex Get_V2()
	{
		return mV2;
	}
private:
	//vertex
	Vertex mV0;
	Vertex mV1;
	Vertex mV2;
};