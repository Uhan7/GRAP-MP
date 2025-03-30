#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/gtc/type_ptr.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera Scripts/camera.h"

class Light{
private:
    glm::vec3 lightPos;
    glm::vec3 lightColor;
    float ambientStr;
    glm::vec3 ambientColor;
    float specStr;
    float specPhong;

public:
Light(glm::vec3 pLightPos, glm::vec3 pLightColor, float pAmbientStr, glm::vec3 pAmbientColor, float pSpecStr, float pSpecPhong);
    void Render(unsigned int shaderProgram, Camera* activeCameraPointer);
};