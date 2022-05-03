// 7-1_client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/asio.hpp>

int main() {
    try {
        std::string ip = "127.0.0.1";
        auto port = 65000u;

        boost::asio::ip::tcp::endpoint endpoint(
            boost::asio::ip::address::from_string(ip), port);
        boost::asio::io_service io_service;

        boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());
        socket.connect(endpoint);

        std::string message = "Connected!";
        std::cout << message << std::endl;

        do {
            message.push_back('\n');
            boost::asio::write(socket, boost::asio::buffer(message));
        } while (std::getline(std::cin, message));

        boost::asio::write(socket, boost::asio::buffer("EXIT\n"));

    }
    catch (std::system_error& err) {
        std::cerr << err.what();
    }
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
