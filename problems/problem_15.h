#ifndef PROBLEM_15
#define PROBLEM_15
#include "problem.h"

/************************
Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down,
there are exactly 6 routes to the bottom right corner.
    ._._.   ._. .   ._. .
    . . |   . |_.   . | .
    . . |   . . |   . |_.

    . . .   . . .   . . .
    |_._.   |_. .   | . .
    . . |   . |_.   |_._.

How many such routes are there through a 20×20 grid?
************************/

namespace problem_15 {

    static const int prime_count = 8;
    static const unsigned prime_factors[8] = { 2, 3, 5, 7, 11, 13, 17, 19 };

    void mark_factors ( unsigned n, auto&& factor_counts ) {
        auto i = 0;

        while ( n > 1 && i < prime_count ) {
            while ( n % prime_factors[i] == 0 ) {
                n /= prime_factors[i];
                ++factor_counts[i];
            }
            ++i;
        }

    }

    unsigned remove_factors ( unsigned long long n, auto&& factor_counts )
    {
        auto i = 0;

        while ( n > 1 && i < prime_count ) {
            while ( factor_counts[i] && n % prime_factors[i] == 0 ) {
                n /= prime_factors[i];
                --factor_counts[i];
            }
            ++i;
        }
        return n;
    }


    unsigned long long solve ()
    {
        /*
        # of ways to get to a point in a p x p grid == pascals triangle at that point with
        the triangle's apex at (0,0) and center base at (p,p)
        row = p*2, col = p
        e.g. for p = 2, it'd be row 4, col 2 of pascal's triangle
        i.e. 4 choose 2

        n choose r = n! / (r!(n-r)!)
                   = ( n * n-1 ... r+1 ) / (r!)
        */
        unsigned long long n = 40;
        unsigned long long r = 20;
        unsigned long long routes = 1;

        // since 20! and 40!/20! will be huge
        // first getting all the prime factors for 20!
        // skipping 2 and 20 from the bottome and 40 from the top
        unsigned factor_counts[8] = { 0 };

        for ( unsigned i = 3; i < 20; ++i ) {
            mark_factors(i, factor_counts);
        }

        // multiplying 21-39
        // dividing out factors of 20! each time
        while ( ++r < n ) {
            routes *= remove_factors(r, factor_counts);
        }

        return routes;

    }

    Problem p(15, solve);
}

#endif