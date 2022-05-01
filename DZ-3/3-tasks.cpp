// 3-all.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iterator>

bool prime(unsigned long a)
{
    unsigned long i;
    if (a == 2)
        return 1;
    if (a == 0 || a == 1 || a % 2 == 0)
        return 0;
    for (i = 3; i * i <= a && a % i; i += 2);
    return i * i > a;
}

int main()
{
    srand(time(0));
    std::vector<int> v;
    auto print = [&](std::vector<int>* p, int id) {
        std::cout << "@" << id << ": " << p << ": ";
        for (int i : *p)
            std::cout << i << ' ';
        std::cout << '\n';
    };

    // Task 1
    for (int i = 0; i < 10; i++)
        v.push_back(i + 1);
    print(&v, 1);

    // Task 2
    std::cout << "Input 5 numbers:\n";
    for (int i = 0; i < 5; i++)
    {
        int tmp;
        std::cin >> tmp;
        v.push_back(tmp);
    }
    print(&v, 2);

    // Task 3
    for (int i = 0; i < 30; i++)
    {
        int tmp1, tmp2;
        tmp1 = rand() % v.size();
        tmp2 = rand() % v.size();
        if (tmp1 != tmp2)
        {
            v[tmp1] = v[tmp1] + v[tmp2];
            v[tmp2] = v[tmp1] - v[tmp2];
            v[tmp1] = v[tmp1] - v[tmp2];
        }
    }
    print(&v, 3);

    // Task 4
    std::sort(v.begin(), v.end());
    auto last = std::unique(v.begin(), v.end());
    v.erase(last, v.end());
    print(&v, 4);


    // Task 5
    int odd_count = 0;
    for (int i : v)
        if (i % 2 == 1) odd_count += 1;
    std::cout << "Count of odd numbers is " << odd_count << '\n';

    // Task 6
    std::cout << "Minimal element: " << *std::min_element(v.begin(), v.end()) << '\n';
    std::cout << "Maximal element: " << *std::max_element(v.begin(), v.end()) << '\n';

    // Task 7
    bool flag = 0;
    for (int i : v)
    {
        if (prime(i))
        {
            std::cout << "Prime found: " << i << '\n';
            flag = 1;
            break;
        }
    }
    if (!flag) std::cout << "No primes found.\n";

    // Task 8
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = v[i] * v[i];
    }
    print(&v, 5);

    // Task 9
    std::vector<int> u;
    for (int i = 0; i < v.size(); i++)
    {
        u.push_back(rand() % 100);
    }
    print(&u, 6);

    // Task 10
    int sum = 0;
    for (auto i : u)
        sum += i;
    std::cout << "Summary of 2nd sequence elements: " << sum << '\n';

    // Task 11
    for (int i = 0; i < 5; i++)
        u[i] = 1;
    print(&u, 7);

    std::vector<int> :: iterator it1;
    std::vector<int> :: iterator it2;

    // Task 12
    std::vector<int> w;
    it1 = v.begin();
    it2 = u.begin();
    while (it1 != v.end())
    {
        w.push_back(*it1 - *it2);
        it1++;
        it2++;
    }
    print(&w, 8);

    // Task 13
    std::vector<int> ::iterator it3 = w.begin();
    while (it3 != w.end())
    {
        if (*it3 < 0) *it3 = 0;
        it3++;
    }
    print(&w, 9);

    // Task 14
    it3 = w.begin();
    while (it3 != w.end())
    {
        if (*it3 == 0)
        {
            if (it3 != w.begin())
            {
                std::vector<int> ::iterator tmp = it3;
                tmp--;
                w.erase(it3);
                it3 = tmp;
            }
            else
            {
                w.erase(it3);
                it3 = w.begin();
            }
        }
        it3++;
    }
    print(&w, 10);

    // Task 15
    std::vector<int> ::iterator it4 = w.end() - 1;
    it3 = w.begin();
    while (it4 - it3 > 0)
    {
        iter_swap(it3, it4);
        it3++;
        it4--;
    }
    print(&w, 11);

    // Task 16
    std::vector<int> z = w;
    std::cout << "Maximal element in P3: " << *std::max_element(z.begin(), z.end()) << '\n';
    z.erase(std::max_element(z.begin(), z.end()));
    std::cout << "2nd maximal element in P3: " << *std::max_element(z.begin(), z.end()) << '\n';
    z.erase(std::max_element(z.begin(), z.end()));
    std::cout << "3rd maximal element in P3: " << *std::max_element(z.begin(), z.end()) << '\n';

    // Task 17
    sort(v.begin(), v.end());
    sort(u.begin(), u.end());
    print(&v, 12);
    print(&u, 13);

    // Task 18
    std::vector<int> p;
    std::merge(v.begin(), v.end(), u.begin(), u.end(), std::back_inserter(p));
    print(&p, 14);

    // Task 19
    it4 = p.begin();
    while (*it4 < 1) it4++;
    std::vector<int> ::iterator it5 = it4;
    while (*it5 == 1) it5++;
    std::cout << "Range of 1 insertion is: " << it4 - p.begin() << " . . " << it5 - p.begin() << '\n';

    // Task 20
    print(&v, 15);
    print(&u, 16);
    print(&w, 17);
    print(&p, 18);

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
