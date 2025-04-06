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
    
    
    float mouse_x_pos = 0; /// Test variable for the orthographic camera.
    float mouse_y_pos = 0;

    float yaw;
    float pitch;
    float cameraMoveSpeed = 0.5f;
    float cameraOrientationSpeed = 1.0f;

public:
    Camera(glm::vec3 positionVector, float startingYaw, float startingPitch);
    virtual ~Camera();

    void SetPosition(glm::vec3 newPositionVector);
    void SetScale(glm::vec3 newScaleVector);
    void SetRotation(glm::vec3 newRotationVector);
    
    void MovePosition(char inputDirection);
    void Rotate(char inputDirection);
    virtual void Update(unsigned int shaderProgram, int screenWidth, int screenHeight) = 0;

    glm::vec3 GetCameraPosition();
    glm::mat4 GetCameraTranslationMatrix();
    glm::mat4 GetCameraViewMatrix();
    glm::mat4 GetCameraProjectionMatrix();

    float GetMouse_XPos();
    float GetMouse_YPos();
    void UpdateMousePos(float x, float y);
};
