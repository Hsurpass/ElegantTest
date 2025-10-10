import sys
import os

# true
# sys.path.append(os.path.abspath(".."))  # 添加上级目录到模块搜索路径
# from dir2 import test2

# error
# from ..dir2.test2 import test2

# true
# print(sys.path)
# print(__file__)
# print(os.path.dirname(__file__))
# print(os.path.abspath(os.path.dirname(__file__)))
# print(os.path.dirname(os.path.abspath(os.path.dirname(__file__))))
# sys.path.insert(0, os.path.dirname(os.path.abspath(os.path.dirname(__file__))))
# from dir2 import test2

print(os.path.abspath(__file__))
print(os.path.dirname(os.path.abspath(__file__)))
print(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from dir2 import test2

print(sys.path)
test2.test2()