#pragma once
#include "engine.h"

namespace Octane
{
    class LogFile
    {
    public:
        LogFile();
        ~LogFile();
        void print(std::string s);
        void print(char c[]);
        std::ofstream& operator<<(char c[]); 
        std::ofstream& operator<<(std::string s);
        std::ofstream& operator<<(double d);
        std::ofstream& operator<<(float f);
        std::ofstream& operator<<(int i);
        std::ofstream& operator<<(bool b);
    };
};

static Octane::LogFile debug;
