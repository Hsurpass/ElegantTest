#!/usr/bin/python3

from multiprocessing import Process, Pool
import os

def run_proc(name):
    print('Run child process %s (%s)...' % (name, os.getpid()))

if __name__ == '__main__':
    print('Parent process %s.' % os.getpid())

    childProcess = Process(target=run_proc, args=('test',))
    print(type(childProcess))
    print('Child process will start.')
    childProcess.start()
    childProcess.join()
    print('Child process end.')


