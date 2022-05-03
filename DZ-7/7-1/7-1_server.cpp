// 7-1_server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/asio.hpp>

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

bool read(boost::asio::ip::tcp::socket& socket, std::string& message)
{
    // Буфер -- "коробочка" с байтами
    boost::asio::streambuf buffer;
    // Достаём байты из сокета, пока не встретится \n
    // Выбран этот разделитель, но можно выбирать любой, какой угодно
    boost::asio::read_until(socket, buffer, '\n');
    // Создаём поток на основе буфера
    std::istream stream(&buffer);
    // Достаём из потока строчку с сообщением
    std::getline(stream, message);
    return message != "EXIT";
}

int main()
{
    auto port = 65000u;
    // Специальный ip -- адрес компьютера,
    // на котором запущены процессы.
    std::string ip = "127.0.0.1";

    // Адаптер для порта
    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::address::from_string(ip), port);
    std::cout << "Endpoint ready.\n";

    // Технический класс -- сервис ввода-вывода
    boost::asio::io_service io_service;
    std::cout << "IO_SERVICE ready.\n";

    // Специальный адаптер -- acceptor -- нужен для того,
    // чтобы занять эндпоинт и ждать на нём
    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());
    acceptor.bind(endpoint);
    std::cout << "Acceptor ready.\n";
    // Начинаем ждать
    acceptor.listen();
    std::cout << "Waiting for connections...\n";

    boost::asio::ip::tcp::socket socket(io_service);
    acceptor.accept(socket);
    std::cout << "Connection accepted.\n";

    std::string message;

    while (read(socket, message)) {
        std::cout << message << std::endl;
    }

    socket.close();
    acceptor.close();
    std::cout << "Disconnected.\n";
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
