#!/usr/bin/python3
# pip install pyinstaller
# pyinstaller --onefile progress_bar.py

from tqdm import tqdm, trange
import time

iter = range(100)

for i in tqdm(iter, desc="Processing", unit="item"):
# for i in list(tqdm.tqdm(iter)):
# for i in tqdm(list(tqdm.tqdm(iter))): # TypeError: 'module' object is not callable
    time.sleep(0.01)

for i in trange(1000):
    time.sleep(0.001)