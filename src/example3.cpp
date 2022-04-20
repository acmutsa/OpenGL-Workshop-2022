#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//We can apply transforms by changing our pos to take in this 4x4 matrix

const char* vertexShaderSource = "#version 450 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;\n"
"uniform mat4 view;\n"
"uniform float time;\n"
"void main()\n"
"{\n"
"   gl_Position = view * transform * vec4(aPos.x, aPos.y*cos(time), aPos.z, 1.0);\n" //Transform comes in 
"}\0"; //this is an actual shader written in GLSL, we then compile this

const char* fragShaderSource = "#version 450 core\n"
"out vec4 FragColor;\n"
"uniform float time;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(sin(time), 0.5*cos(time), 1.0f, 1.0f);\n"
"}\n\0"; //Fragment shader, what determines pixel color

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);




	GLFWwindow* window = glfwCreateWindow(1024, 768, "OpenGL Workshop", nullptr, nullptr);
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

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);


	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	//To draw a square, instead, we can:
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

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //comment this and next line when making a cube
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0); //these lines basically set the attributes for our verticies 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glViewport(0, 0, 1024, 768);
	glEnable(GL_DEPTH_TEST); //Enables Z-buffer
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 trans = glm::mat4(1.0); //identity matrix
		//trans = glm::scale(trans, glm::vec3(1.5f, 1.5f, 1.5f));
		//trans = glm::translate(trans, glm::vec3(0.1f, 0.2f, -0.5f));

		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.5, 1.0, 0.0));

		glUseProgram(finalShader); //This actually draws our triangle!
		GLuint transInShader = glGetUniformLocation(finalShader, "transform");
		glUniformMatrix4fv(transInShader, 1, GL_FALSE, glm::value_ptr(trans));

		glm::mat4 view = glm::mat4(1.0); //view matrix for our camera
		view = glm::translate(view, glm::vec3(0.0f, 0.5*sinf(glfwGetTime()), 0.0f));
		GLuint viewInShader = glGetUniformLocation(finalShader, "view"); 
		glUniformMatrix4fv(viewInShader, 1, GL_FALSE, glm::value_ptr(view));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); //We have to swap buffers so we don't actually have any flickering. We draw left to right, up to down, because the displaying is not instant, we may see flickering, which is why we "swap" to a back buffer so that we can make these displays instant
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VBO); //Clean our objects & Close
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(finalShader);

	glfwTerminate(); //clean GL's resources
	return 0;
}