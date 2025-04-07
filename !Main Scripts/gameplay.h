#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Default Stuff for OpenGL

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "object.h"
#include "timer.h"

#include <iostream>
#include <chrono>
#include <thread>

#include "setup.cpp"
#include "settings.h"
#include "shaders.cpp"
#include "object.cpp"
#include "Camera Scripts/camera.cpp"
#include "Camera Scripts/perspective_camera.cpp"
#include "Camera Scripts/orthographic_camera.cpp"
#include "light.cpp"
#include "skybox.cpp"

#include "Helper Scripts/input_helper.h"
#include "Helper Scripts/debug_help.h"


class Gaming{
    private:
        bool game_running = false;
        bool Player_Cross = false;
        bool Fast_Cross = false;
        bool Slow_Cross = false;
        bool All_Cross = false;

        PerspectiveCamera* thirdPersonCameraPointer = nullptr;
        PerspectiveCamera* firstPersonCameraPointer = nullptr;
        Camera* activeCameraPointer = nullptr;

        Object* playerCarPointer = nullptr;
        Object* fastCarPointer = nullptr;
        Object* slowCarPointer = nullptr;

        Light* directionalLightPointer = nullptr;

        Light* playerLightLeftPointer = nullptr;
        Light* playerLightRightPointer = nullptr;
        Light* fastCarLightLeftPointer = nullptr;
        Light* fastCarLightRightPointer = nullptr;
        Light* slowCarLightLeftPointer = nullptr;
        Light* slowCarLightRightPointer = nullptr;

        Skybox* skyboxPointer = nullptr;

        unsigned int shaderProgram;
        unsigned int skyboxShaderProgram;

        bool timeIsDay = true;

    public:
        ///Gaming Constructor
        Gaming(Timer* timer);

        ///SetterGetter Functions

        PerspectiveCamera* getThirdPersonCamera();
        PerspectiveCamera* getFirstPersonCamera();
        Camera* getActiveCamera();
        void setActiveCamera(PerspectiveCamera* view);
        Object* getPlayer();
        Object* getFastCar();
        Object* getSlowCar();

        Light* GetPlayerLightLeftPointer();
        Light* GetPlayerLightRightPointer();
        Light* GetFastCarLightLeftPointer();
        Light* GetFastCarLightRightPointer();
        Light* GetSlowLightLeftPointer();
        Light* GetSlowLightRightPointer();

        unsigned int getShaderProg();
        unsigned int getSkyboxProg();

        /// RENDERING FUNCTIONS
        void InitiateObjects();
        void Update(Timer* timer);
        void Render();

        /// GAME LOOP FUNCTIONS
        bool stillRacing();
        void runRace(Timer* timer);
        void endRace(Timer* timer);

        void SetToDay(bool value);

        bool GetTimeIsDay();

};