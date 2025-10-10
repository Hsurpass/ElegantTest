#!/usr/bin/python3

import sys
import test_module

for i in sys.argv:
    print(i)

print(sys.path)

test_module.func()