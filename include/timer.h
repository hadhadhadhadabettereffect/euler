#ifndef TIMER_H
#define TIMER_H

#include <map>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <string>

namespace timer {
    // output col width options
    static int kIdWidth = 6;
    static int kAnswerWidth = 16;
    static int kTimeWidth = 16;
    static int kRatingWidth = 12;

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

    double exec_time (auto (*fn)())
    {
        auto start = std::chrono::high_resolution_clock::now();
        fn();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    void read_times ()
    {
        std::ifstream f("times.txt");
        int problem;
        int t;
        while (!f.eof()) {
           f >> problem >> t;
           prev[problem] = t;
           best[problem] = t;
        }
        f.close();
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
            std::setw(kIdWidth) << "id" <<
            std::setw(kAnswerWidth) << "answer" <<
            std::setw(kTimeWidth) << "time" << '\n' <<
            std::setw(kIdWidth + kTimeWidth + kRatingWidth + kAnswerWidth) <<
            std::setfill('-') << '\n' << kReset <<
            std::setfill(' ');

        for (std::map<int,int>::iterator it=results.begin(); it!=results.end(); ++it)
        {
            id = it->first;
            t = it->second;
            std::cout << std::setw(kIdWidth) << id <<
                        std::setw(kAnswerWidth) << answers[id] <<
                        std::setw(kTimeWidth) << t <<
                        std::setw(kRatingWidth) <<
                        tags[change(t, prev[id])] <<
                        kReset << '\n';
        }
    }

    void save_times ()
    {
        show_times();
        std::ofstream f("times.txt");
        for (std::map<int,int>::iterator it=best.begin(); it!=best.end(); ++it)
            f << it->first << ' ' << it->second << std::endl;
        f.close();
    }

}
#endif