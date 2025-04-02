#include "gameplay.h"


Timer::Timer(){
    active = false;
}

void Timer::Start(){
    active = true;
    start = steady_clock::now();
}

void Timer::Stop(){
    active = false;
    ending = steady_clock::now();

    auto duration = duration_cast<seconds>(ending - start);
    cout << "All vehicles crossed the finishline at " << duration.count() << "seconds!" << endl;

}



bool Gaming::stillRacing(Object* player, Object* fastcar, Object* slowcar){

    // Still an arbitrary finishline
   // if(player->GetPosition() >= vec3(x,y,z) && fastcar->GetPosition() >= vec3(x,y,z) && fastcar->GetPosition() >= vec3(x,y,z))
   {
        return true;
   }
   
   return false;

}

void Gaming::endRace(Timer* timer){
    timer->Stop();
}