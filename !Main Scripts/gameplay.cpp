#include "gameplay.h"


Gaming::Gaming(Timer* timer){
    this->game_running = true;
    timer->Start();

    /// Setup Camera Pointers
    PerspectiveCamera* ThirdPersonCamera = new PerspectiveCamera(glm::vec3(0, 85, 50), 0, -30);
    PerspectiveCamera* FirstPersonCamera = new PerspectiveCamera(glm::vec3(0, 30, 0), 0, 0);
    this->thirdPersonCameraPointer = ThirdPersonCamera;
    this->firstPersonCameraPointer = FirstPersonCamera;
    this->activeCameraPointer = ThirdPersonCamera;


   /// Setup Object Variables

   this->playerCarPointer = new Object("Models and Textures/ice_cream_van.obj", "Models and Textures/ice_cream_van_texture.png", 0, "RGBA", 0.15f);
   this->playerCarPointer->SetForward(glm::vec3(1, 0, 0));
   this->playerCarPointer->SetPosition(glm::vec3(0, 0, 0));
   this->playerCarPointer->SetRotation(glm::vec3(0, 90, 0));

   this->fastCarPointer = new Object("Models and Textures/f1.obj", "Models and Textures/f1_specular.png", 1, "RGB", .3f);
   this->fastCarPointer->SetForward(glm::vec3(1, 0, 0));
   this->fastCarPointer->SetPosition(glm::vec3(150, 0, 0));
   this->fastCarPointer->SetRotation(glm::vec3(0, 90, 0));

   this->slowCarPointer = new Object("Models and Textures/bumper_car.obj", "Models and Textures/bumper_car_texture.png", 2, "RGB", .25f);
   this->slowCarPointer->SetForward(glm::vec3(1, 0, 0));
   this->slowCarPointer->SetPosition(glm::vec3(-150, 0, 0));
   this->slowCarPointer->SetRotation(glm::vec3(0, 90, 0));

   this->shaderProgram = CreateShaderProgram("Shaders/sample.vert", "Shaders/sample.frag");
   this->skyboxShaderProgram = CreateShaderProgram("Shaders/skybox.vert", "Shaders/skybox.frag");

}

PerspectiveCamera* Gaming::getThirdPersonCamera(){return thirdPersonCameraPointer;}
PerspectiveCamera* Gaming::getFirstPersonCamera(){return firstPersonCameraPointer;}
Camera* Gaming::getActiveCamera(){return activeCameraPointer;}
void Gaming::setActiveCamera(PerspectiveCamera* view){
    activeCameraPointer = view;
}

Object* Gaming::getPlayer(){return playerCarPointer;}
Object* Gaming::getFastCar(){return fastCarPointer;}
Object* Gaming::getSlowCar(){return slowCarPointer;}

unsigned int Gaming::getShaderProg(){return shaderProgram;}
unsigned int Gaming::getSkyboxProg(){return skyboxShaderProgram;}

void Gaming::InitiateObjects(){

}

void Gaming::Update(Timer* timer){
    thirdPersonCameraPointer->SetPosition({playerCarPointer->GetPosition().x, playerCarPointer->GetPosition().y + 120, playerCarPointer->GetPosition().z + 90});
    firstPersonCameraPointer->SetPosition({playerCarPointer->GetPosition().x, playerCarPointer->GetPosition().y + 30, playerCarPointer->GetPosition().z});

    activeCameraPointer->Update(shaderProgram, SCR_WIDTH, SCR_HEIGHT);
    playerCarPointer->Update(shaderProgram, "transform0", 0);
    fastCarPointer->Update(shaderProgram, "transform1", 1);
    slowCarPointer->Update(shaderProgram, "transform2", 2);

    if (activeCameraPointer == thirdPersonCameraPointer) playerCarPointer->Render(shaderProgram, 0, 0);
    fastCarPointer->Render(shaderProgram, 1, 1);
    slowCarPointer->Render(shaderProgram, 2, 2);

    fastCarPointer->MoveForward(3.5);
    slowCarPointer->MoveForward(1.25);

    runRace(timer);

}


void Gaming::runRace(Timer* timer){

    if(playerCarPointer->GetPosition().z <= -1000 && Player_Cross == false){
        steady_clock::time_point time = steady_clock::now();
        auto duration = duration_cast<seconds>(time - timer->getStart());
        cout << "PLAYER crossed the finish line at " << duration.count() << "seconds!" << endl;
        Player_Cross = true;
    }

    if(fastCarPointer->GetPosition().z <= -1000 && Fast_Cross == false){
        steady_clock::time_point time = steady_clock::now();
        auto duration = duration_cast<seconds>(time - timer->getStart());
        cout << "FAST CAR crossed the finish line at " << duration.count() << "seconds!" << endl;
        Fast_Cross = true;
    }

    if(slowCarPointer->GetPosition().z <= -1000 && Slow_Cross == false){
        steady_clock::time_point time = steady_clock::now();
        auto duration = duration_cast<seconds>(time - timer->getStart());
        cout << "SLOW CAR crossed the finish line at " << duration.count() << "seconds!" << endl;
        Slow_Cross = true;
    }


    if(!stillRacing()){
        game_running = false;
        endRace(timer);
    }
}

bool Gaming::stillRacing(){
   // if(player->GetPosition() >= vec3(x,y,z) && fastcar->GetPosition() >= vec3(x,y,z) && fastcar->GetPosition() >= vec3(x,y,z))
   if(playerCarPointer->GetPosition().z <= -1000.f && fastCarPointer->GetPosition().z <= -1000.f && slowCarPointer->GetPosition().z == -1000.f)
   {    
        return true;
   }
   return false;
}

void Gaming::endRace(Timer* timer){
    timer->Stop();
}