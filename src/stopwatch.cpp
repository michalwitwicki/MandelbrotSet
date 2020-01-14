#include "stopwatch.h"

Stopwatch::Stopwatch()
{
    start = 0;
}

void Stopwatch::tick()
{
    if(start == 0)
    {
        before = clock();
        start = 1;
    }
    else if(start == 1)
    {
        after = clock();
        start = 0;
    }
}

clock_t Stopwatch::time()
{
    return (after-before)/(CLOCKS_PER_SEC/1000);
}
