#ifndef PROBLEM_21
#define PROBLEM_21
#include "problem.h"
#include "shared.h"

/************************
Let d(n) be defined as the sum of proper divisors of n
(numbers less than n which divide evenly into n).

If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair
and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110;
therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
************************/

namespace problem_21 {

    int solve ()
    {
        auto total = 0;
        for ( auto a = 2, b = 0; a < 10000; ++a )
        {
            b = shared::sum_of_factors(a) - a;
            // if a > b then the pair was already recorded
            if ( a < b && shared::sum_of_factors(b) == a + b ) total += a + b;
        }
        return total;
    }

    Problem p(21, solve);
}

#endif