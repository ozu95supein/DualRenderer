#include "Camera.h"
Camera::Camera() {
	mViewMatrix = glm::mat4(1.0f);
}
Camera::Camera(glm::vec3 camposition, glm::vec3 camtarget, glm::vec3 up)
{
	//variables for the camera
	mCameraPosition		= camposition;
	mCameraDirection	= glm::normalize(camposition - camtarget);
	mCameraUp			= up;
	UpdateViewMatrix();

}
void Camera::UpdateViewMatrix()
{
	glm::vec3 camtarget = mCameraPosition + mCameraDirection;
	mViewMatrix = glm::lookAt(mCameraPosition, camtarget, mCameraUp);
}
void Camera::SetMatrix(glm::mat4 input)
{
	mViewMatrix = input;
}
glm::mat4 Camera::GetMatrix()
{
	return mViewMatrix;
}
void Camera::Inputs(GLFWwindow* window, float dt)
{
	// Stores the width and height of the window
	int width = 800;
	int height = 800;
	glfwGetWindowSize(window, &width, &height);
	
	float deltaSpeed = speed * dt;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mCameraPosition += deltaSpeed * mCameraDirection;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mCameraPosition -= deltaSpeed * mCameraDirection;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mCameraPosition -= glm::normalize(glm::cross(mCameraDirection, mCameraUp)) * deltaSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mCameraPosition += glm::normalize(glm::cross(mCameraDirection, mCameraUp)) * deltaSpeed;
	
	//after all variables are changed, we apply these changes to the 
	UpdateViewMatrix();
}