#ifndef PROBLEM_1
#define PROBLEM_1
#include "problem.h"

/************************
If we list all the natural numbers below 10 that are multiples
of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
************************/

namespace problem_1 {

    int sum_of_multiples(int n)
    {
        /***
        sum multiples of n up to limit, where k = floor(limit / n)
        n + 2n + 3n + ... + (k * n)
        n * (1 + 2 + 3 + ... + k)
        n * (k * (1 + k) / 2)
        ***/
        int k = 999 / n;
        return n * k * (1 + k) / 2;
    }

    int solve ()
    {
        return sum_of_multiples(3) + sum_of_multiples(5) - sum_of_multiples(15);
    }

    Problem p(1, solve);
}

#endif