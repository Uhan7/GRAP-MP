#pragma once
#include "camera.h"

class OrthographicCamera : public Camera{
public:
    OrthographicCamera(glm::vec3 positionVector, glm::vec3 directionVector);
    void Update(unsigned int shaderProgram, int screenWidth, int screenHeight) override;
};
