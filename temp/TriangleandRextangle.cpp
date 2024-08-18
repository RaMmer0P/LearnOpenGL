#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int triangle()
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

	// Send the vertices input to the shader
		// Colors the window
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Mentions this is a color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	// Generate buffers
	unsigned int VBO;
	glGenBuffers(1, &VBO);


	// We need array objects so that glsl can user the data in the buffers
	// These are lke pointers
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send the bufffer data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// We have to mention it to GLSL on how to interpret the vertex data in the verte shader
/*The function glVertexAttribPointer has quite a few parameters so let's carefully walk through them:

	The first parameter specifies which vertex attribute we want to configure.Remember that we specified the location of the position vertex attribute in the vertex shader with layout(location = 0).This sets the location of the vertex attribute to 0 and since we want to pass data to this vertex attribute, we pass in 0.
	The next argument specifies the size of the vertex attribute.The vertex attribute is a vec3 so it is composed of 3 values.
	The third argument specifies the type of the data which is GL_FLOAT(a vec * in GLSL consists of floating point values).
	The next argument specifies if we want the data to be normalized.If we're inputting integer data types (int, byte) and we've set this to GL_TRUE, the integer data is normalized to 0 (or -1 for signed data) and 1 when converted to float.This is not relevant for us so we'll leave this at GL_FALSE.
	The fifth argument is known as the stride and tells us the space between consecutive vertex attributes.Since the next set of position data is located exactly 3 times the size of a float away we specify that value as the stride.Note that since we know that the array is tightly packed(there is no space between the next vertex attribute value) we could've also specified the stride as 0 to let OpenGL determine the stride (this only works when values are tightly packed). Whenever we have more vertex attributes we have to carefully define the spacing between each vertex attribute but we'll get to see more examples of that later on.
	The last parameter is of type void* and thus requires that weird cast.This is the offset of where the position data begins in the buffer.Since the position data is at the start of the data array this value is just 0. We will explore this parameter in more detail later on*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Enable this vertex attrib
	glEnableVertexAttribArray(0);

	// Get the vertex shader source
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	// Create the shader in the glsl program
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Set the shader source to the created vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the shader after the shader source is set
	glCompileShader(vertexShader);

	// Do the same thing with the fragment shader
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"

		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create a shader program and attach this shaders to the program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Use this shader program
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Once shaders are attached the shader objects are useless
// We can delete them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glfwSwapBuffers(window);


	// Draw a rextangle instead
	float Rectangle[] = {
		0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f
	};
	unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
	};
	// Generate buffers
	unsigned int EBBO;
	glGenBuffers(1, &EBBO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// Create an vertex object as well
	unsigned int EAO;
	glGenVertexArrays(1, &EAO);
	glBindVertexArray(EAO);

	// Bind the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, EBBO);

	// Bind the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Rectangle), Rectangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Enable this vertex attrib
	glEnableVertexAttribArray(0);
	glBindVertexArray(EAO);
	// wIRE FRAME MODE
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
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