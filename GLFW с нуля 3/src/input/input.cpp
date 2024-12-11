#include "input.h"
#include <iostream>

// Определение статических переменных
std::unordered_set<int> Input::_justPressed = {};
std::unordered_set<int> Input::_pressed = {};
std::unordered_set<int> Input::_released = {};

void Input::InputProcCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //std::cout << "Key: " << key << ", Action: " << action << std::endl; // Отладка
    if (action == 1) { // GLFW_PRESS
        _justPressed.insert(key);
        _pressed.insert(key);
    }
    if (action == 0) { // GLFW_RELEASE
        _released.insert(key);
        _pressed.erase(key);
    }
}


void Input::ClearInput() {
    _justPressed.clear();
    _released.clear();
}

bool Input::Pressed(int glfw_key) {
    return _pressed.find(glfw_key) != _pressed.end();
}

bool Input::JustPressed(int glfw_key) {
    return _justPressed.find(glfw_key) != _justPressed.end();
}

bool Input::Released(int glfw_key) {
    return _released.find(glfw_key) != _released.end();
}

int Input::GetAxis(int glfw_key_negative, int glfw_key_positive) {
    return Input::Pressed(glfw_key_positive) - Input::Pressed(glfw_key_negative);
}