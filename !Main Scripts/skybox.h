#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera Scripts/camera.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Skybox{
private:
    float vertices[24]{
        -1.f, -1.f, 1.f, //0
        1.f, -1.f, 1.f,  //1
        1.f, -1.f, -1.f, //2
        -1.f, -1.f, -1.f,//3
        -1.f, 1.f, 1.f,  //4
        1.f, 1.f, 1.f,   //5
        1.f, 1.f, -1.f,  //6
        -1.f, 1.f, -1.f  //7
    };

    unsigned int indices[36]{
        1,2,6,
        6,5,1,

        0,4,7,
        7,3,0,

        4,5,6,
        6,7,4,

        0,3,2,
        2,1,0,

        0,1,5,
        5,4,0,

        3,7,6,
        6,2,3
    };

    string faces[6];

    unsigned int skyboxVBO, skyboxVAO, skyboxEBO;
    unsigned int skyboxTexture;

    // Predetermined skybox patterns to load from
    std::string skyboxFace0[6]{
        "Models and Textures/Skybox/rainbow_rt.png",
        "Models and Textures/Skybox/rainbow_lf.png",
        "Models and Textures/Skybox/rainbow_up.png",
        "Models and Textures/Skybox/rainbow_dn.png",
        "Models and Textures/Skybox/rainbow_ft.png",
        "Models and Textures/Skybox/rainbow_bk.png"
    };

    std::string skyboxFace1[6]{
        "Models and Textures/Skybox/posx.jpg",
        "Models and Textures/Skybox/negx.jpg",
        "Models and Textures/Skybox/posy.jpg",
        "Models and Textures/Skybox/negy.jpg",
        "Models and Textures/Skybox/posz.jpg",
        "Models and Textures/Skybox/negz.jpg"
    };

public:
    Skybox(int skyboxFaceNumber);
    void Render(unsigned int skyboxShaderProgram, Camera* activeCameraPointer);

    void ChangeFaces(int skyboxFaceNumber);
};