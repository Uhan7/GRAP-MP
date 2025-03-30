#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera{
protected:
    glm::vec3 cameraPosition;
    glm::vec3 direction;
    glm::mat4 cameraTranslationMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    float yaw = -90.0f;
    float pitch = 0.0f;
    float cameraMoveSpeed = 0.5f;
    float cameraOrientationSpeed = 1.0f;

public:
    Camera(glm::vec3 positionVector, glm::vec3 directionVector);
    virtual ~Camera();

    void MovePosition(char inputDirection);
    void Rotate(char inputDirection);
    virtual void Update(unsigned int shaderProgram, int screenWidth, int screenHeight) = 0;

    glm::vec3 GetCameraPosition();
    glm::mat4 GetCameraTranslationMatrix();
    glm::mat4 GetCameraViewMatrix();
    glm::mat4 GetCameraProjectionMatrix();
};
