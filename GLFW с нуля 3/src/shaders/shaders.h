#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

std::string loadShaderSrc(const char* filename);
unsigned int loadShader(unsigned int shader_type, std::string& shader_src, std::string shader_name = "");
unsigned int createShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader, std::string program_name = "");
unsigned int createShaderProgram(std::string vertex_path, std::string fragment_path, std::string program_name = "");
void checkCompileStatus(unsigned int shader, const std::string& shader_name = "");
void checkLinkProgramStatus(unsigned int program, const std::string& program_name = "");
 