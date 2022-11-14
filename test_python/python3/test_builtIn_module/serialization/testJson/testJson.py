#!/usr/bin/python3

import json

pyObj = { 'a' : 1, 'b' : 2, 'c' : 3, 'd' : 4, 'e' : 5 , 'f': [1,2,3] } 

# json.dump() 序列化写入文件
# json.load() 从文件中反序列化

jsonData = json.dumps(pyObj)
print(jsonData)
print(type(jsonData))

formatJsonData = json.dumps(pyObj, sort_keys=True, indent = 4, separators=(',', ':'))
print(formatJsonData)
print(type(formatJsonData))

print(json.loads(jsonData))
print(json.loads(formatJsonData))


print("-------------------------------")

class Student(object):
    def __init__(self, name, age, score):
        self.name = name
        self.age = age
        self.score = score

s = Student('Bob', 20, 88)
# print(json.dumps(s))

#运行代码，毫不留情地得到一个TypeError：
#TypeError: Object of type Student is not JSON serializable
#错误的原因是Student对象不是一个可序列化为JSON的对象。
#我们仔细看看dumps()方法的参数列表，可以发现，除了第一个必须的obj参数外，dumps()方法还提供了一大堆的可选参数：
#https://docs.python.org/3/library/json.html#json.dumps
#这些可选参数就是让我们来定制JSON序列化。
# 前面的代码之所以无法把Student类实例序列化为JSON，
# 是因为默认情况下，dumps()方法不知道如何将Student实例变为一个JSON的{}对象。
#可选参数default就是把任意一个对象变成一个可序列为JSON的对象，
# 我们只需要为Student专门写一个转换函数，再把函数传进去即可：

def student2dict(stu):
    return {
        'name': stu.name,
        'age': stu.age,
        'score': stu.score
    }

j = json.dumps(s, default=student2dict)
print(j)
# 不过，下次如果遇到一个Teacher类的实例，照样无法序列化为JSON。
# 我们可以偷个懒，把任意class的实例变为dict：
print(json.dumps(s, default=lambda obj:obj.__dict__))

#因为通常class的实例都有一个__dict__属性，它就是一个dict，用来存储实例变量。
# 也有少数例外，比如定义了__slots__的class。

#同样的道理，如果我们要把JSON反序列化为一个Student对象实例，
# loads()方法首先转换出一个dict对象，
# 然后，我们传入的object_hook函数负责把dict转换为Student实例：

def dict2student(d):
    return Student(d['name'], d['age'], d['score'])

print(type(j))
p = json.loads(j, object_hook=dict2student)
print(type(p))
print(p.name)

print('--------------------------------------------')
obj = dict(name='小明', age=20)
s = json.dumps(obj)
# s = json.dumps(obj, ensure_ascii=True)

print(s)
