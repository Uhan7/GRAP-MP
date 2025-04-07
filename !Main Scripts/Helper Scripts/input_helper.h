#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Since OpenGL is silly af and doesn't have a GLFW_HELD, let's make our own with this
bool D_Held, A_Held, W_Held, S_Held, LEFT_SHIFT_Held,
    MINUS_Held, EQUAL_Held,
    UP_Held, DOWN_Held, LEFT_Held, RIGHT_Held, COMMA_Held, PERIOD_Held,
    J_Held, L_Held, K_Held, I_Held, U_Held, O_Held,
    F_Held, H_Held, T_Held, G_Held,
    TAB_Held,
    Q_Pressed, E_Pressed, Q_CanPress=true, E_CanPress=true,
    SPACE_Pressed = false, SPACE_CanPress = true,
    Z_Pressed = false, Z_CanPress = true;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_D) D_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_A) A_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_W) W_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_S) S_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_Q && action == GLFW_PRESS){
        Q_Pressed = true;
    } else if (key == GLFW_KEY_Q && action == GLFW_RELEASE){
        Q_Pressed = false;
        Q_CanPress = true;
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS){
        E_Pressed = true;
    } else if (key == GLFW_KEY_E && action == GLFW_RELEASE){
        E_Pressed = false;
        E_CanPress = true;
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        SPACE_Pressed = true;
    } else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE){
        SPACE_Pressed = false;
        SPACE_CanPress = true;
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS){
        Z_Pressed = true;
    } else if (key == GLFW_KEY_Z && action == GLFW_RELEASE){
        Z_Pressed = false;
        Z_CanPress = true;
    }
    if (key == GLFW_KEY_LEFT_SHIFT) LEFT_SHIFT_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_MINUS) MINUS_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_EQUAL) EQUAL_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_UP) UP_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_DOWN) DOWN_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_LEFT) LEFT_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_RIGHT) RIGHT_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_COMMA) COMMA_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_PERIOD) PERIOD_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_J) J_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_L) L_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_K) K_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_I) I_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_U) U_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_O) O_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_F) F_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_H) H_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_G) G_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_T) T_Held = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_TAB) TAB_Held = (action != GLFW_RELEASE);
}

void HandleInputs(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    
    glfwSetKeyCallback(window, KeyCallback);
}