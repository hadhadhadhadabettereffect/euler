#ifndef PROBLEM_16
#define PROBLEM_16
#include "problem.h"

/************************
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
************************/

namespace problem_16 {

    // possible to shift all without iter?
    void mult_2 ( int (&digits)[500], int &len ) {
        for ( int i = 0; i < len; ++i ) {
            digits[i] *= 2;
        }
        for ( int i = 0; i < len; ++i ) {
            if ( digits[i] >= 10 )
            {
                digits[i+1] += 1;
                digits[i] %= 10;
            }
        }
        if ( digits[len] ) ++len;
    }


    int solve ()
    {
        // 500 digits seems like a safe over-estimate
        int digits[500] = {};
        // char length of base-ten number
        int len = 1;
        int sum = 0;
        digits[0] = 2;
        for ( int i = 1; i < 1000; ++i ) {
            mult_2( digits, len );
        }
        for ( int i = 0; i < len; ++i ) {
            sum += digits[i];
        }
        return sum;
    }

    Problem p(16, solve);
}

#endif