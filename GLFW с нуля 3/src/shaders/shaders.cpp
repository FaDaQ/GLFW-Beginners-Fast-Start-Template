#include "shaders.h"
#include <fstream>
#include <sstream>

 
std::string loadShaderSrc(const char* filename) {
    std::ifstream file;
    std::stringstream buffer;

    std::string shader_code = "";
    file.open(filename);

    if (file.is_open()) {
        buffer << file.rdbuf();
        shader_code = buffer.str();
    }
    else {
        std::cout << "Failed to load shader: " << filename << std::endl;
    }

    file.close();
    return shader_code;
}

unsigned int loadShader(unsigned int shader_type, std::string& shader_src, std::string shader_name) {
    unsigned int shader = glCreateShader(shader_type);
    const GLchar* shaderSrc = shader_src.c_str();
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);

#ifdef _DEBUG
    checkCompileStatus(shader, shader_name);
#endif

    return shader;
}

unsigned int createShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader, std::string program_name) {
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, fragment_shader);
    glLinkProgram(shaderProgram);

#ifdef _DEBUG
    checkLinkProgramStatus(shaderProgram, program_name);
#endif

    return shaderProgram;
}

unsigned int createShaderProgram(std::string vertex_path, std::string fragment_path, std::string program_name) {
    std::string vertSrc = loadShaderSrc(vertex_path.c_str());
    std::string fragSrc = loadShaderSrc(fragment_path.c_str());

    uint32_t vertex = loadShader(GL_VERTEX_SHADER, vertSrc);
    uint32_t fragment = loadShader(GL_FRAGMENT_SHADER, fragSrc);

    uint32_t program = createShaderProgram(vertex, fragment, program_name);

    return program;
}

void checkCompileStatus(unsigned int shader, const std::string& shader_name) {
    GLint success;
    const int logLength = 512;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, logLength, NULL, infoLog);
        std::cerr << "Compile error " << 
            ((shader_name != "") ? shader_name
                : "Shader(ID: " + std::to_string(shader) + ")") 
            << " shader:\n" << infoLog << std::endl;
    }
    else {
        std::cout << 
            ((shader_name != "") ? shader_name 
                : "Shader(ID: " + std::to_string(shader) + ")") 
            << " shader compile successfully" << std::endl;
    }
}

void checkLinkProgramStatus(unsigned int program, const std::string& program_name) {
    GLint success;
    const int logLength = 512;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, logLength, NULL, infoLog);
        if (program_name != "")
            std::cout << "Link error " << program_name << ": " << infoLog << std::endl;
        else
            std::cout << "Link error ShaderProgram(ID: " << program << "): " << infoLog << std::endl;
    }
    else {
        if (program_name != "")
            std::cout << program_name << " successfuly link" << std::endl;
        else
            std::cout << "ShaderProgram(ID: " << program << ") successfuly link" << std::endl;
    }
}
