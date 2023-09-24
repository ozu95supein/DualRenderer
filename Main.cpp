#include<glad/glad.h>

#include<GLFW/glfw3.h>
#include<iostream>
#include "MeshLoader.h"
#include "RenderableObject.h"
#include "Shader.h"
#include "Camera.h"

const unsigned int window_width = 800;
const unsigned int window_height = 800;

int main()
{
	// Initialize GLFW
	glfwInit();
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "DualRenderer", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, window_width, window_height);
	/// --- MESHES
	//now we try and load a mesh and render it
	std::vector<Triangle> MeshTriangles;
	LoadMeshFromFile("Cube.obj", MeshTriangles);
	Mesh cubeMesh(MeshTriangles);

	std::cout << cubeMesh.GetTriangleNumber() << " Triangles in the cube" << std::endl;
	std::cout << cubeMesh.GetSizeOfMeshData() << " bytes in the mesh" << std::endl;

	// --- RENDERABLE OBJECT
	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectTransform = glm::mat4(1.0f);
	objectTransform = glm::translate(objectTransform, objectPos);

	/// --- CAMERA
	//get a camera object
	Camera myCam;
	glm::vec3 position(0.0f, 0.0f, -3.0f);
	glm::vec3 target(0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::mat4 look = glm::lookAt(position, target, up);
	myCam.SetMatrix(look);
	/// --- SHADERS
	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	
	RenderableObject renderCube(&cubeMesh, objectTransform);

	float fov = 90.0f;
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)window_width / (float)window_height, 0.1f, 100.0f);

	/// --- BUFFERS AND DEPTH
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	float rotSpeed = 0.5f;
	float prevTime = glfwGetTime();
	float currTime = glfwGetTime();
	float dt = 0.0f;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//deal with time issues
		float currTime = glfwGetTime();
		dt = currTime - prevTime;
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rotate the RenderCube
		renderCube.mTransform = glm::rotate(renderCube.mTransform, dt * rotSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
		// Handles camera inputs
		myCam.Inputs(window, dt);

		//activate the shader program
		shaderProgram.Activate();
		unsigned int transformLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(renderCube.mTransform));
		unsigned int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(myCam.mViewMatrix));
		unsigned int projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//bind the VAO of the mesh in the object
		renderCube.Draw();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();

		prevTime = currTime;
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}