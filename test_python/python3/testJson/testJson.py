#!/usr/bin/python3

import json

pyObj = { 'a' : 1, 'b' : 2, 'c' : 3, 'd' : 4, 'e' : 5 , 'f': [1,2,3] } 

jsonData = json.dumps(pyObj)
print(jsonData)
print(type(jsonData))

formatJsonData = json.dumps(pyObj, sort_keys=True, indent = 4, separators=(',', ':'))
print(formatJsonData)
print(type(formatJsonData))

print(json.loads(jsonData))
print(json.loads(formatJsonData))




