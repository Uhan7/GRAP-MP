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

void Light::Render(unsigned int shaderProgram, Camera* activeCameraPointer, int lightIndex){
    // This is so epic
    std::string lightPosName = "lightPos[" + std::to_string(lightIndex) + "]";
    std::string lightColorName = "lightColor[" + std::to_string(lightIndex) + "]";

    GLuint uniformLightPosAddress = glGetUniformLocation(shaderProgram, lightPosName.c_str());
    glUniform3fv(uniformLightPosAddress, 1, glm::value_ptr(lightPos));

    GLuint uniformLightColorAddress = glGetUniformLocation(shaderProgram, lightColorName.c_str());
    glUniform3fv(uniformLightColorAddress, 1, glm::value_ptr(lightColor));
    
    GLuint uniformAmbientStrengthAddress = glGetUniformLocation(shaderProgram, "ambientStr");
    glUniform1f(uniformAmbientStrengthAddress, (ambientStr));
    GLuint uniformAmbientColorAddress = glGetUniformLocation(shaderProgram, "ambientColor");
    glUniform3fv(uniformAmbientColorAddress, 1, glm::value_ptr(ambientColor));
    GLuint uniformcameraPositionitionAddress = glGetUniformLocation(shaderProgram, "cameraPosition");
    glUniform3fv(uniformcameraPositionitionAddress, 1, glm::value_ptr(activeCameraPointer->GetCameraPosition()));
    GLuint uniformSpecularStrengthAddress = glGetUniformLocation(shaderProgram, "specStr");
    glUniform1f(uniformSpecularStrengthAddress, specStr);
    GLuint uniformSpecularPhongAddress = glGetUniformLocation(shaderProgram, "specPhong");
    glUniform1f(uniformSpecularPhongAddress, specPhong);
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

    lightPos = glm::vec3(lightTransformationMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}