#ifndef TIMER_H
#define TIMER_H

#include <map>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <string>

namespace timer {

    /*
     * Options
     */

    // http://en.cppreference.com/w/cpp/chrono/duration
    using timeUnits = std::chrono::nanoseconds;

    // name of file to save results to
    const constexpr char* fileName = "times.txt";

    // ave timer results from x repetitions
    static int fnReps = 32;

    // output col width options
    static int outIdWidth = 6;
    static int outAnswerWidth = 16;
    static int outTimeWidth = 16;
    static int outRatingWidth = 12;

    // console output time change flags
    // ANSI codes
    // https://en.wikipedia.org/wiki/ANSI_escape_code
    static char tags[7][9] = {
        "\033[37m  ", // same
        "\033[34m:)", // preantepenult
        "\033[33mB)", // antepenult
        "\033[32m:D", // penult
        "\033[33m* ", // ult
        "\033[31m:<"  // slower
    };

    /*
     * Options end
     */


    static char kReset[] = "\033[0m";

    enum TimeDiff {
        same,
        preantepenult,
        antepenult,
        penult,
        ult,
        slower
    };

    bool didReadTimes = false;
    std::map<int,int> prev;
    std::map<int,int> results;
    std::map<int,int> best;
    std::map<int,std::string> answers;

    int time_mag (int t)
    {
        int m = 0;
        while ((t >>= 5) && ++m < 30);
        return m;
    }

    int rel_mag (int a, int b)
    {
        if (a == b) return 0;
        if (a > b) return ((time_mag(a - b) - (time_mag(b) >> 2)) >> 1) ? -1 : 0;
        return time_mag(b - a) - (time_mag(b) >> 1);
    }

    int change (int current, int prev)
    {
        if (current == 0) return ult;
        if (prev == -1) return same;
        int d = rel_mag(current, prev);
        if (d < 0) return slower;
        if (d >= penult) return penult;
        return d;
    }

    double single_exec (auto (*fn)())
    {
        auto start = std::chrono::high_resolution_clock::now();
        fn();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<timeUnits>(end - start).count();
    }

    double exec_time (auto (*fn)())
    {
        double t = 0;
        for ( auto i = 0; i < fnReps; ++i )
        {
            t += single_exec(fn);
        }
        t /= fnReps;
        return t;
    }

    void read_times ()
    {
        std::ifstream f(fileName);
        if (f.good()) {
            int problem;
            int t;
            while (!f.eof()) {
               f >> problem >> t;
               prev[problem] = t;
               best[problem] = t;
            }
            f.close();
        }
        didReadTimes = true;
    }

    void record_time (int problem, auto (*fn)())
    {
        int t, p;
        std::map<int,int>::iterator it;

        if (!didReadTimes) read_times();

        answers[problem] = std::to_string(fn());
        t = (int) exec_time(fn);
        it = prev.find(problem);
        p = it == prev.end() ? -1 : it->second;
        prev[problem] = p;
        results[problem] = t;
        best[problem] = (p == -1 || t < p) ? t : p;
    }

    void show_times ()
    {
        int id, t;

        // output col labels
        std::cout << std::endl <<
            std::right << "\033[1m" /*bold*/ <<
            std::setw(outIdWidth) << "id" <<
            std::setw(outAnswerWidth) << "answer" <<
            std::setw(outTimeWidth) << "time" << '\n' <<
            std::setw(outIdWidth + outTimeWidth + outRatingWidth + outAnswerWidth) <<
            std::setfill('-') << '\n' << kReset <<
            std::setfill(' ');

        for (std::map<int,int>::iterator it=results.begin(); it!=results.end(); ++it)
        {
            id = it->first;
            t = it->second;
            std::cout << std::setw(outIdWidth) << id <<
                        std::setw(outAnswerWidth) << answers[id] <<
                        std::setw(outTimeWidth) << t <<
                        std::setw(outRatingWidth) <<
                        tags[change(t, prev[id])] <<
                        kReset << '\n';
        }
    }

    void save_times ()
    {
        show_times();
        std::ofstream f(fileName);
        for (std::map<int,int>::iterator it=best.begin(); it!=best.end(); ++it)
            f << it->first << ' ' << it->second << std::endl;
        f.close();
    }

}
#endif