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

        bool player_active;
        bool fast_active;
        bool slow_active;

    public:
        Timer();
        steady_clock::time_point getStart();
        void Start();
        
        bool getActive(int index);
        void toggleActive(int index);
        void Stop();
};