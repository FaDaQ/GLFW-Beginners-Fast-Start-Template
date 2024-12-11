#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../input/input.h"
#include "../time/time.h"

GLFWwindow* initWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
void updateProc(GLFWwindow* window, void (*updateFunc)());
