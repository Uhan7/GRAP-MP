#version 330 core

in vec3 normCoord;
in vec3 fragPos;
in vec2 texCoord;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;

uniform int textureNumber;

// Light
uniform vec3 lightPos;
uniform vec3 lightColor;
float distanceToObj = length(lightPos - fragPos);
float constant = 0.85;
float linear = 0.0025;
float quadratic = 0.0015;
float attenuation = 1.0 / (constant + linear * distanceToObj + quadratic * (distanceToObj * distanceToObj));

// Ambient Light
uniform float ambientStr;
uniform vec3 ambientColor;
vec3 ambientCol = ambientColor * ambientStr;

// Diffuse
vec3 normal = normalize(normCoord);
vec3 lightDir = normalize(lightPos - fragPos);
// vec3 lightDir = vec3(0, 0, 1);
float diff = max(dot(normal, lightDir), 0.0);
vec3 diffuse = diff * lightColor * attenuation;

// Specular
uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;
vec3 viewDir = normalize(cameraPos - fragPos);
vec3 reflectDir = reflect(-lightDir, normal);
float spec = pow(max(dot(reflectDir, viewDir), 0.1f), specPhong);
vec3 specColor = spec * specStr * lightColor * attenuation;

out vec4 FragColor;

void main() {
    // FragColor = vec4(0.59, 0.29, 0.0, 1.0);
    switch(textureNumber){
        case 0: FragColor = vec4(specColor + diffuse + ambientCol, 1.0) * texture(tex0, texCoord); break;
        case 1: FragColor = vec4(specColor + diffuse + ambientCol, 1.0) * texture(tex1, texCoord); break;
        case 2: FragColor = vec4(specColor + diffuse + ambientCol, 1.0) * texture(tex2, texCoord); break;
        case 3: FragColor = vec4(specColor + diffuse + ambientCol, 1.0) * texture(tex3, texCoord); break;
        default: break;
    }
    //FragColor = texture(tex0, texCoord);
}