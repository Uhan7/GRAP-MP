#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

std::string ReadShaderFile(const std::string& filePath);

unsigned int CompileShader(unsigned int type, const std::string& source);

unsigned int CreateShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);