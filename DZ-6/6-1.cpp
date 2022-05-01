// 6-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <numeric>
#include <vector>
#include <thread>
#include <mutex>

std::mutex tmp;

template <typename Iterator, typename T>
void accumulate_wrapper(Iterator begin, Iterator end, T init, T& result) {
    tmp.lock();
    result += std::accumulate(begin, end, init);
    tmp.unlock();
}

template <typename Iterator, typename T>
void parallel_accumulate(Iterator begin, Iterator end, T init, T& result) 
{
    // Размер диапазона
    auto size = std::distance(begin, end);
    // Количество исполнителей
    auto num_workers = std::thread::hardware_concurrency();
    // Проверяем, нужно ли распараллеливать
    if (size < num_workers * 4) 
    {
        result = std::accumulate(begin, end, init);
        return;
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
            std::next(begin, i * size_per_worker),
            std::next(begin, (i + 1) * size_per_worker),
            0,
            std::ref(result)));
    }
    // Производим расчёт и в основном потоке (с учётом переданного init)
    auto main_result = std::accumulate(std::next(begin, (num_workers - 1) * size_per_worker), end, init);
    result += main_result;
    // Ждём, пока остальные потоки завершат работу
    for (auto& thread : threads) {
        thread.join();
    }

    return;
}

int main() 
{
    int res = 0;

    std::vector<int> sequence(100000);
    std::cout << "\n";
    std::iota(std::begin(sequence), std::end(sequence), 0);
    std::cout << "\n";

    accumulate_wrapper(std::begin(sequence), std::end(sequence), 0, res);

    std::cout << res;
    res = 0;
    std::cout << "\n";

    parallel_accumulate(std::begin(sequence), std::end(sequence), 0, res);

    std::cout << res;
    std::cout << "\n";
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
