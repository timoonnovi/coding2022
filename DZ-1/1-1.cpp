// 1-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std::chrono;


template<typename time_units>
class Timer
{
private:
    steady_clock::time_point start;
    duration<int, std::micro> buff;

public:
    Timer() : start{ steady_clock::now() } {}

    ~Timer() 
    {
        std::cout << "Time is: " << duration_cast<time_units>(steady_clock::now() - start).count() << std::endl;
    }

    void pause() {
        buff = duration_cast<time_units>(steady_clock::now() - start);
        std::cout << "Time is: " << buff.count() << std::endl;
    }

    void resume() {
        start = steady_clock::now() - buff;
        std::cout << "Time is: " << duration_cast<time_units>(steady_clock::now() - start).count() << std::endl;
    }
    
    void reset() {
        start = steady_clock::now();
    }

    double elapsed() const
    {
        return duration_cast<time_units>(steady_clock::now() - start).count();
    }
};


using namespace std;


int main()
{
    vector<long long> a{ 5, 3, 6, 3, 6, 7, 4, 2, 1, 45, 132, 341, 51, 1, 5331, 14 };
    Timer<microseconds> t;
    sort(a.begin(), a.end());
    t.pause();
    for (int i = 0; i < 10; i++)
        a[0] * a[0];
    t.resume();
    for (int i = 0; i < 10; i++)
        a[1] * a[1];
    cout << "Time is " << t.elapsed() << '\n';
    t.reset();
    cout << "Time is " << t.elapsed() << '\n';
}
