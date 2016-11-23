#ifndef PROBLEM_3
#define PROBLEM_3
#include "problem.h"

/************************
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
************************/

namespace problem_3 {
    unsigned solve ()
    {
        /***
        working on assumption that
            if n % x == 0
            and n /= (1...x-1) where n % (1...x-1) == 0
            x is prime
        pretty sure that should be consistently true
        ***/
        unsigned long long n = 600851475143;
        unsigned f = 2; // assumes n > 1

        // if n is even, first factor out 2s
        while ((n & 1) == 0) n >>= 1;

        for (unsigned x = 3, cap = n >> 1; x < cap && n != 1; x += 2)
        {
            while (n % x == 0)
            {
                f = x;
                n /= x;
            }
        }
        return f;
    }

    Problem p(3, solve);
}

#endif