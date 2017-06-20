#ifndef PROBLEM_18
#define PROBLEM_18
#include "problem.h"

/************************
By starting at the top of the triangle below and moving to
adjacent numbers on the row below, the maximum total from top to bottom is 23.

   (3)
  (7) 4
  2(4) 6
 8 5(9) 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

              75
             95 64
            17 47 82
           18 35 87 10
          20 04 82 47 65
         19 01 23 75 03 34
        88 02 77 73 07 63 67
       99 65 04 28 06 16 70 92
      41 41 26 56 83 40 80 70 33
     41 48 72 33 47 32 37 16 94 29
    53 71 44 65 25 43 91 52 97 51 14
   70 11 33 28 77 73 17 78 39 68 17 57
  91 71 52 38 17 14 91 43 58 50 27 29 48
 63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

NOTE: As there are only 16384 routes, it is possible to solve this problem
by trying every route. However, Problem 67, is the same challenge with a triangle
ontaining one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
************************/

namespace problem_18 {

    // total count of numbers in triangle
    // == sum of numbers up to row count (15)
    // == 15 * 16 / 2
    static const int total_numbers = 120;


    int larger ( int &a, int &b )
    {
        return a > b ? a : b;
    }

    int solve ()
    {

        int pyramid[total_numbers] = {
            75,
            95,64,
            17,47,82,
            18,35,87,10,
            20,4,82,47,65,
            19,1,23,75,3,34,
            88,2,77,73,7,63,67,
            99,65,4,28,6,16,70,92,
            41,41,26,56,83,40,80,70,33,
            41,48,72,33,47,32,37,16,94,29,
            53,71,44,65,25,43,91,52,97,51,14,
            70,11,33,28,77,73,17,78,39,68,17,57,
            91,71,52,38,17,14,91,43,58,50,27,29,48,
            63,66,4,68,89,53,67,30,73,16,69,87,40,31,
            4,62,98,27,23,9,70,98,73,93,38,53,60,4,23
        };

        // manually adding single-path options at the top
        // (1,0),(1,1) + (0,0)
        pyramid[1] += pyramid[0];
        pyramid[2] += pyramid[0];
        // (2,0) + (1,0)
        pyramid[3] += pyramid[1];

        // starting iteration on row 2
        int row = 2;
        int col = 2;
        int largest = 0;

        // starting i on 4 since 0-3 set manually
        for ( int i = 4; i < total_numbers; ++i )
        {
            if ( --col ) pyramid[i] += larger( pyramid[i - row], pyramid[i - row - 1] );
            else {
                col = ++row;
                // adding single path along right side
                pyramid[i] += pyramid[i - row];
                // break on last row
                if ( ++i == total_numbers ) break;
                // adding single path along left side
                pyramid[i] += pyramid[i - row];
            }
        }

        for ( int i = total_numbers - 15; i < total_numbers; ++i )
        {
            if ( pyramid[i] > largest ) largest = pyramid[i];
        }

        return largest;
    }

    Problem p(18, solve);
}

#endif