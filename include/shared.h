#ifndef SHARED_H
#define SHARED_H

namespace shared {

    // based on https://oeis.org/wiki/Sum_of_divisors_function
    int sum_of_factors ( int n )
    {
        int total = 1;
        int factor = 1;
        int p = 0; // value of current power of factor
        int sum = 1; // sum of powers of factor

        // doing powers of 2 first
        // loop will increment over odds
        if ( (n&1) == 0 )
        {
            sum = 1;
            p = 2;
            while ( (n&1) == 0 )
            {
                sum += p;
                p <<= 1;
                n >>= 1;
            }
            total *= sum;
        }

        while ( n > 1 )
        {
            factor += 2;
            sum = 1;
            p = factor;
            while ( n % factor == 0 )
            {
                sum += p;
                p *= factor;
                n /= factor;
            }
            total *= sum;
        }
        return total;
    }
}

#endif