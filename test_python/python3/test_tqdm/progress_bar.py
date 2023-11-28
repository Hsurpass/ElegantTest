#!/usr/bin/python3
# pip install pyinstaller
# pyinstaller --onefile progress_bar.py

import tqdm
import time
for i in tqdm.tqdm(range(100)):
    time.sleep(0.1)