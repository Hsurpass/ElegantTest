#!/usr/bin/python3

import smtplib

from email.mime.text import MIMEText
from email.header import Header


sender = 'my@qq.com'
receiver = '1742143252@qq.com'

message = MIMEText('Python SMTP 发送测试', 'plain', 'utf-8')
message['From'] = Header("mytest", 'utf-8')
message['to'] = Header('smtptest', 'utf-8')

subject = 'Python SMTP 测试邮件'
message['Subject'] = Header(subject, 'utf-8')

try:
    smtpObj = smtplib.SMTP('localhost')
    smtpObj.sendmail(sender, receiver, message.as_string())
    print("send mail succ")
except smtplib.SMTPException:
    print("Error: send mail error")


