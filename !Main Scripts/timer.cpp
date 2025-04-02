#include "timer.h"


Timer::Timer(){
    active = false;
}

void Timer::Start(){
    active = true;
    start = steady_clock::now();
}

steady_clock::time_point Timer::getStart(){return start;}

void Timer::Stop(){
    active = false;
    ending = steady_clock::now();

    auto duration = duration_cast<seconds>(ending - start);
    cout << "All vehicles crossed the finishline at " << duration.count() << "seconds!" << endl;

}