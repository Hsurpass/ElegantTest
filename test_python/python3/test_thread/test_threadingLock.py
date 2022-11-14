#!/usr/bin/python3

import tarfile
import threading

count = 0
lock = threading.Lock()

def counter():
    global count
    lock.acquire()
    for i in range(10000000):
        count += 1
    lock.release()

# counter()
print(count)

t1 = threading.Thread(target=counter)
t2 = threading.Thread(target=counter)

t1.start()
t2.start()

t1.join()
t2.join()

print(count)



