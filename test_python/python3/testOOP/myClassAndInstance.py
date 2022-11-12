#!/usr/bin/python3

#给实例绑定属性的方法是通过实例变量，或者通过self变量
#类本身需要绑定一个属性呢？
#可以直接在class中定义属性，这种属性是类属性，归Student类所有
#当我们定义了一个类属性后，这个属性虽然归类所有，但类的所有实例都可以访问到。

##################################################################
#
#   小结:
#   实例属性属于各个实例所有，互不干扰；
#   类属性属于类所有，所有实例共享一个属性；
#   不要对实例属性和类属性使用相同的名字，否则将产生难以发现的错误
#
####################################################################

class Student:
    name = 'peter'  #类属性
    def __init__(self) -> None:
        self.name = "BOB"   #实例的W属性

s = Student()
print(s.name)       #BOB    同名优先查找实例的属性
print(Student.name) #peter

s.name = 'lili'
print(s.name)       #lili
print(Student.name) #peter

s1 = Student()
print(s1.name)       #BOB
print(Student.name)  #peter

print("-------------------------------")
#删除s实例的name属性
del s.name  
print(s.name)       #peter
print(Student.name) #peter
#s1实例的name属性不受影响
print(s1.name)       #BOB
print(Student.name)  #peter

print("##############################")
del Student.name
# print(s.name)       #AttributeError: type object 'Student' has no attribute 'name'
# print(Student.name) #AttributeError: type object 'Student' has no attribute 'name'
#s1实例的name属性不受影响
print(s1.name)         #BOB
# print(Student.name)  #AttributeError: type object 'Student' has no attribute 'name'