#!/usr/bin/python3

from xml.dom.minidom import parse
from xml.dom import minidom

# 使用minidom解析器打开 XML 文档
DOMTree = minidom.parse("movies.xml")
collection = DOMTree.documentElement
if collection.hasAttribute("shelf"):
    print("Root element : %s" % collection.getAttribute("shelf"))
# 在集合中获取所有电影
movies = collection.getElementsByTagName("movie")

for movie in movies:
    print("************Movie************")
    if movie.hasAttribute("title"):
        print("Title:%s" % movie.getAttribute("title"))

    type = movie.getElementsByTagName('type')[0]
    print("type:%s" % (type.childNodes[0].data) )
    format = movie.getElementsByTagName('format')[0]
    print("format:%s" % (format.childNodes[0].data) )
    # year = movie.getElementsByTagName('year')[0]
    # print("year:%s" % (year.childNodes[0].data) )
    rating = movie.getElementsByTagName('rating')[0]
    print("rating:%s" % (rating.childNodes[0].data) )
    stars = movie.getElementsByTagName('stars')[0]
    print("stars:%s" % (stars.childNodes[0].data) )
    description = movie.getElementsByTagName('description')[0]
    print("description:%s" % (description.childNodes[0].data) )




