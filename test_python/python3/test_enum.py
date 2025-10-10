# https://docs.python.org/zh-cn/3/library/enum.html

from enum import Enum , StrEnum, auto

class Color(Enum):
    RED = 1
    GREEN = 2
    BLUE = 3

print(Color.RED)        # Color.RED
print(Color.RED.name)   # RED
print(Color.RED.value)  # 1

for color in Color:
    print(color)        # Color.RED, Color.GREEN, Color.BLUE

print('-------------------------')

# 3.11新增?
class ColorStr(StrEnum):
    RED = 'r'
    GREEN = 'g'
    BLUE = 'b'
    UNKNOWN = auto()

print(ColorStr.RED)        # r
print(ColorStr.RED.name)   # RED
print(ColorStr.RED.value)  # r

for color in ColorStr:
    print(color)        # r, g, b

