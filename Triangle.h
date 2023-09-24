#pragma once
#include "Common.h"
class Triangle
{
public:
	Triangle(){};
	Triangle(Vertex v0, Vertex v1, Vertex v2) : mV0(v0), mV1(v1), mV2(v2) {}

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