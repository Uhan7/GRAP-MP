#include "timer.h"


Timer::Timer(){
}

void Timer::Start(){
    player_active = true;
    fast_active = true;
    slow_active = true;

    start = steady_clock::now();
}

steady_clock::time_point Timer::getStart(){return start;}

bool Timer::getActive(int index){

    switch(index){
        case 0: return player_active; break;
        case 1: return fast_active; break;
        case 2: return slow_active; break;
    }
    return 0;
}


void Timer::toggleActive(int index){

    switch(index){
        case 0: player_active = false;
        case 1: fast_active = false;
        case 2: slow_active = false;
    }
}

void Timer::Stop(){
    ending = steady_clock::now();
    auto duration = duration_cast<seconds>(ending - start);
}