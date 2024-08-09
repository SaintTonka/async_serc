#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>
#include <vector>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

void client_session(const std::string& ip, const std::string& port, int id, int num_cycles, boost::asio::io_context& io_context) {
    try {
        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(socket, resolver.resolve(ip, port));

        for (int i = 0; i < num_cycles; ++i) {
            std::string request;
            do {
                std::cout << id << " Thread; " << i + 1 << " Cycle(write/read) - Enter message: ";
                std::getline(std::cin, request);
                if (request.empty()) {
                    std::cerr << "Empty message, please enter a valid message." << std::endl;
                }
            } while (request.empty());

            size_t request_length = request.size();
            boost::asio::write(socket, boost::asio::buffer(request.data(), request_length));

            std::vector<char> reply(request_length);
            size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply.data(), request_length));
            std::cout << id << " Thread; " << i + 1 << " Cycle(write/read) - Reply is: ";
            std::cout.write(reply.data(), reply_length);
            std::cout << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in thread " << id << ": " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: blocking_tcp_echo_client <number of threads(clients)> <number of cycles(write/read)>" << std::endl;
        return 1;
    }

    int num_threads = std::stoi(argv[1]);
    int num_cycles = std::stoi(argv[2]);

    std::string port;
    std::string ip = "127.0.0.1";
    std::cout << "Your IP address: 127.0.0.1"<<std::endl;
    
    std::cout << "Enter port: (1337 for exmp)";
    std::cin >> port;
    std::cin.ignore(); 

    boost::asio::io_context io_context;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(client_session, ip, port, i + 1, num_cycles, std::ref(io_context));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
