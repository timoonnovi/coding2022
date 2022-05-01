// 4-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "human.h"
#include "json.hpp"
#include <filesystem>
#include <fstream>

using nlohmann::json;

int main()
{
    Human h1, h2, h3;
    std::cin >> h1;
    std::cin >> h2;
    std::cin >> h3;

    std::map<std::string, std::string> m1, m2, m3;

    // Rendering structs to maps
    struct_to_map(h1, m1);
    struct_to_map(h2, m2);
    struct_to_map(h3, m3);

    // Building JSONs from maps
    json j1(m1);
    json j2(m2);
    json j3(m3);

    auto j1d = j1.dump();
    auto j2d = j2.dump();
    auto j3d = j3.dump();

    namespace fs = std::filesystem;

    fs::create_directory("JSON");

    auto filepath = "JSON";

    std::fstream fout1("JSON/human1.json", std::ios::out);
    fout1 << j1d;
    fout1.close();
    std::fstream fout2("JSON/human2.json", std::ios::out);
    fout2 << j2d;
    fout2.close();
    std::fstream fout3("JSON/human3.json", std::ios::out);
    fout3 << j3d;
    fout3.close();

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
