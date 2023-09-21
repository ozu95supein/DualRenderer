#include<glad/glad.h>

#include<GLFW/glfw3.h>
#include<iostream>
#include "MeshLoader.h"
#include "RenderableObject.h"
#include "Shader.h"

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
	std::cout << cubeMesh.GetSizeOfMeshData() << " Triangles in the cube" << std::endl;

	/// --- SHADERS
	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	
	// --- RENDERABLE
	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);
	RenderableObject renderCube(&cubeMesh, objectModel);

	/// --- BUFFERS AND DEPTH
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//activate the shader program
		shaderProgram.Activate();
		//bind the VAO of the mesh in the object
		renderCube.BindMeshVAO();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}