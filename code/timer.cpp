//#include "stdafx.h"
#include "engine.h"

namespace Octane
{
    Timer::Timer()
    {
        UINT desired_scheduler_ms = 1;
        sleep_is_granular = (timeBeginPeriod(desired_scheduler_ms) == TIMERR_NOERROR);
        LARGE_INTEGER perf_count_frequency;
        QueryPerformanceFrequency(&perf_count_frequency);
        this->frequency = (int64_t)perf_count_frequency.QuadPart;
        this->reset();
    }

    Timer::~Timer()
    {
    
    }

    double Timer::get_elapsed()
    { 
        LARGE_INTEGER li_counter;
        QueryPerformanceCounter(&li_counter);
        int64_t elapsed = ((1000 * li_counter.QuadPart) / this->frequency); //get time pass in miliSeconds

        return (double)elapsed;
    }

    void Timer::rest(double ms)
    {
        double start = this->get_elapsed();
        while(start + ms > get_elapsed())
        {
            if(sleep_is_granular)
            {
                Sleep(1);
            }
        } 
    }

    void Timer::reset()
    {
        this->stopwatch_start = get_elapsed(); 
    }

    bool Timer::stopwatch(double ms)
    {
        if(get_elapsed() > stopwatch_start + (double)ms)
        {
            reset();
            return true;
        }
        else return false;
    }
};
