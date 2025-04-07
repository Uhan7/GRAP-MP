
// Other C++ Stuff
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "gameplay.cpp"
#include "timer.cpp"

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
        if (!program->GetTimeIsDay()) program->GetPlayerLightLeftPointer()->SetColor(glm::vec3(1, 1, 1));
        if (!program->GetTimeIsDay()) program->GetPlayerLightRightPointer()->SetColor(glm::vec3(1, 1, 1));
    }
    if (S_Held){
        program->getPlayer()->MoveForward(-2.75);
        if (!program->GetTimeIsDay()) program->GetPlayerLightLeftPointer()->SetColor(glm::vec3(1, 0, 0));
        if (!program->GetTimeIsDay()) program->GetPlayerLightRightPointer()->SetColor(glm::vec3(1, 0, 0));
    } else{
        if (!program->GetTimeIsDay() && !W_Held) program->GetPlayerLightLeftPointer()->SetColor(glm::vec3(.5f, .5f, .5f));
        if (!program->GetTimeIsDay() && !W_Held) program->GetPlayerLightRightPointer()->SetColor(glm::vec3(.5f, .5f, .5f));
    }
    if (A_Held){
        program->getPlayer()->Rotate('-', 'Y');
        program->getFirstPersonCamera()->Rotate('L');
    }
    if (D_Held){
        program->getPlayer()->Rotate('+', 'Y');
        program->getFirstPersonCamera()->Rotate('R');
    }
    if (Q_Pressed && Q_CanPress){
        program->SetToDay(true);
        Q_CanPress = false;
    }
    if (E_Pressed && E_CanPress){
        program->SetToDay(false);
        E_CanPress = false;
    }
    if (SPACE_Pressed && SPACE_CanPress){
        program->ToggleTime();
        SPACE_CanPress = false;
    }
    // if (UP_Held) fastCarPointer->MoveForward(3);
    // if (DOWN_Held) fastCarPointer->MoveForward(-3);
    // if (LEFT_Held) fastCarPointer->Rotate('-', 'Y');
    // if (RIGHT_Held) fastCarPointer->Rotate('+', 'Y');
    if (TAB_Held)
    {
        program->setActiveCamera(program->getFirstPersonCamera());
        program->setThirdPerson(false);
    } else{
        program->setActiveCamera(program->getThirdPersonCamera()); 
        program->setThirdPerson(true);
    } 
}

/// Mouse Processing with respect to the position of the mouse. 
void MouseProcesses(GLFWwindow* window, bool thirdperson, Camera* Camera){

    double Curr_Pos_x, Curr_Pos_y;
    double dx, dy;

    if (thirdperson == true) { /// TRUE when in third person view.

        std::cout << "I AM HERE, I SHOULD BE ON THIRD PERSON VIEW" << std::endl;


        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) { /// TRUE when left click is held
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            dx = Curr_Pos_x - Camera->GetMouse_XPos();
            dy = Curr_Pos_y - Camera->GetMouse_YPos();

            std::cout << "I SHOULD BE CLICKING ON LEFT CLICK!" << std::endl;

            glfwGetCursorPos(window, &Curr_Pos_x, &Curr_Pos_y);
            if (dx > 0) { //TRUE when the Mouse is moved to the left
                Camera->Rotate('J');
            } else if (dx < 0) { // TRUE when the Mouse is moved to the right
                Camera->Rotate('G');
            }
            
            if (dy > 0){
                Camera->Rotate('H');
            } else if(dy < 0){
                Camera->Rotate('Y');
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

    while(!glfwWindowShouldClose(window))
    {   
        // Inputs
        HandleInputs(window);
        // KeyHeldProcesses(currentGameStatePointer);
        KeyHeldProcesses(&Program);
        MouseProcesses(window, Program.getThirdPerson(), Program.getActiveCamera());

        // Rendering BG
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Game update
        Program.Update(timer);

        //Render
        Program.Render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}