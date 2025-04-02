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
        void Start();
        void Stop();
};