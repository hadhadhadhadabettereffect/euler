#ifndef PROBLEM
#define PROBLEM
#include "timer.h"

class Problem
{
public:
    Problem (unsigned p, auto (*fn)()) {
        timer::record_time(p, fn);
    }
};

#endif