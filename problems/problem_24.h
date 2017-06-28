#ifndef PROBLEM_24
#define PROBLEM_24
#include "problem.h"

/************************
A permutation is an ordered arrangement of objects. For example,
3124 is one possible permutation of the digits 1, 2, 3 and 4.
If all of the permutations are listed numerically or alphabetically,
we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits
0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
************************/

namespace problem_24 {

    int pop_nth ( int (&arr)[10], int n )
    {
        int d = 0;
        for ( auto i=0; i<10; ++i )
        {
            if ( arr[i] == -1 ) continue;
            if ( n == 0 )
            {
                d = arr[i];
                arr[i] = -1;
                break;
            }
            --n;
        }
        return d;
    }

    long long solve ()
    {
        int digits[10] = { 0,1,2,3,4,5,6,7,8,9 };
        long remaining = 999999; // millionth permutation

        // pX == possible permutations with digits at index >= X fixed
        auto p7 = 2;
        auto p6 = p7 * 3;
        auto p5 = p6 * 4;
        auto p4 = p5 * 5;
        auto p3 = p4 * 6;
        auto p2 = p3 * 7;
        auto p1 = p2 * 8;
        auto p0 = p1 * 9;

        // # of complete permutations with the first digit fixed
        int n = remaining / p0;
        // get nth digit from remaining digits, remove from set
        int d = pop_nth( digits, n );
        // setting d in the 1st position of final result
        long long answer = 1000000000 * d;
        // remove permutations from remaining
        remaining -= d * p0;
        n = remaining / p1;
        d = pop_nth( digits, n );
        answer += 100000000 * d;
        remaining -= n * p1;

        n = remaining / p2;
        d = pop_nth( digits, n );
        answer += 10000000 * d;
        remaining -= n * p2;

        n = remaining / p3;
        d = pop_nth( digits, n );
        answer += 1000000 * d;
        remaining -= n * p3;

        n = remaining / p4;
        d = pop_nth( digits, n );
        answer += 100000 * d;
        remaining -= n * p4;

        n = remaining / p5;
        d = pop_nth( digits, n );
        answer += 10000 * d;
        remaining -= n * p5;

        n = remaining / p6;
        d = pop_nth( digits, n );
        answer += 1000 * d;
        remaining -= n * p6;

        n = remaining / p7;
        d = pop_nth( digits, n );
        answer += 100 * d;
        remaining -= n * p7;

        answer += 10 * pop_nth( digits, remaining ) + pop_nth( digits, 0 );

        return answer;
    }

    Problem p(24, solve);
}

#endif