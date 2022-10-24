#!/usr/bin/python3

import pickle, pprint

# 使用pickle模块将数据对象保存到文件
data1 = {'a': [1, 2.0, 3, 4+6j],
         'b': ('string', u'Unicode string'),
         'c': None}
print(data1)

selfref_list = [1, 2, 3]
selfref_list.append(selfref_list)        
print(selfref_list)

output = open('data.pkl', 'wb')
# Pickle dictionary using protocol 0.
pickle.dump(data1, output)

# Pickle the list using the highest protocol available.
pickle.dump(selfref_list, output, -1)

output.close()

#使用pickle模块从文件中重构python对象
pkl_file = open('./data.pkl', 'rb')
data2 = pickle.load(pkl_file)
print(data2)
pprint.pprint(data2)

data3 = pickle.load(pkl_file)
print(data3)
pprint.pprint(data3)
pkl_file.close()

print('########################')
#用循环是因为发现pickle.load(f)每次运行只能读取一行
with open("./data.pkl", 'rb') as f:
    while True:
        try:
            print(pickle.load(f))
        except EOFError:
            f.close()
            break


