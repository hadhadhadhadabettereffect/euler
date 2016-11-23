#ifndef PROBLEM_5
#define PROBLEM_5
#include "problem.h"

#include <cmath>

/************************
2520 is the smallest number that can be divided by each
of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible
by all of the numbers from 1 to 20?
************************/
namespace problem_5 {
    long solve ()
    {
        // smallest number divisible by all numbers 1-20 would be
        // the combined product of the largest powers of primes < 20
        // e.g. largest power of 2 under 20 = 2^4 = 16
        // primes > sqrt(20) will have a power of 1
        // if we can assume we begin with knowledge of primes under 20
        // we could just return
        // answer = 2^4 * 3^2 * 5 * 7 * 11 * 13 * 17 * 19;

        // handling 2 separately
        long total = 20;
        long p = 0;
        while (total >>= 1) ++p;
        total = 1 << p;

        // finding remaining primes with Sieve of Eratosthenes
        // bools for odd numbers, starting with 1
        bool is_composite[10] = { true };
        long root = std::sqrt(20);

        for (long i = 1, jump = 0; i < 10; ++i)
        {
            if (!is_composite[i])
            {
                jump = 1 + (i << 1);
                if (jump < root)
                {
                    for (long j = i + jump; j < 10; j += jump)
                        is_composite[j] = true;
                    while (jump * jump < 20) jump *= jump;
                }
                total *= jump;
            }
        }
        return total;
    }

    Problem p(5, solve);
}

#endif