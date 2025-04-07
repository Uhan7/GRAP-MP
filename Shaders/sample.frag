#version 330 core

// Objects

in vec3 normCoord;
in vec3 fragPos;
in vec2 texCoord;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;
uniform sampler2D tex5;

uniform sampler2D norm_tex;
uniform int textureNumber;  

// Lights

#define LIGHTS 7

uniform vec3 lightPos[LIGHTS];
uniform vec3 lightColor[LIGHTS];
uniform vec3 lightDirection[LIGHTS];
uniform bool isDirectional[LIGHTS];

uniform float ambientStr;
uniform vec3 ambientColor;

// uniform float outerCone;
// uniform float innerCone;

uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;

out vec4 FragColor;

void main(){

    vec3 normal;

    switch(textureNumber){
        case 0:
        case 1:
        case 2:
        case 3:  
        case 4: normal = normalize(normCoord); break;
        case 5:  normal = texture(norm_tex, texCoord).rgb; normal = normalize(normal * 2.0 - 1.0);
    }
    vec3 ambientCol = ambientColor * ambientStr;


    vec3 finalDiffuse = vec3(0.0);
    vec3 finalSpecular = vec3(0.0);

    for (int i = 0; i < LIGHTS; i++){
        vec3 lightDir = normalize(lightPos[i] - fragPos);
        float attenuation = 1.0f;

        if (isDirectional[i]){
            lightDir = normalize(-lightDirection[i]);
        }
        else{
            float distance = length(lightPos[i] - fragPos);
            float constant = 0.85;
            float linear = 0.002;
            float quadratic = 0.001;
            attenuation = 1.0 / (constant + linear * distance + quadratic * distance * distance);

            float outerCone = 0.9f;
            float innerCone = 0.5f;

            float angle1 = dot(lightDir, normalize(-lightDirection[i]));
            float angle2 = innerCone - outerCone;
            float intensity = clamp((angle1 - outerCone) / angle2, 0.0, 1.0);
            attenuation *= intensity;
        }

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
