import tracemalloc

class FileIterator:
    def __init__(self, file_name):
        self.file = open(file_name, 'r')
        self.current_line = 0

    def __iter__(self):
        return self

    def __next__(self):
        line = self.file.readline()
        if not line:
            self.file.close()
            raise StopIteration
        self.current_line += 1
        return line

tracemalloc.start()

# 把文件一次性加载到内存中
with open('qa.log', 'r') as f:
    lines = f.readlines()

# with open('qa.log', 'r') as f:
#     for line in f:
#         # print(line.strip())
#         pass
# == 使用迭代器 内存使用量和上面方法一致 ==
# file_itr = FileIterator('qa.log')
# for line in file_itr:
#     # print(f"Line {file_itr.current_line}: {line.strip()}")
#     pass

current, peak = tracemalloc.get_traced_memory()
print(f"Current memory usage is {current / 1024**2}MB; Peak was {peak / 1024**2}MB")
tracemalloc.stop()