#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>



int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "OpenGL Workshop", nullptr, nullptr);
	if (!window) {
		std::cout << "ERROR: Unable to create window!\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//To utilize glad, we have to call the function to intialize
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Cannot initalize GLAD!\n";
		return -1;
	}

	glViewport(0, 0, 1024, 768);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.9, 0.1, 0.9, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwPollEvents();
		glfwSwapBuffers(window); //We have to swap buffers so we don't actually have any flickering. We draw left to right, up to down, because the displaying is not instant, we may see flickering, which is why we "swap" to a back buffer so that we can make these displays instant

	}
	
	glfwTerminate(); //clean GL's resources
	return 0;
}