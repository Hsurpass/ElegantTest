#!/usr/bin/python3

import datetime, time

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