#pragma once
#include "engine.h"
#include <stdint.h>
namespace Octane
{
    class Timer
    {
    private:
        bool sleep_is_granular;
        int64_t frequency;
        double timer_start;
        double stopwatch_start;
    public:
        Timer();
        ~Timer();
        double get_elapsed();
        void rest(double ms);
        void reset();
        bool stopwatch(double ms);
    };
};
