#!/usr/bin/python3


import socket

listenSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print(listenSocket.fileno())
hostName = socket.gethostname()
print(hostName)
ip = "127.0.0.1"
port = 8888
listenSocket.bind((ip, port))
# listenSocket.bind((hostName, port))
listenSocket.listen(2)

while 1:
    connSocket, addr = listenSocket.accept()
    print(connSocket.fileno(), addr)

    data = connSocket.recv(1024)
    print("server data:", data.decode())
    connSocket.send(data.upper())

connSocket.close()




