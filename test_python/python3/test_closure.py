#!/usr/bin/python3

def lazy_sum(*args):
    def _sum():
        sum = 0
        for x in args:
            sum += x
        return sum
    return _sum

# def lazy_sum(*args):
#     sum = 0
#     def _sum():
#         nonlocal sum
#         for x in args:
#             sum += x
#         return sum
#     return _sum

f = lazy_sum(1,2,3,4,5)
print(f())