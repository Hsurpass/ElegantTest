#!/usr/bin/python3

import time
#当前时间戳
time_stamp = time.time()    
print(type(time_stamp), time_stamp)   #1667037415.485543

#struct_time元组
now_struct_time = time.localtime(time_stamp)
# print(now_struct_time)   

#获取格式化的时间
format_now_struct_time = time.asctime(time.localtime(time.time()))
print(format_now_struct_time)   #Sat Oct 29 17:56:55 2022

# 格式化成2016-03-20 11:45:39形式
print(time.strftime("%Y-%m-%d %H:%M:%S", now_struct_time))  #2022-10-29 17:56:55
# 将格式字符串"%Y-%m-%d %H:%M:%S"转换成时间戳
a = "2022-10-29 17:56:55"
print(time.mktime(time.strptime(a, "%Y-%m-%d %H:%M:%S")))

# 格式化成Sat Mar 28 22:24:24 2016形式
print(time.strftime("%a %b %d %H:%M:%S %Y", now_struct_time))   ##Sat Oct 29 17:56:55 2022

#将格式字符串"%a %b %d %H:%M:%S %Y"转换成时间戳
a = "Sat Oct 29 17:56:55 2022"
print(time.mktime(time.strptime(a, "%a %b %d %H:%M:%S %Y")))    

print(time.timezone)
print(time.tzname)


