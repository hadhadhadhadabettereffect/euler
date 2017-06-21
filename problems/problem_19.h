#ifndef PROBLEM_19
#define PROBLEM_19
#include "problem.h"

/************************
You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.

Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.

A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
************************/

namespace problem_19 {

    enum Day { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
    enum Month { Jan = 1, Feb = 2, Mar = 4, Apr = 8, May = 16, Jun = 32,
                Jul = 64, Aug = 128, Sep = 256, Oct = 512, Nov = 1024, Dec = 2048 };

    static int short_month = Sep | Apr | Jun | Nov;
    static int long_month = Jan | Mar | May | Jul | Aug | Oct | Dec;

    static int short_off = 30 % 7;
    static int long_off = 31 % 7;
    // "but not on a century unless it is divisible by 400" can be ignored
    // since 2000 % 400 == 0
    static int leap_off = 29 % 7;


    int solve ()
    {
        int year = 1; // 1901
        int month = Jan;
        int d = Monday + (365 % 7); // 365 days after 1 Jan 1900's Monday
        int count = 0;

        while ( year <= 100 ) // 2000
        {
            // add to count if day == Sunday
            if ( d == Sunday ) ++count;

            if ( month & short_month ) d += short_off;
            else if ( month & long_month ) d += long_off;
            else if ( (year & 3) == 0 /* leap year */ )  d += leap_off;
            // 28 % 7 == 0, so no change if non-leap feb

            if ( d >= 7 ) d -= 7;

            // increment month, year
            if ( month == Dec )
            {
                month = Jan;
                ++year;
            }
            else month <<= 1;
        }

        return count;
    }

    Problem p(19, solve);
}

#endif