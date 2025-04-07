#include "perspective_camera.h"

PerspectiveCamera::PerspectiveCamera(glm::vec3 positionVector, float startingYaw, float startingPitch):
    Camera(positionVector, startingYaw, startingPitch){}

void PerspectiveCamera::Update(unsigned int shaderProgram, int screenWidth, int screenHeight){
    pitch = glm::clamp(pitch, -89.9f, 89.9f);

    direction = glm::normalize(glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    ));
    
    glm::vec3 WorldUp = glm::normalize(glm::vec3(0, 1.0f, 0));
    glm::vec3 Center = cameraPosition + direction;
    glm::vec3 F = glm::normalize(glm::vec3(Center - cameraPosition));
    glm::vec3 R = glm::normalize(glm::cross(F, WorldUp));
    glm::vec3 U = glm::normalize(glm::cross(R, F));

    glm::mat4 cameraOrientationMatrix = glm::mat4(
        R.x,  U.x, -F.x,  0.0f,
        R.y,  U.y, -F.y,  0.0f,
        R.z,  U.z, -F.z,  0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    viewMatrix = glm::lookAt(cameraPosition, Center, WorldUp);
    projectionMatrix = glm::perspective(glm::radians(90.f), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 2000.f);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    unsigned int uniformProjectionLocation = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(uniformProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}
