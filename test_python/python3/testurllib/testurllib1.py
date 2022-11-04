#!/usr/bin/python3

from urllib import request, error, parse

# try:
#     myURL = request.urlopen("https://www.runoob.com/")
# except error.HTTPError as e:
#     print(e.code)

# print(myURL.getcode())
# # print(myURL.read())
# # print(myURL.read(300))
# # print(myURL.readline())
# lines = myURL.readlines()
# for line in lines:
#     print(line)


result = parse.urlparse('https://192.168.101:80/nc/v1/routing?dv=2.5.8&s=1&username=user&password=1234')
print(result)

