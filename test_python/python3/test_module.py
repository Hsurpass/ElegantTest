#!/usr/bin/python3

def func():
    print("hello, python3")

def func1():
    print("test_module func1")

if __name__ == '__main__':
# if '__main__':
    print('test_module main func1')
else:
    print('from other module')