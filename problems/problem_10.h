#ifndef PROBLEM_10
#define PROBLEM_10
#include <cmath>
#include "problem.h"
#include <vector>

/************************
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
************************/

namespace problem_10 {

   unsigned long long solve ()
    {
        // using Sieve of Eratosthenes
        unsigned long long sum = 2; // starting with 2 in sum
        unsigned long number_limit = 2000000;
        unsigned array_size = number_limit / 2; // only checking odds
        unsigned prime_limit = 1 + sqrt(number_limit);
        bool tag_multiples = true;
        bool is_composite[array_size] = { false };

        for (unsigned jump, i=1; i < array_size; ++i) {
            if (!is_composite[i]) {
                jump = 1 + i * 2;
                sum += jump;
                if (tag_multiples) {
                    if (jump > prime_limit) tag_multiples = false;
                    else for (unsigned j = i; (j += jump) < array_size; is_composite[j] = true);
                }

            }
        }
        return sum;
    }

    Problem p(10, solve);
}

#endif