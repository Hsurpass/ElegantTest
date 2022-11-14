#!/usr/bin/python3

from io import StringIO

strio = StringIO()
print(strio.write('hello'))
print(strio.write(' '))
print(strio.write('world!'))

print(strio.getvalue())

strio.close()

f = StringIO('Hello!\nHi!\nGoodbye!')
while True:
    line = f.readline()
    if line == '':
        break
    print(line.strip())

f.close()