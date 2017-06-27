#ifndef PROBLEM_20
#define PROBLEM_20
#include "problem.h"
#include <vector>


/************************
n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
************************/

namespace problem_20 {

    int solve ()
    {
        std::vector<int> n; // 100! value as an array of ints
        n.reserve(500);
        // starting with 100
        // omitting '00' since zeros won't factor into the final sum
        n.push_back(1);

        // counting down from 100
        auto f = 100;
        while ( --f > 1 )
        {
            // multiplying f by each digit
            for ( unsigned i = 0; i < n.size(); n.at(i++) *= f );

            // carrying over where digits > 9
            for ( unsigned i = 0; i < n.size(); ++i )
            {
                if ( n.at(i) > 9 )
                {
                    if ( i + 1 == n.size() ) n.push_back( n.at(i) / 10 );
                    else n.at(i+1) += (n.at(i) / 10);
                    n.at(i) %= 10;
                }
            }
        }

        auto total = 0;
        for ( auto x : n ) total += x;
        return total;
    }

    Problem p(20, solve);
}

#endif