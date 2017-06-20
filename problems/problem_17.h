#ifndef PROBLEM_17
#define PROBLEM_17
#include "problem.h"

/************************
If the numbers 1 to 5 are written out in words:
one, two, three, four, five, then there are
3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive
were written out in words, how many letters would be used?


NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two)
contains 23 letters and 115 (one hundred and fifteen) contains 20 letters.
The use of "and" when writing out numbers is in compliance with British usage.
************************/

namespace problem_17 {

    static const unsigned ones_char_count[10] = {
        0,
        3, // one
        3, // two
        5, // three
        4, // four
        4, // five
        3, // six
        5, // seven
        5, // eight
        4  // nine
    };

    static const unsigned teen_char_count[] = {
        3, // ten
        6, // eleven
        6, // twelve
        8, // thirteen
        8, // fourteen
        7, // fifteen
        7, // sixteen
        9, // seventeen
        8, // eighteen
        8, // nineteen
    };

    static const unsigned tens_char_count[] = {
        0, // <10
        0, // tens -> special cases
        6, // twenty
        6, // thirty
        5, // forty
        5, // fifty
        5, // sixty
        7, // seventy
        6, // eighty
        6  // ninety

    };

    unsigned solve ()
    {
        auto thousands = 11; // "one thousand"

        // per hundred, teens used once each
        auto teens = 0;
        for ( auto i = 0; i < 10; ++i ) teens += teen_char_count[i];
        teens *= 10;

        // per hundred, tens place written out 10 each 10 times
        auto tens = 0;
        for ( auto i = 0; i < 10; ++i ) tens += tens_char_count[i] * 10;
        tens *= 10;

        // per hundred, one-nine in the ones place are written out 9 times (skipping 10-19)
        auto ones = 0;
        for ( auto i = 0; i < 10; ++i ) ones += ones_char_count[i] * 9;
        ones *= 10;

        auto hundreds = 7; // "hundred"
        // "hundred" used in each number between 100-999
        hundreds *= 900;
        // each number one-nine used 100x for that multiple of 100
        for ( auto i = 1; i < 10; ++i ) hundreds += ones_char_count[i] * 100;

        auto ands = 3; // "and"
        // "and" used for every number > 100 if not a multiple of 100
        // 99 times per hundred for 1-9 hundred
        ands *= 9 * 99;
        return thousands + hundreds + teens + tens + ones + ands;
    }

    Problem p(17, solve);
}

#endif