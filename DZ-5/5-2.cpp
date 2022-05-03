// 5-2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <algorithm>
#include <future>

template <typename Iterator, typename UnaryFunction>
void parallel_for_each(Iterator begin, Iterator end, UnaryFunction f) {
    auto size = std::distance(begin, end);
    auto num_workers = std::thread::hardware_concurrency();

    if (size < num_workers * 4) {
        std::for_each(begin, end, f);
        return;
    }

    auto size_per_worker = size / num_workers;

    for (auto i = 0u; i < num_workers; i++) {
        std::async(std::launch::async, std::for_each<Iterator, UnaryFunction>,
            std::next(begin, i * size_per_worker),
            std::next(begin, (i + 1) * size_per_worker), f);
    }

    return;
}

void function(const int& n)
{
    std::cout << n << "\n";
}

int main() {
    std::vector<int> sequence(100);
    std::iota(std::begin(sequence), std::end(sequence), 0);

    parallel_for_each(std::begin(sequence), std::end(sequence), function);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
