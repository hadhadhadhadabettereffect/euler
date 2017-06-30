#ifndef PROBLEM_23
#define PROBLEM_23
#include "problem.h"
#include "shared.h"

/************************
A perfect number is a number for which the sum of its proper divisors
is exactly equal to the number. For example, the sum of the proper divisors
of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n
and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number
that can be written as the sum of two abundant numbers is 24. By mathematical analysis,
it can be shown that all integers greater than 28123 can be written as the sum of
two abundant numbers. However, this upper limit cannot be reduced any further by analysis
even though it is known that the greatest number that cannot be expressed as the sum of
two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
************************/

namespace problem_23 {

    int solve ()
    {
        // reserving space based on natural desity
        // https://projecteuclid.org/euclid.em/1048515661
        // round_up(28123 * 0.248)
        int abundant[7000] = { 12 };
        int count = 1; // # of abundant numbers
        // true @ index n if n can be written as the sum to two abundant numbers
        bool summable[28124] = { false };

        // marking abundant numbers under 28124
        for ( int i = 13; i < 28124; ++i )
            if ( shared::sum_of_factors(i) > (i<<1) )
                abundant[count++] = i;

        // marking sums of abundant number pairs in summable array
        for ( int i = 0, s = 0; i < count; ++i )
        {
            for ( int j = i; j < count; ++j )
            {
                s = abundant[i] + abundant[j];
                if ( s > 28123 ) break;
                summable[s] = true;
            }
        }

        // adding up indexes where summable[index] == false
        int total = 0;
        for( int i = 1; i < 28124; ++i )
            if( !summable[i] ) total += i;

        return total;
    }

    Problem p(23, solve);
}

#endif