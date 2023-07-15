#include <iostream>

#include "UdpServer.h"
#include "consumer_tread.h"

int main(int argc, char* argv[])
{

    if ( argc < 2) 
    {
        //std::cout << argv[0] << " Version " << SSRV_VERSION_MAJOR << "." << SSRV_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " brrrrrrrrr" << std::endl; // TODO: add ip/soc redef through args cast warn on defalut vals usage
    }
    //std::cout << "Qweek!\n";
    
    boost::asio::io_context io_context;
    AsyncQueue<std::string> queue;
    // Bind the UDP server to port 1234
    //udp::endpoint endpoint(udp::v4(), 1234);
    // Bind the UDP server to port 1234 listen on specific ip 
    udp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234); // TODO: add ip/soc redef through args hiere
    UdpServer<std::string> server(io_context, endpoint, queue);

    std::cout << "Adress is: " << endpoint << std::endl;
    // Run the I/O service in a separate thread
    std::thread io_thread([&io_context]() {
        io_context.run();
        });    

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