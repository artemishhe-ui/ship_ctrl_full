#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

void send_random_traffic(const std::string& destination_ip, int destination_port, int packet_count, float packet_interval, int payload_size) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, 255);
    
    for (int i = 0; i < packet_count; ++i) {
        std::vector<char> payload(payload_size);
        std::generate(payload.begin(), payload.end(), [&]() { return static_cast<char>(distribution(generator)); });
        
        // Send UDP packet (implementation dependent)
        // ...
        
        // Update progress bar
        float progress = static_cast<float>(i + 1) / packet_count;
        update_progress_bar(progress);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(packet_interval * 1000)));
    }
}

void update_progress_bar(float progress) {
    int bar_length = 50;
    int filled_length = static_cast<int>(bar_length * progress);
    std::string bar(filled_length, '=');
    bar += std::string(bar_length - filled_length, '-');
    float percentage = progress * 100;
    
    std::cout << "\r[" << bar << "] " << percentage << "% " << std::flush;
}

int main() {
    std::string destination_ip = "192.168.0.100";  // Replace with the destination IP address
    int destination_port = 12345;  // Replace with the destination port
    int packet_count = 100;  // Number of UDP packets to send
    float packet_interval = 0.1;  // Interval between packets in seconds
    int payload_size = 1024;  // Size of the payload in bytes

    send_random_traffic(destination_ip, destination_port, packet_count, packet_interval, payload_size);

    return 0;
}
