#include "window.h"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* initWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetKeyCallback(window, Input::InputProcCallback);

	return window;
}


void updateProc(GLFWwindow* window, void(*updateFunc)()) {
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		updateFunc();

		Input::ClearInput();
		glfwPollEvents();
		glfwSwapBuffers(window);
		Time::updateDeltaTime();
	}
}