#!/usr/bin/python3

from pydoc import cli
import socket

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
hostName = clientSocket.getsockname()
serverIP = "127.0.0.1"
port = 8888
    
clientSocket.connect((serverIP, port))
while True:
    mess = "hello"
    clientSocket.send(mess.encode())  #发送一条信息 python3 只接收btye流
    buffer = clientSocket.recv(1024)
    print(buffer.decode())
    break

clientSocket.close()