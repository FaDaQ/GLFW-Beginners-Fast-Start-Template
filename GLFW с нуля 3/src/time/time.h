#pragma once
#include <iostream>

class Time {
public:
	static double getDeltaTime();
	static void updateDeltaTime();

private:
	static double deltaTime;
	static double currentTime;
	static double previousTime;
};

