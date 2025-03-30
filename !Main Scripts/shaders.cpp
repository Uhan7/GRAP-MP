#include "shaders.h"

std::string ReadShaderFile(const std::string& filePath){
    std::ifstream shaderFile(filePath);
    if (!shaderFile) {
        std::cerr << "ERROR! Shader Not Found At : " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    return buffer.str();
}

unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int shaderID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, NULL);
    glCompileShader(shaderID);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cerr << "Error! Shader Loading Failed.\n" << infoLog << std::endl;
    }
    return shaderID;
}

unsigned int CreateShaderProgram(const std::string& vertexPath, const std::string& fragmentPath){
    std::string vertShaderSource = ReadShaderFile(vertexPath);
    std::string fragShaderSource = ReadShaderFile(fragmentPath);

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertShaderSource);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragShaderSource);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Error! Shader Linking Failed.\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}