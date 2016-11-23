#ifndef PROBLEM_6
#define PROBLEM_6
#include "problem.h"

/************************
The sum of the squares of the first ten natural numbers is,
1^2 + 2^2 + ... + 10^2 = 385
The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)^2 = 55^2 = 3025
Hence the difference between the sum of the squares of the
first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the
first one hundred natural numbers and the square of the sum.
************************/
namespace problem_6 {
    long solve ()
    {
        // sum of 1-100
        long sum = 100 * 101 / 2;
        long square_of_sum = sum * sum;

        // formula for the sum of squares from 1 to n
        // https://en.wikipedia.org/wiki/Square_pyramidal_number
        // n * (n + 1) * (2n + 1) / 6

        long sum_of_squares = 100 * 101 * 201 / 6;

        return square_of_sum - sum_of_squares;
    }

    Problem p(6, solve);
}

#endif