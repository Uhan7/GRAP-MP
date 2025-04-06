
// Other C++ Stuff
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "gameplay.cpp"
#include "timer.cpp"


PerspectiveCamera* thirdPersonCameraPointer = nullptr;
PerspectiveCamera* firstPersonCameraPointer = nullptr;
Camera* activeCameraPointer = thirdPersonCameraPointer;

Object* playerCarPointer = nullptr;
Object* fastCarPointer = nullptr;
Object* slowCarPointer = nullptr;

Light* light1Pointer = nullptr;
Light* light2Pointer = nullptr;

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
//     if (TAB_Held) activeCameraPointer = firstPersonCameraPointer;
//         else activeCameraPointer = thirdPersonCameraPointer;
// }

void KeyHeldProcesses(Gaming* program){
    if (W_Held){
        program->getPlayer()->MoveForward(2.75);
        light1Pointer->SetColor(glm::vec3(2, 2, 2));
        light2Pointer->SetColor(glm::vec3(2, 2, 2));
    }
    if (S_Held){
        program->getPlayer()->MoveForward(-2.75);
        light1Pointer->SetColor(glm::vec3(5, 0, 0));
        light2Pointer->SetColor(glm::vec3(5, 0, 0));
    }
    if (A_Held){
        program->getPlayer()->Rotate('-', 'Y');
        program->getFirstPersonCamera()->Rotate('L');
    }
    if (D_Held){
        program->getPlayer()->Rotate('+', 'Y');
        program->getFirstPersonCamera()->Rotate('R');
    }
    // if (UP_Held) fastCarPointer->MoveForward(3);
    // if (DOWN_Held) fastCarPointer->MoveForward(-3);
    // if (LEFT_Held) fastCarPointer->Rotate('-', 'Y');
    // if (RIGHT_Held) fastCarPointer->Rotate('+', 'Y');
    if (TAB_Held)
    {
        program->setActiveCamera(program->getFirstPersonCamera());
    } else program->setActiveCamera(program->getThirdPersonCamera());
}

/// Mouse Processing with respect to the position of the mouse. 
void MouseProcesses(GLFWwindow* window, bool ortographic_view, Camera* Camera){

    double Curr_Pos_x, Curr_Pos_y;
    if (ortographic_view == true) { /// TRUE when in ortographic_view.

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) { /// TRUE when left click is held
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            glfwGetCursorPos(window, &Curr_Pos_x, &Curr_Pos_y);
            if (Camera->GetMouse_XPos() > Curr_Pos_x) { //TRUE when the Mouse is moved to the left
                Camera->Rotate('L');
            } else if (Camera->GetMouse_XPos() < Curr_Pos_x) { // TRUE when the Mouse is moved to the right
                Camera->Rotate('R');
            }
            
            if (Camera->GetMouse_YPos() > Curr_Pos_x){
                Camera->Rotate('U');
            } else if(Camera->GetMouse_YPos()> Curr_Pos_y){
                Camera->Rotate('D');
            }

        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) { /// TRUE when left click is released
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        Camera->UpdateMousePos(Curr_Pos_x, Curr_Pos_y);
    }
}

int main()
{
    // Set Up Stuff
    SetUpGLFW();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Epik Kart Deluxe HD", NULL, NULL);
    SetUpWindow(window);

    Timer* timer = new Timer();
    Gaming Program = Gaming(timer);

    Light light1(glm::vec3(0, 10, -5), glm::vec3(1, 1, 1), 0.8f, glm::vec3(1, 1, 1), 1.f, 1.0f);
    Light light2(glm::vec3(0, 10, -5), glm::vec3(1, 1, 1), 0.8f, glm::vec3(1, 1, 1), 1.f, 1.0f);

    light1Pointer = &light1;
    light2Pointer = &light2;

    Skybox skybox(0);

    while(!glfwWindowShouldClose(window))
    {   
        // Inputs
        HandleInputs(window);
        // KeyHeldProcesses(currentGameStatePointer);
        KeyHeldProcesses(&Program);
        MouseProcesses(window, true, Program.getActiveCamera());

        // Rendering BG
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Lighting Stuff
        light1.SetRotation(Program.getPlayer()->GetRotation());
        light1.SetPosition(Program.getPlayer()->GetPosition());
        light1.SetForward(Program.getPlayer()->GetForward());
        light1.MoveForward(20.f);
        light1.MoveSide(6.f);
        
        light2.SetRotation(Program.getPlayer()->GetRotation());
        light2.SetPosition(Program.getPlayer()->GetPosition());
        light2.SetForward(Program.getPlayer()->GetForward());
        light2.MoveForward(20.f);
        light2.MoveSide(-6.f);

        light1.Update();
        light2.Update();

        light1.Render(Program.getShaderProg(), Program.getActiveCamera(), 0);
        light2.Render(Program.getShaderProg(), Program.getActiveCamera(), 1);

        // Game update
        Program.Update(timer);

        //Render
        skybox.Render(Program.getSkyboxProg(), Program.getActiveCamera());
        Program.Render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}