#! /usr/bin/python2
# coding=utf-8



dic = {}
dict1 = dict()
print(dic, type(dic))
print(dict1, type(dict1))

dic['one'] = "this is one"
dic[0] = "10"
dic[1] = 10
dic[100] = 100
dic["two"] = ["abc", 200, [11, 12] ]
# print dict
print(type(dic.keys()))     #<type 'list'>
print(type(dic.values()))   #<type 'list'>
print(dic.keys())
print(dic.values())

dic = {"aa" : 123}
print(dic)

print("###########################")
dicc = dict([('Runoob', 1), ('Google', 2), ('Taobao', 3)])
print(dicc)
dicc = dict({('Runoob', 1), ('Google', 2), ('Taobao', 4)})
print(dicc)
dicc = {x:x**2 for x in [2, 4, 6] }
print(dicc)
dicc = dict({x:x**3 for x in (2, 4, 6) })
print(dicc)
dicc = dict(Runoob=1, Google=2, Taobao=3)
print(dicc)
dicc = dict([['a',1],['b',2],['c',3]])
print(dicc)

print("-----------------------")
for c in dicc:
    print(c)
    print(c, dicc[c])

for k, v in dicc.items():
    print(k, ":", v)

del dicc["a"]
print(dicc)


