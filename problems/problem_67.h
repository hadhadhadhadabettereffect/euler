#ifndef PROBLEM_67
#define PROBLEM_67
#include "problem.h"
#include <fstream>

/************************
By starting at the top of the triangle below and moving to
adjacent numbers on the row below, the maximum total from top to bottom is 23.

   (3)
  (7) 4
  2(4) 6
 8 5(9) 3

That is, 3 + 7 + 4 + 9 = 23.
Find the maximum total from top to bottom in triangle.txt
(https://projecteuler.net/project/resources/p067_triangle.txt),
a 15K text file containing a triangle with one-hundred rows.

NOTE: This is a much more difficult version of Problem 18. It is not possible to try every route
to solve this problem, as there are 2^99 altogether! If you could check one trillion (10^12) routes
every second it would take over twenty billion years to check them all.
There is an efficient algorithm to solve it. ;o)
************************/

namespace problem_67 {
    const constexpr char* FILENAME = "include/p067_triangle.txt";

    int larger ( int &a, int &b )
    {
        return a > b ? a : b;
    }

    int solve ()
    {
        std::ifstream file(FILENAME);

        int row_a[100] = {0};
        int row_b[100] = {0};

        int largest = 0;

        // starting while loop on row 2 after first col
        int row = 2;
        int col = 1;

        // doing first two rows manually
        file >> row_b[0];
        file >> row_a[0];
        file >> row_a[1];
        row_a[0] += row_b[0];
        row_a[1] += row_b[0];
        file >> row_b[0];
        row_b[0] += row_a[0];

        while ( !file.eof() )
        {
            file >> row_b[col];
            row_b[col] += larger( row_a[col-1], row_a[col] );

            if ( ++col >= row )
            {
                file >> row_b[col];
                row_b[col] += row_a[col-1];
                col = 1;
                std::swap( row_a, row_b );
                if ( ++row == 100 ) break;
                file >> row_b[0];
                row_b[0] += row_a[0];
            }
        }

        for ( int i = 0; i < 100; ++i )
        {
            if ( row_a[i] > largest ) largest = row_a[i];
        }

        return largest;
    }

    Problem p(67, solve);
}

#endif