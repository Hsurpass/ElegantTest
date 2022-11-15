#!/usr/bin/python3

#https://www.liaoxuefeng.com/wiki/1016959663602400/1017648783851616

import datetime, time
from threading import local

#获取当前日期和时间
now = datetime.datetime.now()
print(now)  #2022-11-15 12:07:51.775983

#获取指定日期和时间
dt = datetime.datetime(2015, 4, 19, 19, 12, 10)
print(dt)   #2015-04-19 19:12:10

#datetime转换为timestamp
ts = dt.timestamp()
print(ts)   #1429441930.0

#timestamp转换为datetime
localDatetime = datetime.datetime.fromtimestamp(1429441930.0)
print(localDatetime)    #2015-04-19 19:12:10
#注意到timestamp是一个浮点数，它没有时区的概念，而datetime是有时区的。
# 上述转换是在timestamp和本地时间做转换。

#本地时间是指当前操作系统设定的时区。例如北京时区是东8区，则本地时间：
# 2015-04-19 12:20:00
# 实际上就是UTC+8:00时区的时间：
# 2015-04-19 12:20:00 UTC+8:00
# 而此刻的格林威治标准时间与北京时间差了8小时，也就是UTC+0:00时区的时间应该是：
# 2015-04-19 04:20:00 UTC+0:00

# timestamp也可以直接被转换到UTC标准时区的时间：
utcDatetime = datetime.datetime.utcfromtimestamp(1429441930.0)
print(utcDatetime)

#str转换为datetime
#很多时候，用户输入的日期和时间是字符串，要处理日期和时间，首先必须把str转换为datetime。
# 转换方法是通过datetime.strptime()实现，需要一个日期和时间的格式化字符串：

strToDatetime = datetime.datetime.strptime("2015-04-19 19:12:10", '%Y-%m-%d %H:%M:%S' )
print(strToDatetime)

#datetime转换为str
strnow = now.strftime('%a, %b %d %H:%M')
print(strnow)

#datetime加减
#对日期和时间进行加减实际上就是把datetime往后或往前计算，得到新的datetime。
# 加减可以直接用+和-运算符，不过需要导入timedelta这个类：
print(now + datetime.timedelta(hours = 10))
print(now - datetime.timedelta(days=1))
print(now + datetime.timedelta(days = 1, hours = 10))

print('----------------------------------------------')
#时区转换
#我们可以先通过utcnow()拿到当前的UTC时间，再转换为任意时区的时间：
# 拿到UTC时间，并强制设置时区为UTC+0:00:
utc_now = datetime.datetime.utcnow()
print(utc_now)
utc_now = datetime.datetime.utcnow().replace(tzinfo=datetime.timezone.utc)
print(utc_now)

# astimezone()将转换时区为北京时间:
bj_dt = utc_now.astimezone(datetime.timezone(datetime.timedelta(hours=8)))
print(bj_dt)
bj_dt = bj_dt.astimezone(datetime.timezone(datetime.timedelta(hours=8)))
print(bj_dt)

# astimezone()将转换时区为东京时间:
tokyo_dt = utc_now.astimezone(datetime.timezone(datetime.timedelta(hours=9)))
print(tokyo_dt)
# astimezone()将bj_dt转换时区为东京时间:
tokyo_dt1 = bj_dt.astimezone(datetime.timezone(datetime.timedelta(hours=9)))
print(tokyo_dt1)

# astimezone()将bj_dt转换时区为UTC时间:
utc_dt = bj_dt.astimezone(datetime.timezone(datetime.timedelta(hours=0)))
print(utc_dt)

# astimezone()将tokyo_dt转换时区为UTC时间:
utc_dt = tokyo_dt.astimezone(datetime.timezone(datetime.timedelta(hours=0)))
print(utc_dt)




print('----------------------------------------------')
today = datetime.date.today()
print(type(today), today)    #2022-10-26

yesterday = today - datetime.timedelta(days=1)
print(yesterday)    #2022-10-25

last_month = today.month - 1 if today.month - 1 else 12
print(last_month)   #9

#当前时间戳
time_stamp = time.time()    
print(type(time_stamp), time_stamp)   #1667037415.485543

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
# print(datetime.timezone())
print(today + datetime.timedelta(hours=8))