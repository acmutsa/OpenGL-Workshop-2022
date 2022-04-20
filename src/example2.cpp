#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 450 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0"; //this is an actual shader written in GLSL, we then compile this

const char* fragShaderSource = "#version 450 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.9f, 0.2f, 0.2f, 1.0f);\n"
"}\n\0"; //Fragment shader, what determines pixel color

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);




	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Workshop", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "ERROR: Unable to create window!\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);



	//To utilize glad, we have to call the function to intialize
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Cannot initalize GLAD!\n";
		return -1;
	}


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr); //pass shader source onto the vertex shader then compile it
	glCompileShader(vertexShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, nullptr);
	glCompileShader(fragShader);

	GLuint finalShader = glCreateProgram(); //Shader program that combines fragment and vertex shaders
	glAttachShader(finalShader, vertexShader);
	glAttachShader(finalShader, fragShader);
	glLinkProgram(finalShader);
	//glUseProgram(finalShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	float vertices2[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f

	,0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left

	}; //We have to map these from 0,1 because those are our screen coordinates. This is a VBO, a series of verticies we store in the GPU. We want this due to speed

	//To draw a square, instead, we can:
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	}; //Using an element buffer object (EBO)

	GLuint EBO;
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO); //Vertex Array Object, keeps track of vertex array states 

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copies the verticies we defined into the currently bound buffer (GL_ARRAY_BUFFER)

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); //these lines basically set the attributes for our verticies 

	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.9, 0.1, 0.9, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(finalShader); //This actually draws our triangle!
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); //We have to swap buffers so we don't actually have any flickering. We draw left to right, up to down, because the displaying is not instant, we may see flickering, which is why we "swap" to a back buffer so that we can make these displays instant
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VBO); //Clean our objects & Close
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(finalShader);

	glfwTerminate(); //clean GL's resources
	return 0;
}