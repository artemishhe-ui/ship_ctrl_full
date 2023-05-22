import socket
import random
import time

def generate_random_payload(size):
    return bytearray(random.getrandbits(8) for _ in range(size))

def send_random_traffic(destination_ip, destination_port, packet_count, packet_interval, payload_size):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    for _ in range(packet_count):
        payload = generate_random_payload(payload_size)
        sock.sendto(payload, (destination_ip, destination_port))
        time.sleep(packet_interval)
    
    sock.close()

# Usage example
destination_ip = '192.168.16.10'  # Replace with the destination IP address
destination_port = 1234  # Replace with the destination port
packet_count = 100  # Number of UDP packets to send
packet_interval = 0.9  # Interval between packets in seconds
payload_size = 1024  # Size of the payload in bytes

send_random_traffic(destination_ip, destination_port, packet_count, packet_interval, payload_size)
