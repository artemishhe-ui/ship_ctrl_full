import socket
from controls import *
import threading
import time

'''
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
sock.bind(('192.168.88.53', 9090))  
sock.listen(1)  
print('Server is running, please, press ctrl+c to stop')
while True:
    conn, addr = sock.accept()  
    print('connected:', addr)  
    data = conn.recv(1024)  
    print(str(data))
    conn.send(data.upper())  
conn.close()
'''


def send_data():
    while data["work"] == 1:
        print("The following is going to be sent:", data)
        sock.send(bytes(str(data), encoding = "UTF-8"))
        time.sleep(3)


print("starting program...")

data = {"work"       : 1,
        "direction"  : 0,
        "turn"       : 0,
        "gamepad_mod": 0
        }


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
try:
    sock.connect(('192.168.88.80', 9090))
    th = threading.Thread(target = send_data)
    th.start()
    
    print("starting cycle")
    while data["work"]:
        events = get_gamepad()
        data = analise_gamepad(events[0], data)
        print(data)
    print("ending cycle") 

except Exception as ex:
    print("Error.")
    print(ex)

finally:
    data = {"work"       : 0,
            "direction"  : 0,
            "turn"       : 0,
            "gamepad_mod": 0
            }
    th.join()
    sock.close()
