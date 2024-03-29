#!/usr/bin/python3

#把一个getter方法变成属性，只需要加上@property就可以了，
#此时，@property本身又创建了另一个装饰器@score.setter，
#负责把一个setter方法变成属性赋值，于是，我们就拥有一个可控的属性操作：
class Student(object):

    @property
    def score(self):
        return self._score

    @score.setter
    def score(self, value):
        if not isinstance(value, int):
            raise ValueError('score must be an integer!')
        if value < 0 or value > 100:
            raise ValueError('score must between 0 ~ 100!')
        self._score = value

    @property
    def birth(self):
        return self._birth

    @birth.setter
    def birth(self, value):
        self._birth = value

    #还可以定义只读属性，只定义getter方法，不定义setter方法就是一个只读属性
    @property
    def age(self):
        return 2015 - self._birth


s = Student()
s.score = 60
print(s.score)

s.birth = 1990
print(s.age)




