import multiprocessing as mp
import os
from tqdm import tqdm

def square(x):
    print("sub process pid: ", mp.current_process().pid)
    return x ** 2

if __name__ == '__main__':
    print(os.getpid())
    print(mp.current_process().pid)
    print(mp.cpu_count())
    numbers = [1, 2, 3, 4, 5]
    with mp.Pool(processes=4) as pool:
        print(mp.current_process().pid)
        results = pool.imap(square, numbers)
        print(results)
        print(list(results))
        print(list(tqdm(results)))
        
        # for x in list(results):
        #     print(x)
    print("\n")



