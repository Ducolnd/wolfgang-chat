#include <iostream>
#include "MathFunc/math.hpp"

#define ASIO_STANDALONE

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

using namespace std;

vector<char> vBuffer(20 * 1024); // 10 Kb

void grabData(asio::ip::tcp::socket& socket) {
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](error_code ec, size_t length) {
                if (!ec) {
                    cout << "\nRead " << length << " bytes\n\n";

                    for (int i = 0; i < length; i++) {
                        cout << vBuffer[i];
                    }
                    grabData(socket);
                }
        });
}

int main() {
    asio::error_code ec;

    asio::io_context context;

    asio::io_context::work idleWork(context);
    thread thrContext = thread([&]() { context.run(); });

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49", ec), 80);

    asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);

    if (!ec) {
        cout << "Connected!" << ec.message() << endl;
    } else {
        cout << " failed to connect: " << ec.message() << endl;
    }

    if (socket.is_open()) {

        grabData(socket);

        string sRequest = 
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close \r\n\r\n";

        cout << "Socket is open " << endl;

        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20000ms);

        context.stop();
        if (thrContext.joinable()) thrContext.join();
    }

    return 0;
}