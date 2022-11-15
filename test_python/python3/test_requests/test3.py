#!/usr/bin/python3

# 导入 requests 包
import requests

# 发送请求
res1 = requests.post('https://www.runoob.com/try/ajax/demo_post.php')

# 返回网页内容
print(res1.text)

# 表单参数，参数名为 fname 和 lname
myobj = {'fname': 'RUNOOB','lname': 'Boy'}

res2 = requests.post('https://www.runoob.com/try/ajax/demo_post2.php', data=myobj)
print(res2.text)
