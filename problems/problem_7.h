#ifndef PROBLEM_7
#define PROBLEM_7
#include "problem.h"

#include <math.h>

/************************
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13
 we can see that the 6th prime is 13.

What is the 10001st prime number?
************************/
namespace problem_7 {
    unsigned solve ()
    {
        unsigned n = 0;
        unsigned count = 10001;
        // Prime Number Theorem to estimate 10001th prime
        // https://en.wikipedia.org/wiki/Prime_number_theorem
        // skipping evens (x0.5), but adding padding (x0.6)
        unsigned limit = count * log(count) * 0.6;

        // Sieve of Sundaram
        bool composite[limit] = {false};

        for (unsigned i=1; i < limit; ++i)
        {
            if (!composite[i])
            {
                n = 2 * i + 1;
                if (--count == 1) break;
                for (unsigned j = i + i * n; j < limit; j += n)
                    composite[j] = true;
            }
        }
        return n;
    }

    Problem p(7, solve);
}

#endif