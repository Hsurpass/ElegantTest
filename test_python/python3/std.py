#!/usr/bin/python3

import glob,sys,math, random
from time import time
from urllib.request import Request, urlopen
from datetime import date, datetime
import zlib

print(glob.glob('*.py'))

sys.stderr.write("warning\n")

print('tea for too'.replace('too', 'two'))

print(math.cos(math.pi / 4))
print(math.log(1024, 2))

print(random.choice(['apple', 'pear', 'banana']))
print(random.sample(range(100), 10))
print(random.random())
print(random.randrange(6))

# for line in urlopen('http://www.baidu.com'):
#     line = line.decode('utf-8') # Decoding the binary data to text.
#     if 'EST' in line or 'EDT' in line: # look for Eastern Time
#         print(line)

now = date.today()
print(now)
age = now - date(1970, 6,5)
print(age.days) 

s = b'witch which has which witches wrist watch'
print("crs32:", zlib.crc32(s))
print(len(s))   #41
t= zlib.compress(s)
print(len(t))   #37
x = zlib.decompress(t)
print("crs32:", zlib.crc32(x))
print(x)
print(len(x))


from timeit import Timer
print(Timer('t=a; a = b; b = t;', 'a=1; b=2').timeit())
print(Timer('a,b = b,a', 'a=1; b=2').timeit())

import doctest
doctest.testmod()

def average(values):
    return sum(values) / len(values)

print(average((1,2,3)))

import unittest

class TestAverage(unittest.TestCase):
    def test_average(self):
        self.assertEqual(average([2,3,7]), 4) 
        self.assertEqual(round(average([1,5,7])), 4.3) #failed
        self.assertRaises(ZeroDivisionError, average, [])
        self.assertRaises(TypeError, average, 20,30,70)


# t = TestAverage()
# t.test_average()

# unittest.main();       


import urllib
from urllib.request import urlopen
from urllib.parse import urlencode

url='http://www.xxx.com/login'
data={"username":"admin","password":123456}
req_data = urlencode(data)
print(type(req_data), req_data)
# res = urlopen(url + '?' + req_data)
# print(type(res))
# res=res.read().decode()#read()方法是读取返回数据内容，decode是转换返回数据的bytes格式为str
# print(res)
print('---------------')

encodeData = req_data.encode("ascii")
print(type(encodeData), encodeData)
post_data = Request(url, encodeData)
print(type(post_data), post_data)

import datetime
today = datetime.date.today()
print(type(today), today)    #2022-10-26

yesterday = today - datetime.timedelta(days=1)
print(yesterday)    #2022-10-25

last_month = today.month - 1 if today.month - 1 else 12
print(last_month)   #9

import time
#当前时间戳
time_stamp = time.time()    
print(type(time_stamp), time_stamp)   #1666772635.8568633
#时间戳转datetime
datetime_ = datetime.datetime.fromtimestamp(time_stamp)
print(type(datetime_), datetime_)    #2022-10-26 16:23:55.856863

#datetime转时间戳
print(today.timetuple())
print(int(time.mktime(today.timetuple())))  

#datetime转字符串
today_str = today.strftime("%Y-%m-%d")
print(today_str)

#字符串转datetime
today_datetime = datetime.datetime.strptime(today_str, "%Y-%m-%d")
print(today_datetime)

#补时差
print(datetime.timezone())
print(today + datetime.timedelta(hours=8))


