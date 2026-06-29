#ifndef PLPTIME_H
#define PLPTIME_H

#include <iostream>
#include <chrono>
#include <time.h>

class runtime {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    void stop() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duartion = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "\n" << duartion << "ms\n";
    }
};

static runtime run;

#endif