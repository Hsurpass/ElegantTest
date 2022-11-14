#!/usr/bin/python3

from ctypes.wintypes import BYTE
from io import BytesIO

binio = BytesIO()
binio.write('中文'.encode('utf-8'))
print(binio.getvalue())

binio.close()

f = BytesIO(b'\xe4\xb8\xad\xe6\x96\x87')
print(f.read())
f.seek(0)
print(f.read().decode("utf-8"))

f.close()
