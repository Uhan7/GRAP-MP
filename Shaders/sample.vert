#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 transform0;
uniform mat4 transform1;
uniform mat4 transform2;

uniform int transformNumber;

uniform mat4 projection;
uniform mat4 view;

out vec3 normCoord;
out vec3 fragPos;
out vec2 texCoord;

void main() {
    mat4 finalTransform;
    switch(transformNumber){
        case 0: finalTransform = transform0; break;
        case 1: finalTransform = transform1; break;
        case 2: finalTransform = transform2; break;
    }

    gl_Position = projection * view * finalTransform * vec4(aPos, 1.0);
    normCoord = mat3(transpose(inverse(finalTransform))) * vertexNormal;
    fragPos = vec3(finalTransform * vec4(aPos, 1.0));

    texCoord = aTex;
}