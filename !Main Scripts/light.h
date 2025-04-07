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

    bool isDirectional = false;

    glm::vec3 lightTranslationVector;
    glm::mat4 lightTransformationMatrix;

    glm::quat lightRotationQuaternion = glm::quat(1, 0, 0, 0);
    // glm::quat qx = glm::angleAxis(objectRotateSpeed, glm::vec3(1, 0, 0));
    // glm::quat qy = glm::angleAxis(objectRotateSpeed, glm::vec3(0, 1, 0));
    // glm::quat qz = glm::angleAxis(objectRotateSpeed, glm::vec3(0, 0, 1));

    glm::vec3 forwardDirection = glm::vec3(-1.0, 0, 0);
    glm::vec3 forward;

public:
    Light(glm::vec3 pLightPos, glm::vec3 pLightColor, float pAmbientStr, glm::vec3 pAmbientColor, float pSpecStr, float pSpecPhong);

    void Translate(char inputDirection, float translateSpeed);
    void MoveSide(float moveSpeed);
    void MoveUp(float moveSpeed);
    void MoveForward(float moveSpeed);

    void Update();
    void Render(unsigned int shaderProgram, Camera* activeCameraPointer, int lightIndex);

    void SetColor(glm::vec3 newColor);
    void SetForward(glm::vec3 newForward);
    void SetPosition(glm::vec3 newPosition);
    void SetRotation(glm::vec3 newRotationEulerAngles);

    void PositionFromCar(Object* carPointer, glm::vec3 offset);

    void SetDirectional(bool value);
    bool GetDirectional();
};