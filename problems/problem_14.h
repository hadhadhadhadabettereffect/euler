#ifndef PROBLEM_14
#define PROBLEM_14
#include "problem.h"

/************************
The following iterative sequence is defined for the set of positive integers:

    n → n/2 (n is even)
    n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

    13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms.
Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
************************/
namespace problem_14 {
    // decrementing by 1, 999,999
    unsigned long n = 999999;
    // tmp n to apply Collatz sequence to
    unsigned long _n = n;
    // n that produced longest chain
    unsigned long longest_n = n;
    // length of longest chain
    unsigned long longest_chain = 0;
    // if n has been checked at some point
    bool marked[ 1000000 ] = { false };

    // set n to next largest unchecked number
    void next_unmarked () {
        while ( n > 1 && marked[ n ] ) --n;
        marked[ n ] = true;
        _n = n;
    }

    void collatz ( unsigned long &c ) {
        if ( c & 1 ) c = c * 3 + 1;
        else c >>= 1;
    }

    void next_chain () {

        unsigned long current_chain = 0;

        next_unmarked();

        while ( _n != 1 ) {
            collatz( _n );
            ++current_chain;
            if ( _n < 1000000 ) marked[ _n ] = true;
        }

        if ( current_chain > longest_chain ) {
            longest_chain = current_chain;
            longest_n = n;
        }
    }

    unsigned long solve ()
    {
        while ( n > 1 ) next_chain();
        return longest_n;
    }

    Problem p(14, solve);
}

#endif