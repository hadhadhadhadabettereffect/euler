#ifndef PROBLEM_4
#define PROBLEM_4
#include "problem.h"

/************************
A palindromic number reads the same both ways. The largest
palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
************************/

namespace problem_4 {
    // making a couple assumptions
    // 1. palindrome will be 6 digits long
    // 2. initial digit of palindrome will be 9
    // would be more complete to add logic for continued decrementing of assumed values

    // there's probably a more elegant way to do this
    // assumes 6 digit palindrome and first digit is 9
    bool is_palindrome(long n)
    {
        if (n < 900000) return false;
        long n1 = n / 10000;
        long n2 = n / 10;
        if (n1 % 10 != n2 % 10) return false;
        n1 = n / 1000;
        n2 = n / 100;
        return n1 % 10 == n2 % 10;
    }

    long solve ()
    {
        // palindrome = a * b = xyzzyx (assuming six digits)
        // a <==> a1.a2.a3, b <==> b1.b2.b3  if 123 <==> 1.2.3
        // xyzzyx = x * 100001 +
        //          y *  10010 +
        //          z *   1100;
        //        = 11 (9091x + 910y +100z);
        // palindrome % 11 == 0
        // at least one of a,b is evenly divisible by 11

        // starting with the assumption that palindrome is 9...9
        // if no palindromes found, can move to trying 8...8
        // but turns out not to be necessary
        // if x == 9 then a1 == 9 && b1 == 9 ( 899*999 < 900,000 )
        // and (a3 * b3) % 10 == 9
        // so (a3,b3) = (3,3) || (7,7) || (9,1)

        long longest_palindrome = 0;

        long a;
        long b;
        long ab;
        long a1 = 9;
        long b1 = 9;

        // trying 3,3
        long a3 = 3;
        long b3 = 3;

        // making sure one of them is evenly divisible by 11
        // using trick of checking 11 divisibility by seeing
        // if alternating btw subtracting and adding digits
        // from left to right results in a number evenly
        // divisible by 11.
        // a1 - a2 + a3 = n where 11 | n
        // the range of possible values for n is -8 to 18,
        // so n must be 11
        // so if 11 | a,  a1 - a2 + a3 = 11

        long a2 = a1 + a3 - 11;
        long b2 = 9; // will try 0-9 for b2

        a = a1 * 100 + a2 * 10 + a3;
        b = b1 * 100 + b2 * 10 + b3;

       // trying 0-9 for b2
        while (b2--) {
            ab = a * b;
            if (is_palindrome(ab)) {
                if (ab > longest_palindrome) longest_palindrome = ab;
                break;
            }
            b -= 10;
        }

        // trying 7,7
        a3 = 7;
        b3 = 7;

        a2 = a1 + a3 - 11;
        b2 = 9;

        a = a1 * 100 + a2 * 10 + a3;
        b = b1 * 100 + b2 * 10 + b3;

        while (b2--) {
            ab = a * b;
            if (is_palindrome(ab)) {
                if (ab > longest_palindrome) longest_palindrome = ab;
                break;
            }
            b -= 10;
        }

        // trying 9,1
        // 9 + 1 - 11 < 0, so if 11 | a, a3 can't be 1
        // it'd be better to check for this programatically
        a3 = 9;
        b3 = 1;
        a2 = a1 + a3 - 11;
        b2 = 9;
        a = a1 * 100 + a2 * 10 + a3;
        b = b1 * 100 + b2 * 10 + b3;
        while (b2--) {
            ab = a * b;
            if (is_palindrome(ab)) {
                if (ab > longest_palindrome) longest_palindrome = ab;
                break;
            }
            b -= 10;
        }

        // if a palindrome isn't found at this point, should repeate above with
        // decremented assumed values. but since a palindrome will be found here
        // all that would get skipped so just exiting here
        return longest_palindrome;
    }

    Problem p(4, solve);
}

#endif