#pragma once
#include "Common.h"
class Camera {
public:
	Camera() {
		mViewMatrix = glm::mat4(1.0f);
	}
	void SetMatrix(glm::mat4 input)
	{
		mViewMatrix = input;
	}
	glm::mat4 GetMatrix()
	{
		return mViewMatrix;
	}
	glm::mat4 mViewMatrix;

private:
};