#pragma once

#include "object.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;



class Timer{
    private:
        steady_clock::time_point start;
        steady_clock::time_point ending;

        bool active;

    public:
        Timer();
        void Start(){active = true;}
        void Stop();
};


class Gaming{

    private:
        bool game_running = false;

    public:
        bool stillRacing(Object* player, Object* fastcar, Object* slowcar);
        void endRace(Timer* timer);



};