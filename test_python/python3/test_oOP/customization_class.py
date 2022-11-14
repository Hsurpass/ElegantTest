#!/usr/bin/python3

from typing import Any


class Student(object):
    def __init__(self, name):
        self.name = name
    def __str__(self) -> str:
        return 'Student object (name: %s)' % self.name
    __repr__ = __str__

    def __call__(self, *args: Any, **kwds: Any) ->Any:
        print('My name is %s.' % self.name)   

s = Student("bob")
print(s)
# print(s())

print(Student('li'))

#如果一个类想被用于for ... in循环，类似list或tuple那样，
#就必须实现一个__iter__()方法，该方法返回一个迭代对象，
#然后，Python的for循环就会不断调用该迭代对象的__next__()方法拿到循环的下一个值，
# 直到遇到StopIteration错误时退出循环。

class Fib:
    def __init__(self):
        self.a, self.b = 0, 1 # 初始化两个计数器a，b
    
    def __iter__(self):
        print("Fib __iter__")
        return self #实例本身就是迭代对象，故返回自己
    
    def __next__(self):
        print("Fib __next__")
        self.a, self.b = self.b, self.a + self.b    #计算下一个值
        if self.a > 10:
            raise StopIteration()
        return self.a

    def __getitem__(self, n):
        print("Fib __getitem__")
        if isinstance(n, int):
            print("n is int")
            a, b = 1, 1
            for x in range(n):
                a, b = b, a+b
            return a
        if isinstance(n, slice):
            print("n is slice")
            start = n.start
            stop = n.stop
            if start is None:
                start = 0
            a,b = 1,1
            L = []
            for x in range(stop):
                if x >= start:
                    L.append(a)
                a, b = b, a+b
            return L     


for n in Fib():
    print(n)

print("-----------------------------------")
#__getitem__
#Fib实例虽然能作用于for循环，看起来和list有点像，
#但是，把它当成list来使用还是不行，比如，取第5个元素
#要表现得像list那样按照下标取出元素，需要实现__getitem__()方法
f = Fib()
print(f[0])
print(f[1])
print(f[2])
print(f[3])
print(f[4])
print(f[5])
print(f[6])

print("-----------------------------------")
#但是list有个神奇的切片方法：
#>>>list(range(100))[5:10]
#[5, 6, 7, 8, 9]
#对于Fib却报错。原因是__getitem__()传入的参数可能是一个int，也可能是一个切片对象slice，所以要做判断：
print(f[0:5])
print(f[:10])

#但是没有对step参数作处理：
print(f[:10:2])
#也没有对负数作处理，所以，要正确实现一个__getitem__()还是有很多工作要做的。
#此外，如果把对象看成dict，__getitem__()的参数也可能是一个可以作key的object，例如str。
#与之对应的是__setitem__()方法，把对象视作list或dict来对集合赋值。最后，还有一个__delitem__()方法，用于删除某个元素。
#总之，通过上面的方法，我们自己定义的类表现得和Python自带的list、tuple、dict没什么区别，这完全归功于动态语言的“鸭子类型”，不需要强制继承某个接口。

#__getattr__
class Chain(object):

    def __init__(self, path=''):
        self._path = path

    def __getattr__(self, path):
        return Chain('%s/%s' % (self._path, path))

    def __str__(self):
        return self._path

    __repr__ = __str__

print(Chain().s)
print(Chain().status.user.timeline.list)
print(Chain("/").status.user.timeline.list)


#__call__
#一个对象实例可以有自己的属性和方法，当我们调用实例方法时，我们用instance.method()来调用。
#能不能直接在实例本身上调用呢？在Python中，答案是肯定的。
#任何类，只需要定义一个__call__()方法，就可以直接对实例进行调用
s()
print(callable(s))          #True
print(callable(Student("")))#True
print(callable(abs))        #True

print(callable([1,2]))  #False
print(callable('str'))  #False

