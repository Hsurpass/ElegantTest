#!/usr/bin/python2
# coding=utf-8

import thread, threading
import time

def printFunc(threadName, id):
    time.sleep(2)
    print(threadName, id)
    thread.exit()
try:
    thread.start_new_thread(printFunc, ("thread1", 1))
except SystemExit as err:
    print(err, "thread exit")
except:
    print("start thread failed")

# threading.currentThread()
threadinglist = threading.enumerate()
print(threadinglist)
print(threading.active_count())

time.sleep(3)

def print_time(threadName, counter):
    while counter:
        time.sleep(1)
        print("%s:%s" % (threadName, time.ctime(time.time())))
        counter -= 1

threadLock = threading.Lock()
class myThread(threading.Thread):
    def __init__(self, threadId, name, counter):
        threading.Thread.__init__(self)
        self.threadId = threadId
        self.name = name
        self.counter = counter
    
    def run(self):
        print("start thread: ", self.name)
        threadLock.acquire()
        print_time(self.name, self.counter)
        threadLock.release()

thread1 = myThread(1, "Thread-1", 2)
thread2 = myThread(2, "Thread-2", 3)

thread1.start()
thread2.start()

threads = []
threads.append(thread1)
threads.append(thread2)

for t in threads:
    t.join()

print("exit main thread")

