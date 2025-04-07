#include "light.h"

Light::Light(glm::vec3 pLightPos, glm::vec3 pLightColor, float pAmbientStr, glm::vec3 pAmbientColor, float pSpecStr, float pSpecPhong):
    lightPos(pLightPos),
    lightColor(pLightColor),
    ambientStr(pAmbientStr),
    ambientColor(pAmbientColor),
    specStr(pSpecStr),
    specPhong(pSpecPhong){
        lightTranslationVector = pLightPos;
        lightTransformationMatrix = glm::mat4(1.0f);
}

void Light::MoveForward(float moveSpeed){
    lightTranslationVector += forward * moveSpeed;
}

void Light::MoveUp(float moveSpeed){
    lightTranslationVector += glm::vec3(0.0f, moveSpeed, 0.0f);
}

void Light::MoveSide(float moveSpeed){
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
    lightTranslationVector += right * moveSpeed;
}

void Light::Translate(char inputDirection, float translateSpeed){
    switch (inputDirection){
        case 'L': lightTranslationVector -= glm::vec3(translateSpeed, 0.0f, 0.0f); break;
        case 'R': lightTranslationVector += glm::vec3(translateSpeed, 0.0f, 0.0f); break;
        case 'D': lightTranslationVector -= glm::vec3(0.0f, translateSpeed, 0.0f); break;
        case 'U': lightTranslationVector += glm::vec3(0.0f, translateSpeed, 0.0f); break;
        case 'B': lightTranslationVector += glm::vec3(0.0f, 0.0f, translateSpeed); break;
        case 'F': lightTranslationVector -= glm::vec3(0.0f, 0.0f, translateSpeed); break;
        default: std::cout << inputDirection << " is not a valid Object Translation inputDirection." << std::endl; break;
    }
}

void Light::Update(){
    lightTransformationMatrix = glm::mat4(1.0f);
    lightTransformationMatrix = glm::translate(lightTransformationMatrix, lightTranslationVector);
    lightTransformationMatrix *= glm::mat4_cast(lightRotationQuaternion);

    lightPos = glm::vec3(lightTransformationMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    forward = glm::mat3(lightTransformationMatrix) * glm::vec3(0.0f, 0.0f, -1.0f);
}

void Light::Render(unsigned int shaderProgram, Camera* activeCameraPointer, int lightIndex){
    std::string lightPosName = "lightPos[" + std::to_string(lightIndex) + "]";
    GLuint uniformLightPosAddress = glGetUniformLocation(shaderProgram, lightPosName.c_str());
    glUniform3fv(uniformLightPosAddress, 1, glm::value_ptr(lightPos));

    std::string lightColorName = "lightColor[" + std::to_string(lightIndex) + "]";
    GLuint uniformLightColorAddress = glGetUniformLocation(shaderProgram, lightColorName.c_str());
    glUniform3fv(uniformLightColorAddress, 1, glm::value_ptr(lightColor));

    std::string lightDirectionName = "lightDirection[" + std::to_string(lightIndex) + "]";
    GLuint uniformLightDirectionAddress = glGetUniformLocation(shaderProgram, lightDirectionName.c_str());
    glUniform3fv(uniformLightDirectionAddress, 1, glm::value_ptr(forward));

    std::string isDirectionalName = "isDirectional[" + std::to_string(lightIndex) + "]";
    GLuint uniformIsDirectionalAddress = glGetUniformLocation(shaderProgram, isDirectionalName.c_str());
    glUniform1i(uniformIsDirectionalAddress, isDirectional);

    GLuint uniformAmbientStrengthAddress = glGetUniformLocation(shaderProgram, "ambientStr");
    glUniform1f(uniformAmbientStrengthAddress, ambientStr);

    GLuint uniformAmbientColorAddress = glGetUniformLocation(shaderProgram, "ambientColor");
    glUniform3fv(uniformAmbientColorAddress, 1, glm::value_ptr(ambientColor));

    GLuint uniformCameraPosAddress = glGetUniformLocation(shaderProgram, "cameraPos");
    glUniform3fv(uniformCameraPosAddress, 1, glm::value_ptr(activeCameraPointer->GetCameraPosition()));

    GLuint uniformSpecularStrengthAddress = glGetUniformLocation(shaderProgram, "specStr");
    glUniform1f(uniformSpecularStrengthAddress, specStr);

    GLuint uniformSpecularPhongAddress = glGetUniformLocation(shaderProgram, "specPhong");
    glUniform1f(uniformSpecularPhongAddress, specPhong);
}


void Light::SetColor(glm::vec3 newColor){
    lightColor = newColor;
}

void Light::SetForward(glm::vec3 newForward){
    forward = newForward;
}

void Light::SetPosition(glm::vec3 newPosition){
    lightTranslationVector = newPosition;
}

void Light::SetRotation(glm::vec3 newRotationEulerAngles){
    lightRotationQuaternion = glm::quat(glm::radians(newRotationEulerAngles));
}

void Light::PositionFromCar(Object* carPointer, glm::vec3 offset){
    SetPosition(carPointer->GetPosition());
    SetRotation(carPointer->GetRotation());
    SetForward(carPointer->GetForward());
    MoveSide(offset.x);
    MoveUp(offset.y);
    MoveForward(offset.z);
}

void Light::SetDirectional(bool value){
    isDirectional = value;
}
bool Light::GetDirectional(){
    return isDirectional;
}