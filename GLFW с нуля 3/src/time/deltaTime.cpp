#include <GLFW/glfw3.h>
#include "time.h"

double Time::deltaTime = 0.0;
double Time::currentTime = 0.0;
double Time::previousTime = 0.0;

double Time::getDeltaTime() {
	return Time::deltaTime;
}

void Time::updateDeltaTime() {
	Time::currentTime = glfwGetTime();
	Time::deltaTime = Time::currentTime - Time::previousTime;
	Time::previousTime = Time::currentTime;
}

