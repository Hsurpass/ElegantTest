#!/usr/bin/python3

import re
from flask import Flask

app = Flask(__name__)


def auth(func):
    def inner(*args, **kv):
        r = func(*args, **kv)
        return r
    return inner

def index():
    return "首页"

def info():
    return "用户中心"

def order():
    return "订单中心"

def login():
    return "登录页面"

app.add_url_rule("/index", view_func=index)
app.add_url_rule("/info", view_func=info)
app.add_url_rule("/order", view_func=order)
app.add_url_rule("/login", view_func=login)

app.run()


