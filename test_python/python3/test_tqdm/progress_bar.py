#!/usr/bin/python3
# pip install pyinstaller
# pyinstaller --onefile progress_bar.py

import tqdm
import time

iter = range(100)

for i in tqdm.tqdm(iter):
# for i in list(tqdm.tqdm(iter)):
# for i in tqdm(list(tqdm.tqdm(iter))): # TypeError: 'module' object is not callable
    time.sleep(0.01)