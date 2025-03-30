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

PerspectiveCamera* perspectiveCameraPointer = nullptr;
OrthographicCamera* orthographicCameraPointer = nullptr;
Camera* activeCameraPointer = nullptr;
Object* playerCarPointer = nullptr;

void KeyHeldProcesses(){ 
    if (D_Held) playerCarPointer->Translate('R');
    if (A_Held) playerCarPointer->Translate('L');
    if (W_Held) playerCarPointer->Translate('F');
    if (S_Held) playerCarPointer->Translate('B');
    if (LEFT_SHIFT_Held) playerCarPointer->Translate('D');
    if (SPACE_Held) playerCarPointer->Translate('U');
    if (MINUS_Held) playerCarPointer->Scale(true);
    if (EQUAL_Held) playerCarPointer->Scale(false);
    if (UP_Held) playerCarPointer->Rotate('+', 'X');
    if (DOWN_Held) playerCarPointer->Rotate('-', 'X');
    if (LEFT_Held) playerCarPointer->Rotate('+', 'Y');
    if (RIGHT_Held) playerCarPointer->Rotate('-', 'Y');
    if (COMMA_Held) playerCarPointer->Rotate('+', 'Z');
    if (PERIOD_Held) playerCarPointer->Rotate('-', 'Z');
    if (J_Held) activeCameraPointer->MovePosition('L');
    if (L_Held) activeCameraPointer->MovePosition('R');
    if (K_Held) activeCameraPointer->MovePosition('D');
    if (I_Held) activeCameraPointer->MovePosition('U');
    if (U_Held) activeCameraPointer->MovePosition('B');
    if (O_Held) activeCameraPointer->MovePosition('F');
    if (F_Held) activeCameraPointer->Rotate('L');
    if (H_Held) activeCameraPointer->Rotate('R');
    if (G_Held) activeCameraPointer->Rotate('D');
    if (T_Held) activeCameraPointer->Rotate('U');
    if (TAB_Held) activeCameraPointer = orthographicCameraPointer;
        else activeCameraPointer = perspectiveCameraPointer;
}

int main()
{
    // Set Up Stuff
    SetUpGLFW();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Epik Kart Deluxe HD", NULL, NULL);
    SetUpWindow(window);

    // Make our objects
    PerspectiveCamera perspectiveCamera(glm::vec3(0, 40, 80), glm::vec3(-45, 0, 0));
    OrthographicCamera orthographicCamera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0));
    Object playerCar("Models and Textures/f1.obj", "Models and Textures/f1_specular.png", 0.2f);
    playerCar.SetPosition(glm::vec3(0, 0, 0));
    playerCar.SetRotation(glm::vec3(0, -90, 0));

    // Set our Pointers
    perspectiveCameraPointer = &perspectiveCamera;
    orthographicCameraPointer = &orthographicCamera;
    playerCarPointer = &playerCar;

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

        // Update Camera and Obj
        activeCameraPointer->Update(shaderProgram, SCR_WIDTH, SCR_HEIGHT);
        playerCarPointer->Update(shaderProgram);

        // Lighting Stuff
        Light light(glm::vec3(0, 10, -5), glm::vec3(1, 1, 1), 0.65f, glm::vec3(1, 1, 1), 1.2f, 2.0f);
        light.Render(shaderProgram, activeCameraPointer);

        // Rendering Object
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        playerCarPointer->Render(shaderProgram);

        // Check Events and Swap Buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}