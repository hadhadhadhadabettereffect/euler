#ifndef PROBLEM_23
#define PROBLEM_23
#include "problem.h"
#include "shared.h"
#include <vector>
#include <bitset>

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

    bool is_abundant ( int n )
    {
        return shared::sum_of_divisors(n) > n;
    }

    unsigned solve ()
    {
        std::vector<int> abundant;
        std::bitset<28124> summable;

        abundant.push_back(12);
        for ( auto i = 13; i < 28124; ++i )
        {
            if ( is_abundant(i) ) abundant.push_back(i);
        }

        for ( unsigned i = 0, cap = abundant.size(); i < cap; ++i )
        {
            for ( unsigned j = i; j < cap; ++j )
            {
                if ( abundant.at(i) + abundant.at(j) >= 28124 ) break;
                summable.set( abundant.at(i) + abundant.at(j) );
            }
        }

        unsigned total = 0;
        for ( unsigned i = 1; i < 28124; ++i )
        {
            if ( !summable[i] ) total += i;
        }
        return total;
    }

    Problem p(23, solve);
}

#endif