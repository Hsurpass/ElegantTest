#!/usr/bin/python3

from enum import Enum, unique

Month = Enum('Month', ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'))

print(type(Month))
print(Month.Jan)
print(type(Month.Jan))
print(Month.Jan.value)

print(Month.Feb)
print(Month.Mar)
print(Month.Apr)
print(Month.May)
print(Month.Jun)
print(Month.Jul)
print(Month.Aug)

for name, member in Month.__members__.items():
    print(name, '>=', member, ',', member.value)

@unique #检查有没有重复值
class Weekday(Enum):
    Sun = 0 # Sun的value被设定为0
    Mon = 1
    Tue = 2
    Wed = 3
    Thu = 4
    Fri = 5
    Sat = 6

print(type(Weekday))
print(Weekday.Sun)
print(type(Weekday.Sun))
print(Weekday.Sun.value)

print(Weekday['Mon'])
print(Weekday['Mon'].value)

print(Weekday(2))
print(Weekday(2).value)

# print(Weekday[3])         #error
# print(Weekday[3].value)   #error

for name, member in Weekday.__members__.items():
    print(name, '>=', member, ", value=", member.value)

