#!/usr/bin/python3

import sys

list = [1, 2, 3, 4]
it = iter(list)
print(next(it))
print(next(it))
print(next(it))
print(next(it))
# print(next(it)) #StopIteration


it = iter(list)
for x in it:
    print(x, end=" ")
print()

it = iter(list)
while True:
    try:
        print(next(it), end=" ")
    except StopIteration:
        # sys.exit()
        break
print()

for x in list:
    print(x, end=" ")
print()

print(len(list))
for i in range(len(list)):
    print(list[i], end=" ")
print()