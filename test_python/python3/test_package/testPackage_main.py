#!/usr/bin/python3

# from testPackage.test1 import test1
# from testPackage.test2 import test2

#包不能直接导入，模块可以直接导入
# from testPackage import *
# import testPackage

from testPackage.test1 import *
from testPackage.test2 import *
# import testPackage.test1  #error
# import testPackage.test2  #error

test1()
test2()