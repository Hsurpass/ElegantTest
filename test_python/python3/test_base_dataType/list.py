#! /usr/bin/python3

list = ['hello', 786, 2.23, 'john', 70.2]
tinyList = [123, 'world']

print(list )     #['hello', 786, 2.23, 'john', 70.2]
print(list[0])   #['hello']
print(list[1:3]) #[786, 2.23]
print(list[2:])  #[2.23, 'john', 70.2]
print(tinyList * 2)  #[123, 'world', 123, 'world']
print(list + tinyList)   #['hello', 786, 2.23, 'john', 70.2, 123, 'world']
print(list[0:-1]) #['hello', 786, 2.23, 'john']
print(list[2:-1]) #[2.23, 'john']
print(list[-1]) #[70.2]

list[1] = 789
print(list)      #['hello', 789, 2.23, 'john', 70.2]
print(list[:])   #['hello', 789, 2.23, 'john', 70.2]



print("$$$$$$$$$$$$$$$$$$$$$$$$$$")
for i, value in enumerate(list):
    print(i, value)

for x, y in [(1, 1), (2, 4), (3, 9)]:
    print(x, y)

for i, val in enumerate([(1, 1), (2, 4), (3, 9)]):
    print(i, val)


'''
在Python中，list和tuple是两种不同的数据类型，它们之间有以下主要区别：

可变性：list是可变的，这意味着你可以在一个list中添加、删除或更改元素。而tuple是不可变的，一旦它被创建，就不能更改。
例如：
a_list = [1, 2, 3]  
a_list[0] = 0  # 这是合法的  
  
a_tuple = (1, 2, 3)  
a_tuple[0] = 0  # 这将抛出一个错误

占用空间：tuple的内存占用比list小。所以，如果你有大量不变的数据需要存储，使用tuple可能会更高效。
字典键：由于tuple的不可变性，它们可以用作字典的键。然而，由于list是可变的，所以它们不能用作字典的键。

'''

print("###########################")
#如果第三个参数为负数表示逆向读取，可以用于翻转：
#翻转列表
l = ["abc", 10, 20.5]
print(l[-1::-1])    #[20.5, 10, "abc"]
print(l[::-1])    #[20.5, 10, "abc"]

#翻转字符串
str = "abcdefg"
print(str[-1::-1])  #gfedcba
print(str[::-1])  #gfedcba

#翻转元组
tuple = ["ab", 100, 10.5]
print(tuple[-1::-1]) #[10.5, 100, "ab"]
print(tuple[::-1]) #[10.5, 100, "ab"]

def reverseWorlds(input):

    # 通过空格将字符串分隔符，把各个单词分隔为列表
    inputWords = input.split(" ")   #变成list
    print(type(inputWords), id(inputWords))
    print(inputWords)

    # 翻转字符串
    # 假设列表 list = [1,2,3,4],  
    # list[0]=1, list[1]=2 ，而 -1 表示最后一个元素 list[-1]=4 ( 与 list[3]=4 一样)
    # inputWords[-1::-1] 有三个参数
    # 第一个参数 -1 表示最后一个元素
    # 第二个参数为空，表示移动到列表末尾
    # 第三个参数为步长，-1 表示逆向
    inputWords=inputWords[-1::-1]
    print(inputWords, type(inputWords), id(inputWords))
    output = ' '.join(inputWords)
    
    return output

if __name__ == "__main__":
    input = 'I like runoob'
    rw = reverseWorlds(input)
    print(rw)
