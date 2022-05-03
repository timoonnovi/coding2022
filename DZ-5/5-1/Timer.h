#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using namespace std::chrono;

template<typename time_units>
class Timer
{
private:
    steady_clock::time_point start;
    duration<int, std::micro> buff;

public:
    Timer() : start{ steady_clock::now() } {}

    void pause() 
    {
        buff = duration_cast<time_units>(steady_clock::now() - start);
    }

    void resume() 
    {
        start = steady_clock::now() - buff;
    }

    void reset() 
    {
        start = steady_clock::now();
    }

    double elapsed() const
    {
        return duration_cast<time_units>(steady_clock::now() - start).count();
    }
};

#endif // !TIMER_H