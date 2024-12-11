#include <iostream>
#include "window/window.h"
#include "shaders/shaders.h"

using namespace std;

void update();

uint32_t VAO, VBO, EBO, program;
float brightness = 1;
float vertices[] = {
	-0.5f, 0.5f, 0.0f,		1, 1, 0,
	0.5f, 0.5f, 0.0f,		0, 1, 0,
	0.5f, -0.5f, 0.0f,		1, 0, 1,
	-0.5f, -0.5f, 0.0f,		0, 1, 1
};
uint32_t indices[] = {
	0, 1, 2,
	2, 3, 0
};

int main() {
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = initWindow(1280, 720, "GLFW Window", NULL, NULL);
	
	glClearColor(0, 0, 0, 0);

	program = createShaderProgram("assets/shaders/vertex.vert", "assets/shaders/fragment.frag", "Example");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unlink buffer
	glBindVertexArray(0); // unlink VAO


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glfwSwapInterval(0);
	updateProc(window, update);
}

void update() {

	for (int i = 0; i < sizeof(vertices) / sizeof(float); i += 6)
	{
		vertices[i] += Input::GetAxis(GLFW_KEY_A, GLFW_KEY_D) * Time::getDeltaTime();
		vertices[i+1] += Input::GetAxis(GLFW_KEY_S, GLFW_KEY_W) * Time::getDeltaTime();
	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_VERTEX_ARRAY, 0);

	float currentTime = glfwGetTime();
	//brightness = 0.5f + 0.5f * sin(currentTime);
	glUniform1f(glGetUniformLocation(program, "colorBrightness"), brightness);

	float colorOffset = 0.5f /* * sin(currentTime) */;
	glUniform1f(glGetUniformLocation(program, "colorOffset"), colorOffset);

	glUseProgram(program);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}