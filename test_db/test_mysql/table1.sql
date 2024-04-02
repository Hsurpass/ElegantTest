SHOW DATABASES;       # 查看数据库

use mysql;	# 切换数据库

show TABLES;

select user, host from user where user='root'; 				# 查看root访问权限
select user, host from user where user='test'; 				# 查看test访问权限
select user, host from mysql.user where user='test'; 	# 查看test访问权限

select * from mysql.`user`;		# 查看mysql数据库中user表
show VARIABLES like '%port%';	# 查看都有哪些端口
show GRANTS for 'test'@'%'; 	# 查看test用户都有哪些权限