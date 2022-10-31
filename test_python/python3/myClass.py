#!/usr/bin/python3

#self 不是 python 关键字，我们把他换成 this 也是可以正常执行的:
# class MyClass:
#     def __init__(this, *args):
#         print(this)
#         print(this.__class__)
#         print("MyClass constructor, id(self):", id(this))
#         this.data = args
#     i = 10
#     def f(self):
#         print('hello world')

class MyClass:
    "my class"  # __doc__
    i = 10
    def __init__(self, ii, *args):
        print("MyClass ii:", ii)
        print("self:", self)
        print("self.__class__:", self.__class__)
        print("self.__class__.__name__:", self.__class__.__name__)
        print("MyClass constructor, id(self):", id(self))
        self.i = ii
        self.data = args
    
    def __del__(self):
        print("__del__", self.__class__.__name__, "destructor")

    __name = "xiaoming" #私有成员类外无法直接访问
    _grade = 1234234
    def getName(self):
        print("from myClass.getName")
        return self.__name
    def f(self):
        print('hello world')


x = MyClass(1, 'a', [1,2,3], 20.22)
print("id(x)", id(x))
print("x.i:", x.i)
x.f()
print(type(x.data), x.data)
print(x.getName())

print("MyClass.__doc__:", MyClass.__doc__)
print("MyClass.__name__:", MyClass.__name__)
print("MyClass.__module__:", MyClass.__module__)
print("MyClass.__bases__:", MyClass.__bases__)
print("MyClass.__dict__:", MyClass.__dict__)
x1 = x
x2 = x1
del x
del x1
del x2

print("----------------------------------")
class myDerivedClass(MyClass):
    def __init__(self, i_, *args):
        print("_i:{0}, id(self):{1}".format(i_, id(self)))
        MyClass.__init__(self, i_, *args)
        # super(myDerivedClass, self).__init__(self, i_, *args)
    
    age = 15
    def getName(self):
        print("from myDerivedClass.getName")
        # print(self.__name)
        print(self._grade)
        return super().getName()

    #私有方法
    def __privateFunc(self):
        print("myDerivedClass private func()")

    #protect方法
    def _protectFunc(self):
        print("myDerivedClass protect func()")

    #protect方法
    def publicFunc(self):
        print("myDerivedClass public func()")
        self._protectFunc()
        self.__privateFunc()

    @staticmethod
    def getAge():
        return myDerivedClass.age
    #类方法：类和对象访问，不能和其他方法重名，
    #不然会相互覆盖，后面定义的会覆盖前面的
    # @classmethod
    # def getName(self):
        # print("myDerivedClass classmethod")

print(issubclass(myDerivedClass, MyClass))

d = myDerivedClass(111, 'a', [3,4,5])
print(isinstance(d, MyClass))
print(d.age)    #15
print(d.i)      #111
print(id(d.i))  #9788384
print(d.data)   #('a', [3, 4, 5])
# print(d.__name)   #私有成员不可访问
print(super(myDerivedClass, d).i)  #10
print(id(super(myDerivedClass, d).i))   #9785152

#重写方法
print(d.getName())              # 子类调用重写方法
print(super(myDerivedClass, d).getName())  #用子类对象调用父类已被覆盖的方法

#静态方法
print(myDerivedClass.getAge())
print(d.getAge())

#类方法：类和对象访问，不能和其他方法重名，
#不然会相互覆盖，后面定义的会覆盖前面的
# d.getName()
# myDerivedClass.getName()

print(d.__str__())
# print(dir(myDerivedClass))
#Python不允许实例化的类访问私有数据，
#但你可以使用 object._className__attrName（ 对象名._类名__私有属性名 ）访问属性
print(d._MyClass__name)

# d.__privateFunc()
# d._protectFunc()
d.publicFunc()
