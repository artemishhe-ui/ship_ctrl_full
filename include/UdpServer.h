#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include "AsyncQueue.h"
//#include "async_queue.hpp" // Assuming the async queue class is defined in async_queue.hpp

using boost::asio::ip::udp;

template<typename T>
class UdpServer {
public:
    UdpServer(boost::asio::io_context& io_context, const udp::endpoint& endpoint, AsyncQueue<T>& queue)
        : socket_(io_context, endpoint), queue_(queue) {
        start_receive();
    }

private:
    void start_receive() {
        socket_.async_receive_from(boost::asio::buffer(data_, max_length_), sender_endpoint_,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error && bytes_transferred > 0) {
                    T value(data_, data_ + bytes_transferred);
                    queue_.push(std::move(value));
                    //std::cout << "udp got: " << std::move(value) << std::endl;//not working
                }
                start_receive();
            });
    }

    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    AsyncQueue<T>& queue_;
    enum { max_length_ = 1024 };
    char data_[max_length_];
};

