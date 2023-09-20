#pragma once
#include "Common.h"
class Triangle
{
public:
	Triangle(){
		mV_0 = glm::vec3(1, 0, 0);
		mV_1 = glm::vec3(0, 1, 0);
		mV_2 = glm::vec3(0, 0, 1);
		mNormal = glm::vec3(-1, -1, -1);
	};
	Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2){
		mV_0 = v0;
		mV_1 = v1;
		mV_2 = v2;
		glm::vec3 a(v1 - v0);
		glm::vec3 b(v2 - v0);
		mNormal = glm::normalize(glm::cross(a, b));
	}
	Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 normal) {
		mV_0 = v0;
		mV_1 = v1;
		mV_2 = v2;
		mNormal = normal;
	}
	//float Intersect_V_Ray(Ray r, glm::vec3& normal) override;
	glm::vec3 Get_V0(){
		return mV_0;
	}
	glm::vec3 Get_V1(){
		return mV_1;
	}
	glm::vec3 Get_V2(){
		return mV_2;
	}
	glm::vec3 GetTriangleNormal(){
		return mNormal;
	}

private:
	glm::vec3 mV_0;
	glm::vec3 mV_1;
	glm::vec3 mV_2;
	glm::vec3 mNormal;
};