#!/usr/bin/python3

import os

print('Process (%s) start...' % os.getpid())

pid = os.fork()
if pid == 0:
    print('I am child process (%s) and my parent is %s.' % (os.getpid(), os.getppid()))
elif pid > 0:
    print('I (%s) just created a child process (%s).' % (os.getpid(), pid))
else:
    print("fork error")


