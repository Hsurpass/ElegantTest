#!/usr/bin/python3
# sudo apt-get install python3-tk

import matplotlib
matplotlib.use('TkAgg')

# 查看支持的交互式后端
#['GTK3Agg', 'GTK3Cairo', 'GTK4Agg', 'GTK4Cairo', 'MacOSX', 
# 'nbAgg', 'QtAgg', 'QtCairo', 'Qt5Agg', 'Qt5Cairo', 'TkAgg', 
# 'TkCairo', 'WebAgg', 'WX', 'WXAgg', 'WXCairo']
print(matplotlib.rcsetup.interactive_bk)    

# 查看支持的非交互式后端
# ['agg', 'cairo', 'pdf', 'pgf', 'ps', 'svg', 'template']
print(matplotlib.rcsetup.non_interactive_bk)

import matplotlib.pyplot as plt

import numpy as np

x = np.linspace(-10,10,100) # 创建一个包含-10到10之间100个等距点的数组作为x坐标
y= x ** 2 # 计算y坐标

plt.plot(x, y)  # 绘制曲线
plt.xlabel('x') # 设置x轴标签
plt.xlabel('y') # 设置y轴标签
plt.title('y = x^2') # 设置图标题
plt.grid(True) # 显示网格线

plt.show() #显示图形