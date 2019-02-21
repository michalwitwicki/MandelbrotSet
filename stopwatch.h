#pragma once
#include <ctime>
#include <iostream>

class Stopwatch
{
private:
    clock_t before;
    clock_t after;
    bool start;
public:
    Stopwatch();
    void tick();
    clock_t time(); 
};
