#!/usr/bin/python3

# from testPackage.test1 import test1
# from testPackage.test2 import test2

#包不能直接导入，模块可以直接导入
# from testPackage import *
# import testPackage
import testPackage
from testPackage.test1 import test1, a
from testPackage.test2 import *
# import testPackage.test1  #error
# import testPackage.test2  #error

print(testPackage.__version__)
print(testPackage.__author__)

test1()
print(a)
test2()