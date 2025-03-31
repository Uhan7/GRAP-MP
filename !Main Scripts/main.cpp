// Default Stuff for OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Other C++ Stuff
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Referenced Scripts
#include "setup.cpp"
#include "settings.h"
#include "shaders.cpp"
#include "object.cpp"
#include "Camera Scripts/camera.cpp"
#include "Camera Scripts/perspective_camera.cpp"
#include "Camera Scripts/orthographic_camera.cpp"
#include "light.cpp"

#include "Helper Scripts/input_helper.h"
#include "Helper Scripts/debug_help.h"

PerspectiveCamera* perspectiveCameraPointer = nullptr;
OrthographicCamera* orthographicCameraPointer = nullptr;
Camera* activeCameraPointer = nullptr;

Object* playerCarPointer = nullptr;
Object* fastCarPointer = nullptr;
Object* slowCarPointer = nullptr;

// void KeyHeldProcesses(){ 
//     if (D_Held) playerCarPointer->Translate('R');
//     if (A_Held) playerCarPointer->Translate('L');
//     if (W_Held) playerCarPointer->Translate('F');
//     if (S_Held) playerCarPointer->Translate('B');
//     if (LEFT_SHIFT_Held) playerCarPointer->Translate('D');
//     if (SPACE_Held) playerCarPointer->Translate('U');
//     if (MINUS_Held) playerCarPointer->Scale(true);
//     if (EQUAL_Held) playerCarPointer->Scale(false);
//     if (UP_Held) playerCarPointer->Rotate('+', 'X');
//     if (DOWN_Held) playerCarPointer->Rotate('-', 'X');
//     if (LEFT_Held) playerCarPointer->Rotate('+', 'Y');
//     if (RIGHT_Held) playerCarPointer->Rotate('-', 'Y');
//     if (COMMA_Held) playerCarPointer->Rotate('+', 'Z');
//     if (PERIOD_Held) playerCarPointer->Rotate('-', 'Z');
//     if (J_Held) activeCameraPointer->MovePosition('L');
//     if (L_Held) activeCameraPointer->MovePosition('R');
//     if (K_Held) activeCameraPointer->MovePosition('D');
//     if (I_Held) activeCameraPointer->MovePosition('U');
//     if (U_Held) activeCameraPointer->MovePosition('B');
//     if (O_Held) activeCameraPointer->MovePosition('F');
//     if (F_Held) activeCameraPointer->Rotate('L');
//     if (H_Held) activeCameraPointer->Rotate('R');
//     if (G_Held) activeCameraPointer->Rotate('D');
//     if (T_Held) activeCameraPointer->Rotate('U');
//     if (TAB_Held) activeCameraPointer = orthographicCameraPointer;
//         else activeCameraPointer = perspectiveCameraPointer;
// }

void KeyHeldProcesses(){
    if (W_Held) playerCarPointer->MoveForward(2.75);
    if (S_Held) playerCarPointer->MoveForward(2.75);
    if (A_Held) playerCarPointer->Rotate('-', 'Y');
    if (D_Held) playerCarPointer->Rotate('+', 'Y');
    // if (UP_Held) fastCarPointer->MoveForward(3);
    // if (DOWN_Held) fastCarPointer->MoveForward(-3);
    // if (LEFT_Held) fastCarPointer->Rotate('-', 'Y');
    // if (RIGHT_Held) fastCarPointer->Rotate('+', 'Y');
    if (TAB_Held) activeCameraPointer = orthographicCameraPointer;
        else activeCameraPointer = perspectiveCameraPointer;
}

int main()
{
    // Set Up Stuff
    SetUpGLFW();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Epik Kart Deluxe HD", NULL, NULL);
    SetUpWindow(window);

    // Make our Cameras
    PerspectiveCamera perspectiveCamera(glm::vec3(0, 85, 50), 0, -30);
    OrthographicCamera orthographicCamera(glm::vec3(0, 75, 65), 0, -90);

    // Then our cars
    Object playerCar("Models and Textures/ice_cream_van.obj", "Models and Textures/ice_cream_van_texture.png", 0, "RGBA", 0.15f);
    playerCar.SetForward(glm::vec3(1, 0, 0));
    playerCar.SetPosition(glm::vec3(0, 0, 0));
    playerCar.SetRotation(glm::vec3(0, 90, 0));

    std::cout<<"yabadabadoo"<<std::endl;

    Object fastCar("Models and Textures/f1.obj", "Models and Textures/f1_specular.png", 1, "RGB", .3f);
    fastCar.SetForward(glm::vec3(1, 0, 0));
    fastCar.SetPosition(glm::vec3(150, 0, 0));
    fastCar.SetRotation(glm::vec3(0, 90, 0));

    std::cout<<"yabadaba\ttwo"<<std::endl;

    Object slowCar("Models and Textures/bumper_car.obj", "Models and Textures/bumper_car_texture.png", 2, "RGB", .25f);
    slowCar.SetForward(glm::vec3(1, 0, 0));
    slowCar.SetPosition(glm::vec3(-150, 0, 0));
    slowCar.SetRotation(glm::vec3(0, 90, 0));

    std::cout<<"threep!"<<std::endl;

    // Set our Pointers
    perspectiveCameraPointer = &perspectiveCamera;
    orthographicCameraPointer = &orthographicCamera;
    playerCarPointer = &playerCar;
    fastCarPointer = &fastCar;
    slowCarPointer = &slowCar;

    // Shaderz
    unsigned int shaderProgram = CreateShaderProgram("Shaders/sample.vert", "Shaders/sample.frag");
    unsigned int skyboxShaderProgram = CreateShaderProgram("Shaders/skybox.vert", "Shaders/skybox.frag");

    // Render Loop every FRAME
    while(!glfwWindowShouldClose(window))
    {   
        // Inputs, create a Game State for it
        HandleInputs(window);
        // KeyHeldProcesses(currentGameStatePointer);
        KeyHeldProcesses();

        // Rendering BG
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Lighting Stuff
        Light light(glm::vec3(0, 10, -5), glm::vec3(1, 1, 1), 0.8f, glm::vec3(1, 1, 1), 1.f, 1.0f);
        light.Render(shaderProgram, activeCameraPointer);

        // Update Camera and Cars
        activeCameraPointer->Update(shaderProgram, SCR_WIDTH, SCR_HEIGHT);
        playerCarPointer->Update(shaderProgram, "transform0", 0);
        fastCarPointer->Update(shaderProgram, "transform1", 1);
        slowCarPointer->Update(shaderProgram, "transform2", 2);

        // Rendering Object
        playerCarPointer->Render(shaderProgram, 0, 0);
        fastCarPointer->Render(shaderProgram, 1, 1);
        slowCarPointer->Render(shaderProgram, 2, 2);

        // Move Other Cars
        fastCarPointer->MoveForward(3.5);
        slowCarPointer->MoveForward(2.25);

        // Debug Messages
        // PrintVector(playerCarPointer->GetPosition());

        // Check Events and Swap Buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}