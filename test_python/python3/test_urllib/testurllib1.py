#!/usr/bin/python3

from urllib import request, error, parse

try:
    myURL = request.urlopen("https://www.runoob.com/")
except error.HTTPError as e:
    print(e.code)

print("Status: ", myURL.status, myURL.reason)

for k, v in myURL.getheaders():
    print("%s: %s" %(k,v))


# print(myURL.getcode())
# # print(myURL.read())
# # print(myURL.read(300))
# # print(myURL.readline())
# lines = myURL.readlines()
# for line in lines:
#     print(line)


# result = parse.urlparse('https://192.168.101:80/nc/v1/routing?dv=2.5.8&s=1&username=user&password=1234')
# print(result)

print('-------------------------------------')
#如果我们要想模拟浏览器发送GET请求，就需要使用Request对象，
# 通过往Request对象添加HTTP头，我们就可以把请求伪装成浏览器。
# 例如，模拟iPhone 6去请求豆瓣首页：

req = request.Request('http://www.douban.com/')
req.add_header('User-Agent', 'Mozilla/6.0 (iPhone; CPU iPhone OS 8_0 like Mac OS X) AppleWebKit/536.26 (KHTML, like Gecko) Version/8.0 Mobile/10A5376e Safari/8536.25')
with request.urlopen(req) as f:
    print('Status:', f.status, f.reason)
    for k, v in f.getheaders():
        print('%s: %s' % (k, v))
    # print('Data:', f.read().decode('utf-8'))



