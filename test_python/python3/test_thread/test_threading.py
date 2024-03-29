#!/usr/bin/python3

import time, threading

print("main thread:", threading.current_thread().name)

# 新线程执行的代码:
def loop():
    print('thread %s is running...' % threading.current_thread().name)
    n = 0
    while n < 5:
        n = n + 1
        print('thread %s >>> %s' % (threading.current_thread().name, n))
        time.sleep(1)
    print('thread %s ended.' % threading.current_thread().name)

t = threading.Thread(target = loop, name = "LoopThread")
t.start()
t.join()

print("main thread:", threading.current_thread().name)
