#pragma once
#include "camera.h"

class OrthographicCamera : public Camera{
public:
    OrthographicCamera(glm::vec3 positionVector, float startingYaw, float startingPitch);
    void Update(unsigned int shaderProgram, int screenWidth, int screenHeight) override;
};
