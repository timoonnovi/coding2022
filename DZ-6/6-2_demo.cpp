// 6-2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <iostream>

class SafeQueue 
{

private:
    std::queue<int> q;
    std::mutex q_locker;

public:
    int pop() {
        q_locker.lock();
        int tmp = 0;

        if (!q.empty()) {
            tmp = q.front();
            q.pop();
        }
        q_locker.unlock();
        return tmp;
    };

    void push(int tmp) {
        q_locker.lock();
        q.push(tmp);
        q_locker.unlock();
    };
};

std::mutex tmp;

template <typename Iterator>
void from_v_to_q(Iterator begin, Iterator end, SafeQueue& q)
{
    for (auto it = begin; it != end; it++)
    {
        tmp.lock();
        q.push(*it);
        tmp.unlock();
    }
}

template <typename Iterator>
void queue_fill(Iterator begin, Iterator end, SafeQueue& q)
{
    auto num_workers = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    auto size = std::distance(begin, end);
    auto size_per_worker = size / num_workers;

    for (auto i = 0u; i < num_workers - 1; i++)
    {
        threads.push_back(std::thread(from_v_to_q<Iterator>,
            std::next(begin, i * size_per_worker),
            std::next(begin, (i + 1) * size_per_worker),
            std::ref(q)));
    }

    from_v_to_q(std::next(begin, (num_workers - 1) * size_per_worker), end, std::ref(q));

    for (auto& thread : threads) {
        thread.join();
    }

    return;
}

void from_q_to_u(std::vector<int>& u, SafeQueue& q, int size)
{
    int tmp = q.pop();
    for (int i = 0; i < size; i++)
    {
        u.push_back(q.pop());
    }
}

int main()
{
    std::vector<int> v;

    for (int i = 0; i < 100; i++)
    {
        v.push_back(i);
    }

    SafeQueue q;

    queue_fill(std::begin(v), std::end(v), q);

    std::vector<int> u;

    from_q_to_u(u, q, v.size());

    for (int i = 0u; i < u.size(); i++)
        std::cout << u[i] << " ";
    std::cout << "\n";

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
