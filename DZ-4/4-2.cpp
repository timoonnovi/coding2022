// 4-2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <regex>

std::vector<std::string> search(const std::regex& pattern,
    const std::string& text) {
    auto begin = std::sregex_iterator(std::begin(text),
        std::end(text), pattern);
    auto end = std::sregex_iterator();
    std::vector<std::string> results(std::distance(begin, end));
    std::transform(begin, end, std::back_inserter(results), [](auto x) {
        return x.str();
        });
    auto it = std::remove_if(std::begin(results), std::end(results), [](auto item) {
        return item.empty();
        });
    results.erase(it, std::end(results));
    return results;
}

int main()
{
    std::regex pattern(R"([0-3]\d\.[01]\d(\.\d{4})?|([01]?[0-9]|2[0-3]):([0-5]\d)(:[0-5]\d)?)");

    std::string text = "sforgje arig earg +7900000-00-00 dfmpa +734241"
        " +80000000000 2341241241wfm fgerg wfwertrt"
        "+7 000000000 +73000000000 +75000000000"
        "89000000000 +7(910)555-55-00"
        "22.05.2023 Vasya Pupkin 16:55:23";

    auto search_result = search(pattern, text);
    for (const auto& item : search_result) {
        std::cout << item << ' ';
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
