#!/usr/bin/python3

import subprocess


print('$ ls .')
r = subprocess.call(['ls', '.'])
print('Exit code:', r)


print('$ nslookup')
p = subprocess.Popen(['ls'], stdin=subprocess.PIPE, 
            stdout=subprocess.PIPE, stderr=subprocess.PIPE)
output, err = p.communicate(b'set q=mx\npython.org\nexit\n')
print(output.decode('utf-8'))
print('Exit code:', p.returncode)


