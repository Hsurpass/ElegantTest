#! /usr/bin/python2
# coding=utf-8

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
    print("server data:", data)
    connSocket.send(data.upper())

connSocket.close()




