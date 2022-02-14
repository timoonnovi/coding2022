// 2-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <algorithm>
#include "Timer.h"

int main()
{
    {
        // Array part

        std::vector<double> times;
        for (int j = 0; j < 10; j++)
        {
            int a[10000];
            for (int i = 0; i < 10000; i++)
                a[i] = rand() % 1000;

            Timer<microseconds> t;
            std::sort(a, a + 999);
            double tmp = t.elapsed();
            times.push_back(tmp);
        }

        double ans = 0;

        for (int i = 0; i < times.size(); i++)
            ans += times[i];

        ans /= times.size();
        ans = (int)ans;

        std::cout << "Average calculated sorting time for array:         " << ans << " us" << '\n';
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    {
        // Vector part

        std::vector<double> times;
        
        for (int i = 0; i < 10; i++)
        {
            std::vector<int> a;
            for (int j = 0; j < 10000; j++)
                a.push_back(rand() % 1000);

            Timer<microseconds> t;
            sort(a.begin(), a.end());
            double tmp = t.elapsed();
            times.push_back(tmp);
        }

        double ans = 0;

        for (int i = 0; i < times.size(); i++)
            ans += times[i];

        ans /= times.size();
        ans = (int)ans;

        std::cout << "Average calculated sorting time for vector:       " << ans << " us" << '\n';
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    {
        // Deque part

        std::vector<double> times;

        for (int i = 0; i < 10; i++)
        {
            std::deque<int> a;
            for (int j = 0; j < 10000; j++)
                a.push_back(rand() % 1000);

            Timer<microseconds> t;
            sort(a.begin(), a.end());
            double tmp = t.elapsed();
            times.push_back(tmp);
        }

        double ans = 0;

        for (int i = 0; i < times.size(); i++)
            ans += times[i];

        ans /= times.size();
        ans = (int)ans;

        std::cout << "Average calculated sorting time for deque:        " << ans << " us" << '\n';
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    {
        // List part

        std::vector<double> times;

        for (int i = 0; i < 10; i++)
        {
            std::list<int> a;
            for (int j = 0; j < 10000; j++)
                a.push_back(rand() % 1000);

            Timer<microseconds> t;
            a.sort();
            double tmp = t.elapsed();
            times.push_back(tmp);
        }

        double ans = 0;

        for (int i = 0; i < times.size(); i++)
            ans += times[i];

        ans /= times.size();
        ans = (int)ans;

        std::cout << "Average calculated sorting time for list:          " << ans << " us" << '\n';
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    {
        // Forward list part

        std::vector<double> times;

        for (int i = 0; i < 10; i++)
        {
            std::forward_list<int> a;
            for (int j = 0; j < 10000; j++)
                a.push_front(rand() % 1000);

            Timer<microseconds> t;
            a.sort();
            double tmp = t.elapsed();
            times.push_back(tmp);
        }

        double ans = 0;

        for (int i = 0; i < times.size(); i++)
            ans += times[i];

        ans /= times.size();
        ans = (int)ans;

        std::cout << "Average calculated sorting time for forward list:  " << ans << " us" << '\n';
    }

    return 0;
}
