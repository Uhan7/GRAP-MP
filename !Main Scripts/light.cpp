#include "light.h"

Light::Light(glm::vec3 pLightPos, glm::vec3 pLightColor, float pAmbientStr, glm::vec3 pAmbientColor, float pSpecStr, float pSpecPhong):
    lightPos(pLightPos),
    lightColor(pLightColor),
    ambientStr(pAmbientStr),
    ambientColor(pAmbientColor),
    specStr(pSpecStr),
    specPhong(pSpecPhong){}

void Light::Render(unsigned int shaderProgram, Camera* activeCameraPointer){
    GLuint uniformLightPosAddress = glGetUniformLocation(shaderProgram, "lightPos");
    glUniform3fv(uniformLightPosAddress, 1, glm::value_ptr(lightPos));
    GLuint uniformLightColorAddress = glGetUniformLocation(shaderProgram, "lightColor");
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