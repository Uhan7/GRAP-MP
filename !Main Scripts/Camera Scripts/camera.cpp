#include "camera.h"

Camera::Camera(glm::vec3 positionVector, float startingYaw, float startingPitch):
    cameraPosition(positionVector),
    cameraTranslationMatrix(glm::translate(glm::mat4(1.0f), -cameraPosition)),
    yaw(startingYaw - 90),
    pitch(startingPitch){}

Camera::~Camera(){}

void Camera::SetPosition(glm::vec3 newPositionVector){
    cameraPosition = newPositionVector;
    cameraTranslationMatrix = glm::translate(glm::mat4(1.0f), -cameraPosition);
}

void Camera::SetScale(glm::vec3 newScaleVector){

}

void Camera::SetRotation(glm::vec3 newRotationVector){
    yaw = glm::degrees(newRotationVector.y);
}

void Camera::MovePosition(char inputDirection){
    glm::vec3 front = glm::normalize(direction);
    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0, 1.0f, 0)));

    switch (inputDirection){
        case 'L': cameraPosition -= right * cameraMoveSpeed; break;
        case 'R': cameraPosition += right * cameraMoveSpeed; break;
        case 'D': cameraPosition -= glm::vec3(0, 1.0f, 0) * cameraMoveSpeed; break;
        case 'U': cameraPosition += glm::vec3(0, 1.0f, 0) * cameraMoveSpeed; break;
        case 'B': cameraPosition -= front * cameraMoveSpeed; break;
        case 'F': cameraPosition += front * cameraMoveSpeed; break;
        default:
            std::cout << inputDirection << " is not a valid Camera Translation inputDirection." << std::endl;
            break;
    }
    cameraTranslationMatrix = glm::translate(glm::mat4(1.0f), -cameraPosition);
}

void Camera::Rotate(char inputDirection){
    switch (inputDirection){
        case 'L': yaw -= cameraOrientationSpeed; break;
        case 'R': yaw += cameraOrientationSpeed; break;
        case 'D': pitch = glm::clamp(pitch - cameraOrientationSpeed, -89.9f, 89.9f); break;
        case 'U': pitch = glm::clamp(pitch + cameraOrientationSpeed, -89.9f, 89.9f); break;

        case 'Y': pitch = glm::clamp(pitch * 1.01f, -89.9f, 89.9f); break;
        case 'H': pitch = glm::clamp(pitch * -1.01f, -89.9f, 89.9f); break;
        case 'G': yaw -= yaw * 0.10f; break;
        case 'J': yaw += yaw * 0.01f; break;

        default: std::cout << inputDirection << " is not a valid Camera Rotation inputDirection." << std::endl; break;

    }

    if(inputDirection == 'Y' || inputDirection == 'H' || inputDirection == 'G' || inputDirection == 'J'){

        glm::vec3 origin = cameraPosition + direction;

        direction = glm::normalize(glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        ));
    
        cameraPosition = origin * direction;
    }

}

glm::vec3 Camera::GetCameraPosition(){
    return cameraPosition;
}

glm::mat4 Camera::GetCameraTranslationMatrix(){
    return cameraTranslationMatrix;
}

glm::mat4 Camera::GetCameraViewMatrix(){
    return viewMatrix;
}

glm::mat4 Camera::GetCameraProjectionMatrix(){
    return projectionMatrix;
}


float Camera::GetMouse_XPos(){return mouse_x_pos;}
float Camera::GetMouse_YPos(){return mouse_y_pos;}

void Camera::UpdateMousePos(float x, float y){
    mouse_x_pos = x;
    mouse_y_pos = y;
}