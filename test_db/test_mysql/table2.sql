SHOW DATABASES;       # 查看数据库

use mysql;

show TABLES;

select user, host from user where user='root'; 				# 查看root访问权限
select user, host from user where user='test'; 				# 查看test访问权限
select user, host from mysql.user where user='test'; 	# 查看test访问权限

select * from mysql.`user`;		# 查看mysql数据库中user表
show VARIABLES like '%port%';	# 查看都有哪些端口
show GRANTS for 'test'@'%'; 	# 查看test用户都有哪些权限

#######数据库########

CREATE DATABASE test1;						# 创建数据库test1
DROP DATABASE test1;    					# 删除数据库
DROP DATABASE if EXISTS test1;    # 删除数据库
use test1;              					# 切换数据库

#######表########
 # 查看表
show TABLES;   
            
# 创建表
create TABLE test_table1(id int);
create TABLE test1.test_table2(id int, _date DATE); 

# 删除表
drop table test_table1;
drop table test_table2;           
           

# 重命名表
ALTER table test_table1 RENAME student;     

# 查看表结构
desc test_table1;                 
DESCRIBE test_table1;  
DESCRIBE test_table2; 
SHOW COLUMNS from test1.test_table2;

#查看表的详细定义
SHOW CREATE TABLE test_table1;

######## 修改表结构 ########
# 修改表中字段类型
alter table test_table1 modify id tinyint;  

# 修改表中字段名字
alter table test_table1 CHANGE age AGE INT; 

# 添加一个新的列(字段)
alter table test_table1 add COLUMN age int;

# 删除一列(字段)
alter table test_table2 drop COLUMN city2;    


######### 行操作 #########
# 插入一行数据
insert into test1.test_table2 VALUES(1, "2008-12-1");
insert into test1.test_table2 VALUES(2, "2008/12/2");

# 删除一行数据
DELETE from test1.test_table2 WHERE id = 1;
# 删除表中的全部数据
DELETE from test1.test_table2;
TRUNCATE TABLE test1.test_table2;

# 查询数据
select * from test1.test_table2;

# 测试 TIMESTAMP TIME
alter table test1.test_table2 add COLUMN _timestmp TIMESTAMP;
alter table test1.test_table2 add COLUMN _time TIME;

insert into test1.test_table2 VALUES(3, "2008/12/3", NOW(), '11:10:00');
insert into test1.test_table2 VALUES(4, "2008/12/4", "2008-12-4", '11:11:00');
insert into test1.test_table2 VALUES(5, "2008/12/5", '2008/12/5 11:12:00', '11:12:00');
insert into test1.test_table2 VALUES(6, "2008/12/6", '2008-12-6 11:13:00', '11:13:00');
insert into test1.test_table2 VALUES(7, CURDATE(), CURTIME(), NOW());

# 测试YEAR DATETIME
alter table test1.test_table2 add COLUMN _year YEAR;
alter table test1.test_table2 add COLUMN _dateTime DATETIME;
insert into test1.test_table2 VALUES(8, CURDATE(), CURTIME(), NOW(), 2013, '2008-12-8 11:18:00');
insert into test1.test_table2 VALUES(9, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW());

# 测试char(n) varchar(n)
ALTER TABLE test1.test_table2 add COLUMN name char(4);
-- Column length too big for column 'name1' (max = 255); use BLOB or TEXT instead
-- char(n) 中 n的取值范围 [1,255], n代表字符个数
ALTER TABLE test1.test_table2 add COLUMN name1 char(0); 

ALTER TABLE test1.test_table2 add COLUMN city varchar(4);
ALTER TABLE test1.test_table2 add COLUMN city1 varchar(16300);

# 查看某个字段中的数据所占用的字节数
SELECT * from test1.test_table2;
SELECT LENGTH(name), LENGTH(city) from test1.test_table2;
SELECT CHAR_LENGTH(name), CHAR_LENGTH(city) from test1.test_table2;
SELECT CHARACTER_LENGTH(name), CHARACTER_LENGTH(city) from test1.test_table2;
SELECT BIT_LENGTH(name), BIT_LENGTH(city) from test1.test_table2;

insert into test1.test_table2 VALUES(10, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW(), "", ""); -- LENGTH(name): 0 LENGTH(city): 0

insert into test1.test_table2 VALUES(11, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW(), "         ", "                      "); -- LENGTH(name): 0 LENGTH(city): 4

insert into test1.test_table2 VALUES(12, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW(), "abcd", "abcd");

-- Data too long for column 'name' and 'city' at row 1. 
insert into test1.test_table2 VALUES(13, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW(), "abcde", "abcde"); 

insert into test1.test_table2 VALUES(14, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW(), "你好", "世界");

insert into test1.test_table2 VALUES(15, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW(), "周星驰", "长江七号");

-- 说明(4)表示该字段只能存储4个字符，而不是4个字节(因为汉字占3个字节)
insert into test1.test_table2 VALUES(16, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW(), "当你定义",
"当你定义");


# 测试int(n)
ALTER TABLE test1.test_table2 add COLUMN _age int(2);

INSERT INTO test1.test_table2 VALUES(16, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW(), "当你定义", "当你定义", 12);

INSERT INTO test1.test_table2 VALUES(16, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW(), "当你定义", "当你定义", 123);
INSERT INTO test1.test_table2 VALUES(16, CURDATE(), CURTIME(), NOW(), CURDATE(), NOW(), "当你定义", "当你定义", 1234567890);

# 测试text(n)
DESCRIBE test1.test_table2;
ALTER TABLE test1.test_table2 drop COLUMN addr11;

ALTER TABLE test1.test_table2 add COLUMN addr text(2); -- 自动转换成tinytext
ALTER TABLE test1.test_table2 add COLUMN addr1 text;
ALTER TABLE test1.test_table2 add COLUMN addr2 mediumtext; 
ALTER TABLE test1.test_table2 add COLUMN addr3 longtext; 

# 测试blob(n)
ALTER TABLE test1.test_table2 add COLUMN addr1 blob(4);


# 测试decimal
ALTER TABLE test1.test_table2 add COLUMN price DECIMAL(5,2);
ALTER TABLE test1.test_table2 add COLUMN price1 FLOAT(5,2);
ALTER TABLE test1.test_table2 add COLUMN price2 DOUBLE(5,2);

INSERT INTO test1.test_table2 VALUES()

SELECT LENGTH(price), LENGTH(price1), LENGTH(price2) from test1.test_table2;











