
def generator_numbers(n):
    for i in range(n):
        print("before yield", i)
        yield i
        print("after yield", i)

# gen = generator_numbers(3)
# print(next(gen))
# print("-------")
# for num in gen:
#     print(num)

# print(next(gen, 'No more numbers'))


def generator_file(filepath):
    with open(filepath, 'r') as f:
        for line in f:
            yield line.strip()

# line_gen = generator_file('test.log')
# for line in line_gen:
#     print(line)

def fib_generator(n):
    cur, next = 0, 1
    while True:
        yield cur
        cur, next = next, cur + next

fib_gen = fib_generator(10)
for _ in range(10):
    print(next(fib_gen))
