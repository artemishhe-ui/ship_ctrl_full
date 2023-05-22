import socket
import random
import time

def generate_random_payload(size):
    return bytearray(random.getrandbits(8) for _ in range(size))

def send_random_traffic(destination_ip, destination_port, packet_count, packet_interval, payload_size):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    for i in range(packet_count):
        payload = generate_random_payload(payload_size)
        sock.sendto(payload, (destination_ip, destination_port))
        
        # Update progress bar
        progress = (i + 1) / packet_count
        update_progress_bar(progress)
        
        time.sleep(packet_interval)
    
    sock.close()

def update_progress_bar(progress):
    bar_length = 50
    filled_length = int(round(bar_length * progress))
    bar = '=' * filled_length + '-' * (bar_length - filled_length)
    percentage = round(progress * 100, 2)
    print(f'\r[{bar}] {percentage}% ', end='', flush=True)

# Usage example
destination_ip = '192.168.0.100'  # Replace with the destination IP address
destination_port = 12345  # Replace with the destination port
packet_count = 100  # Number of UDP packets to send
packet_interval = 0.1  # Interval between packets in seconds
payload_size = 1024  # Size of the payload in bytes

send_random_traffic(destination_ip, destination_port, packet_count, packet_interval, payload_size)
