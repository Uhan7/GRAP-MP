#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "../Required Scripts/tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Required Scripts/stb_image.h"

class Object{
private:
    unsigned int VAO;
    std::vector<GLfloat> fullVertexData;

    float objectTranslateSpeed = 0.3f;
    float objectScaleSpeed = 1.1f;
    float objectRotateSpeed = glm::radians(1.5f);

    glm::mat4 ObjectTransformationMatrix = glm::mat4(1.0f);

    glm::vec3 objectTranslationVector = glm::vec3(0.0f, -35.0f, -10.0f);
    glm::vec3 objectScaleVector = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::quat objectRotationQuaternion = glm::quat(1, 0, 0, 0);
    glm::quat qx = glm::angleAxis(objectRotateSpeed, glm::vec3(1, 0, 0));
    glm::quat qy = glm::angleAxis(objectRotateSpeed, glm::vec3(0, 1, 0));
    glm::quat qz = glm::angleAxis(objectRotateSpeed, glm::vec3(0, 0, 1));

    glm::vec3 forwardDirection = glm::vec3(-1.0, 0, 0);
    glm::vec3 forward;

public:
    Object(const std::string& objPath, const std::string& texturePath, int textureNumber, std::string imageType, float objectScale);
    ~Object();

    void SetForward(glm::vec3 newForward);

    void SetPosition(glm::vec3 newPositionVector);
    void SetScale(glm::vec3 newScaleVector);
    void SetRotation(glm::vec3 newRotationQuaternion);

    void Translate(char inputDirection, float translateSpeed);
    void Translate(char inputDirection);

    void Scale(bool enlarge);

    void Rotate(char polarity, char axis);

    void MoveForward();
    void MoveForward(float moveSpeed);

    void Update(unsigned int shaderProgram, const GLchar* transformName, int transformNumber);
    void Render(unsigned int shaderProgram, int textureNumber, int transformNumber);

    // Getters
    glm::vec3 GetPosition();
    glm::vec3 GetScale();
    glm::vec3 GetRotation();
    std::vector<GLfloat> GetFullVertexData();
    glm::vec3 GetObjectTranslationVector();

};
