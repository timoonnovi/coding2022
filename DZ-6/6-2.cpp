// 6-2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <queue>
#include <mutex>

class SafeQueue 
{

private:
    std::queue<int> q;
    std::mutex q_locker;

public:
    int pop() {
        int tmp = 0;
        q_locker.lock();

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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
