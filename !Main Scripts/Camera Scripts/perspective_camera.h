#pragma once
#include "camera.h"

class PerspectiveCamera : public Camera{
public:
    PerspectiveCamera(glm::vec3 positionVector, float startingYaw, float startingPitch);
    void Update(unsigned int shaderProgram, int screenWidth, int screenHeight) override;
};