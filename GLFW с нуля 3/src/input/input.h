#pragma once

#include <unordered_set>
#include <GLFW/glfw3.h>

class Input {
public:
    static void InputProcCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void ClearInput();
    static bool Pressed(int glfw_key);
    static bool JustPressed(int glfw_key);
    static bool Released(int glfw_key);
    static int GetAxis(int glfw_key_negative, int glfw_key_positive);

private:
    static std::unordered_set<int> _justPressed;
    static std::unordered_set<int> _pressed;
    static std::unordered_set<int> _released;
};
