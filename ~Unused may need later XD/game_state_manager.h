#pragma once

#include "object.h"
#include "Camera Scripts/camera.h"
#include "Camera Scripts/perspective_camera.h"
#include "Camera Scripts/orthographic_camera.h"

struct gameState {
    Camera* activeCameraPointer;
    Object* objPointer;

    gameState(Camera* activeCameraPointer, Object* objPointer):
        activeCameraPointer(activeCameraPointer),
        objPointer(objPointer){}
};