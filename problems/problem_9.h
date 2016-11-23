#ifndef PROBLEM_9
#define PROBLEM_9
#include "problem.h"

/************************
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a^2 + b^2 = c^2
For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
************************/

namespace problem_9 {
    long solve()
    {
        /***
        Euclid's formula for generating Pythagorean triplets
        https://en.wikipedia.org/wiki/Pythagorean_triple#Proof_of_Euclid.27s_formula
            a = n^2 - m^2
            b = 2nm
            c = n^2 + m^2
            where n and m are ints and n > m

        a + b + c = 1000
        n^2 - m^2 + 2mn + n^2 + m^2 = 1000
        2n^2 + 2mn = 1000
        n(m + n) = 500
        m = 500/n - n

        n > m
        n > 500/n - n
        n^2 > 250
        n > 15

        500/n - n > 0
        500/n > n
        n < 23

        n divides evenly into 500 for m to be an int
        n must be product of prime factors of 500 (2,2,5,5,5)
        15 < n < 23
        only possibility is 20
        ***/

        auto n = 20;
        auto m = 500/n - n;
        auto a = n*n - m*m;
        auto b = 2 * m * n;
        auto c = n*n + m*m;

        return a * b * c;
    }

    Problem p(9, solve);
}

#endif