SHOW DATABASES;       # 查看数据库

CREATE DATABASE test;	# 创建数据库

-- DROP DATABASE test;# 删除数据库

use test;             # 切换数据库


show TABLES;                # 查看表

create TABLE class(id int); # 创建表

desc class;                 # 查看表结构
DESCRIBE class;             # 查看表结构

drop table class;           # 删除表

alter table class modify id tinyint;  # 修改表中字段类型
alter table class CHANGE age AGE INT; # 修改表中字段名字

alter table class add COLUMN age int; # 添加一个新的列(字段)
alter table class drop COLUMN age;    # 删除一列(字段)

-- ALTER table class RENAME student;     # 重命名表

