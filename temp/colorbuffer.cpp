#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int New()
{
	//InITIALIZING OpenGL
	glfwInit();

	// Mentions the version name for the opengl window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core profile to be used so that we have modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a gl window with width,height and a title name
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGl", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Window couldn't be created" << std::endl;
		glfwTerminate();
		return -1;
	}
    //The created window must be added
	glfwMakeContextCurrent(window);

	// This will add something to the window
	gladLoadGL();
	// It will provide how much of view port is present
	glViewport(0,0,800,800);
	// Colors the window
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Mentions this is a color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//swaps this buffer with the other buffer
	glfwSwapBuffers(window);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}


	//Delete window
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}