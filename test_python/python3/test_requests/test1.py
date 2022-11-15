#!/usr/bin/python3

import requests

response = requests.get('http://www.runoob.com/')

#	返回响应的内容，unicode 类型数据
# print(response.text)
# 返回 http 的状态码
print(response.status_code)
# 响应状态的描述
print(response.reason)
#编码方式
print(response.apparent_encoding)
# print(response.json())

resJson = requests.get('https://www.runoob.com/try/ajax/json_demo.json')
print(resJson.json())

res = requests.request('get', "https://www.runoob.com")
print(res.status_code)
