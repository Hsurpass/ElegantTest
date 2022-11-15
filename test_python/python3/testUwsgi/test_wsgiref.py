#!/usr/bin/python3

from wsgiref import simple_server
from hello import application

#Q# 创建一个服务器，IP地址为空，端口是8000，处理函数是application:
ser = simple_server.make_server('172.18.160.172', 8000, application)

print('Serving HTTP on port 8000...')
# 开始监听HTTP请求:
ser.serve_forever()



