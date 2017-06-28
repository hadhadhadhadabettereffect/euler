#ifndef SHARED_H
#define SHARED_H
#include <stack>

namespace shared {

    std::stack<int> divs;

    int sum_of_divisors ( int n )
    {
        // 1 always a divisor
        auto sum = 1;
        for ( auto i = 2, j = n/2; i <= j; ++i )
            if ( n % i == 0 ) divs.push(i);

        while ( !divs.empty() )
        {
            sum += divs.top();
            divs.pop();
        }
        return sum;
    }
}

#endif