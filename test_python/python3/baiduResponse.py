#!/usr/bin/python3

from urllib import request

res = request.urlopen("https://www.baidu.com/")
fi = open("baiduResponse.html", 'w')
page = fi.write( str(res.read()) )
print(page)
fi.close()

