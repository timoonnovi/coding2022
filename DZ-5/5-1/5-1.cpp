// 5-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <numeric>
#include <vector>
#include <thread>
#include "Timer.h"

template <typename Iterator, typename T>
void accumulate_wrapper(Iterator begin, Iterator end, T init, T& result) 
{
    result = std::accumulate(begin, end, init);
}

template <typename Iterator, typename T>
T parallel_accumulate(Iterator begin, Iterator end, T init, int N) 
{
    // Размер диапазона
    auto size = std::distance(begin, end);

    // Проверяем, нужно ли распараллеливать
    auto max_workers = std::thread::hardware_concurrency();
    auto num_workers = N;
    if (num_workers > max_workers) {
        throw std::out_of_range("Too lot threads.");
    }

    // Проверяем, нужно ли распараллеливать
    if (size < num_workers * 4) {
        return std::accumulate(begin, end, init);
    }

    // Распараллеливать всё-таки нужно, тогда:
    // Считаем количество данных на одного исполнителя
    auto size_per_worker = size / num_workers;

    // Создаём два вектора: с потоками и для записи результатов
    std::vector<std::thread> threads;
    std::vector<T> results(num_workers - 1);

    // Распределяем данные и запускаем потоки.
    for (auto i = 0u; i < num_workers - 1; i++) {
        threads.push_back(std::thread(accumulate_wrapper<Iterator, T>,
            std::next(begin, i * size_per_worker), // сдвиг begin
            std::next(begin, (i + 1) * size_per_worker), // сдвиг begin
            0,
            std::ref(results[i]))); // для записи результата
    }
    auto main_result = std::accumulate(
        std::next(begin, (num_workers - 1) * size_per_worker),
        end, init);

    // Ждём, пока остальные потоки завершат работу
    for (auto& thread : threads) {
        thread.join();
    }

    // Собираем все вычисленные результаты
    return std::accumulate(std::begin(results),
        std::end(results), main_result);
}

int main() {
    std::vector<int> sequence(10000000);
    std::iota(std::begin(sequence), std::end(sequence), 0);

    Timer<microseconds> t;

    // >= 5 threads is too many
    for (auto i = 1; i < 5; i++) {
        std::cout << "Number of threads: " << i << "\n";
        t.reset();
        std::cout << "Accumulated sum: " << 
            parallel_accumulate(std::begin(sequence), std::end(sequence), 0, i);
        std::cout << "\n";
        std::cout << "Time taken: " << t.elapsed();
        t.pause();
        std::cout << "\n\n";
    }

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