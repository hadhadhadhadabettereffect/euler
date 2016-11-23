project euler problems <https://projecteuler.net>. feel free to clone if the project setup would be useful. just replace files in problems dir, everything else should be pretty generic.

## make
* `$ make` to build and output all problems to console
* `$ make #[ #]` for an individual problem or problems
    - e.g. `$ make 1 4 7` to run problems 1, 4, and 7
* output format:
    - `problem #    answer     exec time     time compared to previous`

## problem files
* individual problems files can be added under the problems/ dir
* file name format: "problem_<i>x</i>.h"
    - update FILE_PREFIX in the Makefile if naming files differently
* include "problem.h" and create a Problem instance:
    - `Problem <i>name</i>(<i>problem_number</i>, <i>answer_function</i>)`

## timing
* execution time measured in microseconds. Units can be changed in include/timer.h
* times recorded in times.txt