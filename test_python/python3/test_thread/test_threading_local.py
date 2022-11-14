#!/usr/bin/python3

#https://www.cnblogs.com/whatisfantasy/p/6440585.html

import threading

localName = threading.local()

def process_student():
    # 获取当前线程关联的student:
    std = localName.student
    print('Hello, %s (in %s)' % (std, threading.current_thread().name))

def process_thread(name):
    # 绑定ThreadLocal的student:
    localName.student = name
    process_student()

t1 = threading.Thread(target= process_thread, args=('Alice',), name='Thread-A')
t2 = threading.Thread(target= process_thread, args=('Bob',), name='Thread-B')
t1.start()
t2.start()
t1.join()
t2.join()
