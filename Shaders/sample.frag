#version 330 core

// Objects

in vec3 normCoord;
in vec3 fragPos;
in vec2 texCoord;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;

uniform int textureNumber;

// Lights

#define LIGHTS 2

uniform vec3 lightPos[LIGHTS];
uniform vec3 lightColor[LIGHTS];

uniform float ambientStr;
uniform vec3 ambientColor;

uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;

out vec4 FragColor;

void main(){
    vec3 normal = normalize(normCoord);
    vec3 ambientCol = ambientColor * ambientStr;

    vec3 finalDiffuse = vec3(0.0);
    vec3 finalSpecular = vec3(0.0);

    for (int i = 0; i < LIGHTS; i++){
        float distanceToObj = length(lightPos[i] - fragPos);
        float constant = 0.85;
        float linear = 0.0025;
        float quadratic = 0.0015;
        float attenuation = 1.0 / (constant + linear * distanceToObj + quadratic * (distanceToObj * distanceToObj));

        vec3 lightDir = normalize(lightPos[i] - fragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        finalDiffuse += diff * lightColor[i] * attenuation;

        vec3 viewDir = normalize(cameraPos - fragPos);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(reflectDir, viewDir), 0.1f), specPhong);
        finalSpecular += spec * specStr * lightColor[i] * attenuation;
    }

    // To combine em both
    vec3 lightingResult = finalDiffuse + finalSpecular + ambientCol;

    // Apply lighting to obj
    switch(textureNumber){
        case 0: FragColor = vec4(lightingResult, 1.0) * texture(tex0, texCoord); break;
        case 1: FragColor = vec4(lightingResult, 1.0) * texture(tex1, texCoord); FragColor.a = 0.5f; break;
        case 2: FragColor = vec4(lightingResult, 1.0) * texture(tex2, texCoord); FragColor.a = 0.5f; break;
        case 3: FragColor = vec4(lightingResult, 1.0) * texture(tex3, texCoord); break;
        default: FragColor = vec4(lightingResult, 1.0); break;
    }
}
