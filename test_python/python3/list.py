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
