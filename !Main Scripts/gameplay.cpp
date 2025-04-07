#include "gameplay.h"


Gaming::Gaming(Timer* timer){
    this->game_running = true;
    timer->Start();

    timeIsRunning = true;

    /// Setup Camera Pointers
    PerspectiveCamera* ThirdPersonCamera = new PerspectiveCamera(glm::vec3(0, 85, 50), 0, -30);
    PerspectiveCamera* FirstPersonCamera = new PerspectiveCamera(glm::vec3(0, 30, 0), 0, 0);
    this->thirdPersonCameraPointer = ThirdPersonCamera;
    this->firstPersonCameraPointer = FirstPersonCamera;
    this->activeCameraPointer = ThirdPersonCamera;
    this->thirdPerson = true;

    /// Setup Object Variables

    // Player Car
    this->playerCarPointer = new Object("Models and Textures/Car OBJs/ice_cream_van.obj", "Models and Textures/Car Textures/ice_cream_van_texture.png", 0, "RGBA", 0.15f);
    this->playerCarPointer->SetForward(glm::vec3(1, 0, 0));
    this->playerCarPointer->SetPosition(glm::vec3(0, 0, 0));
    this->playerCarPointer->SetRotation(glm::vec3(0, 90, 0));
    this->playerCarPointer->SetSpeed(0);

    // Fast F1 Car
    this->fastCarPointer = new Object("Models and Textures/Car OBJs/f1.obj", "Models and Textures/Car Textures/f1_specular.png", 1, "RGB", .3f);
    this->fastCarPointer->SetForward(glm::vec3(1, 0, 0));
    this->fastCarPointer->SetPosition(glm::vec3(150, 0, 0));
    this->fastCarPointer->SetRotation(glm::vec3(0, 90, 0));

    // Slow Bumper Car
    this->slowCarPointer = new Object("Models and Textures/Car OBJs/bumper_car.obj", "Models and Textures/Car Textures/bumper_car_texture.png", 2, "RGB", .25f);
    this->slowCarPointer->SetForward(glm::vec3(1, 0, 0));
    this->slowCarPointer->SetPosition(glm::vec3(-150, 0, 0));
    this->slowCarPointer->SetRotation(glm::vec3(0, 90, 0));

    // Grass Plane
    this->grassPlanePointer = new Object ("Models and Textures/grass.obj", "Models and Textures/grass_texture.jpg", 3, "RGB", 10.f);
    grassPlanePointer->SetRotation(glm::vec3(-90, 0, 0));
    grassPlanePointer->SetPosition(glm::vec3(0, -85, 0));
    
    this->shaderProgram = CreateShaderProgram("Shaders/sample.vert", "Shaders/sample.frag");
    this->skyboxShaderProgram = CreateShaderProgram("Shaders/skybox.vert", "Shaders/skybox.frag");
    
   // Set up Lights
    this->directionalLightPointer = new Light (glm::vec3(0, 0, 0), glm::vec3(.8f, .55f, .2f), 0.6f, glm::vec3(1, 1, 1), 1.f, 2.f);
    this->directionalLightPointer->SetDirectional(true);
    this->directionalLightPointer->SetRotation(glm::vec3(0, 90, 45));
    directionalLightPointer->Update();

    this->playerLightLeftPointer = new Light (glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.15f, glm::vec3(1, 1, 1), 1.5f, 5.0f);
    this->playerLightRightPointer = new Light (glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.15f, glm::vec3(1, 1, 1), 1.5f, 5.0f);
    this->fastCarLightLeftPointer = new Light (glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.15f, glm::vec3(1, 1, 1), 1.5f, 5.0f);
    this->fastCarLightRightPointer = new Light (glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.15f, glm::vec3(1, 1, 1), 1.5f, 5.0f);
    this->slowCarLightLeftPointer = new Light (glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.15f, glm::vec3(1, 1, 1), 1.5f, 5.0f);
    this->slowCarLightRightPointer = new Light (glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.15f, glm::vec3(1, 1, 1), 1.5f, 5.0f);

    this->startingSpotLightPointer = new Light (glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), 0.6f, glm::vec3(1, 1, 1), 1.f, 2.0f);
    startingSpotLightPointer->SetPosition(glm::vec3(0, 0, -50));
    startingSpotLightPointer->SetRotation(glm::vec3(0, 0, 180));

    // Set Up Skybox
    this->skyboxPointer = new Skybox(0);

}

PerspectiveCamera* Gaming::getThirdPersonCamera(){return thirdPersonCameraPointer;}
PerspectiveCamera* Gaming::getFirstPersonCamera(){return firstPersonCameraPointer;}
Camera* Gaming::getActiveCamera(){return activeCameraPointer;}
void Gaming::setActiveCamera(PerspectiveCamera* view){
    activeCameraPointer = view;
}

void Gaming::ToggleCamera(){
    if (activeCameraPointer == firstPersonCameraPointer){
        setThirdPerson(true);
        activeCameraPointer = thirdPersonCameraPointer;
    }
    else{
        setThirdPerson(false);
        activeCameraPointer = firstPersonCameraPointer;
    }
}

Object* Gaming::getPlayer(){return playerCarPointer;}
Object* Gaming::getFastCar(){return fastCarPointer;}
Object* Gaming::getSlowCar(){return slowCarPointer;}

Light* Gaming::GetPlayerLightLeftPointer(){return playerLightLeftPointer;}
Light* Gaming::GetPlayerLightRightPointer(){return playerLightRightPointer;}
Light* Gaming::GetFastCarLightLeftPointer(){return fastCarLightLeftPointer;}
Light* Gaming::GetFastCarLightRightPointer(){return fastCarLightRightPointer;}
Light* Gaming::GetSlowLightLeftPointer(){return slowCarLightLeftPointer;}
Light* Gaming::GetSlowLightRightPointer(){return slowCarLightRightPointer;}

unsigned int Gaming::getShaderProg(){return shaderProgram;}
unsigned int Gaming::getSkyboxProg(){return skyboxShaderProgram;}

void Gaming::Update(Timer* timer){

    thirdPersonCameraPointer->SetPosition({playerCarPointer->GetPosition().x, playerCarPointer->GetPosition().y + 120, playerCarPointer->GetPosition().z + 90});
    firstPersonCameraPointer->SetPosition({playerCarPointer->GetPosition().x, playerCarPointer->GetPosition().y + 30, playerCarPointer->GetPosition().z - 10});

    // After rendering skybox, enable depth writing again for cars
    glDepthMask(GL_TRUE);  // Enable depth mask for subsequent rendering

    // Object Updates
    {
    activeCameraPointer->Update(shaderProgram, SCR_WIDTH, SCR_HEIGHT);
    playerCarPointer->Update(shaderProgram, "transform0", 0);
    fastCarPointer->Update(shaderProgram, "transform1", 1);
    slowCarPointer->Update(shaderProgram, "transform2", 2);
    grassPlanePointer->Update(shaderProgram, "transform3", 3);
    }

    // Timer events
    {
    if (timeIsRunning && timer->getTime() >= 3) this->playerCarPointer->SetSpeed(2.75f);
    if (timeIsRunning && timer->getTime() >= 3) fastCarPointer->MoveForward(3.5); // 3.5
    if (timeIsRunning && timer->getTime() >= 3) slowCarPointer->MoveForward(1.2); // 1.2

    startingSpotLightPointer->Update();

    if (timer->getTime() >= 1) startingSpotLightPointer->SetColor(glm::vec3(10.f, .0f, 0));
    if (timer->getTime() >= 2) startingSpotLightPointer->SetColor(glm::vec3(7.f, 7.f, 0));
    if (timer->getTime() >= 3) startingSpotLightPointer->SetColor(glm::vec3(0.0f, 10.f, 0));
    if (timer->getTime() >= 4) startingSpotLightPointer->SetColor(glm::vec3(0.0f, 0.f, 0));
    }

    // Only make the special lighting stuff at night to save computation
    if (!timeIsDay){
        playerLightLeftPointer->PositionFromCar(playerCarPointer, glm::vec3(-15.f, 18, 65.f));
        playerLightRightPointer->PositionFromCar(playerCarPointer, glm::vec3(15.f, 18, 65.f));
        fastCarLightLeftPointer->PositionFromCar(fastCarPointer, glm::vec3(-5.f, 10, 45.f));
        fastCarLightRightPointer->PositionFromCar(fastCarPointer, glm::vec3(5.f, 10, 45.f));
        slowCarLightLeftPointer->PositionFromCar(slowCarPointer, glm::vec3(-6.f, 5, 25.f));
        slowCarLightRightPointer->PositionFromCar(slowCarPointer, glm::vec3(6.f, 5, 25.f));

        playerLightLeftPointer->Update();
        playerLightRightPointer->Update();
        fastCarLightLeftPointer->Update();
        fastCarLightRightPointer->Update();
        slowCarLightLeftPointer->Update();
        slowCarLightRightPointer->Update();
    }
    
    runRace(timer);
}

void Gaming::Render(){

    skyboxPointer->Render(getSkyboxProg(), getActiveCamera());

    if (activeCameraPointer == thirdPersonCameraPointer) playerCarPointer->Render(shaderProgram, 0, 0);
    fastCarPointer->Render(shaderProgram, 1, 1);
    slowCarPointer->Render(shaderProgram, 2, 2);
    grassPlanePointer->Render(shaderProgram, 3, 3);

    directionalLightPointer->Render(getShaderProg(), getActiveCamera(), 0);

    if (!timeIsDay){
        playerLightLeftPointer->Render(getShaderProg(), getActiveCamera(), 1);
        playerLightRightPointer->Render(getShaderProg(), getActiveCamera(), 2);
        fastCarLightLeftPointer->Render(getShaderProg(), getActiveCamera(), 3);
        fastCarLightRightPointer->Render(getShaderProg(), getActiveCamera(), 4);
        slowCarLightLeftPointer->Render(getShaderProg(), getActiveCamera(), 5);
        slowCarLightRightPointer->Render(getShaderProg(), getActiveCamera(), 6);
    }

    startingSpotLightPointer->Render(getShaderProg(), getActiveCamera(), 7);
}


void Gaming::runRace(Timer* timer){

    if(playerCarPointer->GetPosition().z <= -1000 && Player_Cross == false){
        steady_clock::time_point time = steady_clock::now();
        auto duration = duration_cast<seconds>(time - timer->getStart());
        cout << "PLAYER crossed the finish line at " << duration.count()-3 << " seconds!" << endl;
        Player_Cross = true;
    }

    if(fastCarPointer->GetPosition().z <= -1000 && Fast_Cross == false){
        steady_clock::time_point time = steady_clock::now();
        auto duration = duration_cast<seconds>(time - timer->getStart());
        cout << "FAST CAR crossed the finish line at " << duration.count()-3 << " seconds!" << endl;
        Fast_Cross = true;
    }

    if(slowCarPointer->GetPosition().z <= -1000 && Slow_Cross == false){
        steady_clock::time_point time = steady_clock::now();
        auto duration = duration_cast<seconds>(time - timer->getStart());
        cout << "SLOW CAR crossed the finish line at " << duration.count()-3 << " seconds!" << endl;
        Slow_Cross = true;
    }

    if (Player_Cross && Fast_Cross && Slow_Cross && !All_Cross){
        steady_clock::time_point time = steady_clock::now();
        auto duration = duration_cast<seconds>(time - timer->getStart());
        cout << "\n\n\n----\nFINISH!\n----ALL CARS crossed the finish line at " << duration.count()-3 << " seconds!" << endl;
        All_Cross = true;
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

void Gaming::ToggleTime(){
    timeIsRunning = !timeIsRunning;
}

void Gaming::setThirdPerson(bool val){
    thirdPerson = val;
}

bool Gaming::getThirdPerson(){return thirdPerson;}



void Gaming::endRace(Timer* timer){
    timer->Stop();
}

void Gaming::SetToDay(bool value){
    timeIsDay = value;

    if (value == true){
        skyboxPointer->ChangeFaces(0);
        playerLightLeftPointer->SetColor(glm::vec3(0, 0, 0));
        playerLightRightPointer->SetColor(glm::vec3(0, 0, 0));
        fastCarLightLeftPointer->SetColor(glm::vec3(0, 0, 0));
        fastCarLightRightPointer->SetColor(glm::vec3(0, 0, 0));
        slowCarLightLeftPointer->SetColor(glm::vec3(0, 0, 0));
        slowCarLightRightPointer->SetColor(glm::vec3(0, 0, 0));
        // Re-rendering
        {
        playerLightLeftPointer->Render(getShaderProg(), getActiveCamera(), 1);
        playerLightRightPointer->Render(getShaderProg(), getActiveCamera(), 2);
        fastCarLightLeftPointer->Render(getShaderProg(), getActiveCamera(), 3);
        fastCarLightRightPointer->Render(getShaderProg(), getActiveCamera(), 4);
        slowCarLightLeftPointer->Render(getShaderProg(), getActiveCamera(), 5);
        slowCarLightRightPointer->Render(getShaderProg(), getActiveCamera(), 6);
        }

        directionalLightPointer->SetRotation(glm::vec3(0, 90, 45));
        directionalLightPointer->SetColor(glm::vec3(.8f, .55f, .2f));
    }
    else{
        skyboxPointer->ChangeFaces(1);

        playerLightLeftPointer->SetColor(glm::vec3(1, 1, 1));
        playerLightRightPointer->SetColor(glm::vec3(1, 1, 1));
        fastCarLightLeftPointer->SetColor(glm::vec3(1, 1, 1));
        fastCarLightRightPointer->SetColor(glm::vec3(1, 1, 1));
        slowCarLightLeftPointer->SetColor(glm::vec3(1, 1, 1));
        slowCarLightRightPointer->SetColor(glm::vec3(1, 1, 1));

        directionalLightPointer->SetRotation(glm::vec3(-30, 90, -45));
        directionalLightPointer->SetColor(glm::vec3(.3f, .3f, .65f));
    }
}

bool Gaming::GetTimeIsDay(){return timeIsDay;}