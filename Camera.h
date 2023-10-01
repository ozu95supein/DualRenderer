#pragma once
#include "Common.h"
class Camera {
public:
	Camera();
	Camera(glm::vec3 camposition, glm::vec3 camtarget, glm::vec3 up);
	void SetMatrix(glm::mat4 input);
	glm::mat4 GetMatrix();
	void Inputs(GLFWwindow* window, float dt);
	void UpdateViewMatrix();

	//all these variables are public for ease of access
	//variables for the camera for when we move it
	glm::vec3 mCameraPosition;
	glm::vec3 mCameraDirection;
	glm::vec3 mCameraUp;
	//the matrixmViewMatrix is a combination of all the other variables below
	glm::mat4 mViewMatrix;
	//magic number that we can change later. Used for camera controls and cam movement
	float speed = 0.1f;
	float sensitivity = 100.0f;

private:
	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

};