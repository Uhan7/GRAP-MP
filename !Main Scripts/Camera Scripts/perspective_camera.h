#pragma once
#include "camera.h"

class PerspectiveCamera : public Camera{
public:
    PerspectiveCamera(glm::vec3 positionVector, glm::vec3 directionVector);
    void Update(unsigned int shaderProgram, int screenWidth, int screenHeight) override;
};