#include <iostream>

#include "UdpServer.h"
#include "consumer_tread.h"

{
    //std::cout << "Qweek!\n";
    
    boost::asio::io_context io_context;
    AsyncQueue<std::string> queue;
    // Bind the UDP server to port 1234
    //udp::endpoint endpoint(udp::v4(), 1234);
    // Bind the UDP server to port 1234 listen on specific ip 
    udp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234);
    UdpServer<std::string> server(io_context, endpoint, queue);

    std::cout << "Adress is: " << endpoint << std::endl;
    // Run the I/O service in a separate thread
    std::thread io_thread([&io_context]() {
        io_context.run();
        });

    // Wait for the thread to finish
    

    // Start running the I/O service
    //io_context.run();
    char q = 'q', b = 'b';
    std::thread consumer(consumer_thread<std::string>, std::ref(queue), std::ref(q));
    std::thread consumer2(consumer_thread<std::string>, std::ref(queue), std::ref(b));

    // Wait for the thread to finish (not actually necessary in this case)
    consumer.join();
    consumer2.join();
    io_thread.join();

    return 0;
}