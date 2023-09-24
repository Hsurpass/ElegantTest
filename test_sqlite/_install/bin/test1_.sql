select tbl_name from sqlite_master where type='table'; --查看都有哪些表 等同于 命令提示符中的.tables命令
select sql from sqlite_master where type='table' and tbl_name='COMPANY'; --查看创建表的命令 等同于 命令提示符中的.schema 命令

CREATE TABLE COMPANY(
   ID INT PRIMARY KEY     NOT NULL,
   NAME           TEXT    NOT NULL,
   AGE            INT     NOT NULL,
   ADDRESS        CHAR(50),
   SALARY         REAL
);

CREATE TABLE DEPARTMENT(
   ID INT PRIMARY KEY      NOT NULL,
   DEPT           CHAR(50) NOT NULL,
   EMP_ID         INT      NOT NULL
);

-- 插入数据
INSERT INto COMPANY (ID,NAME,AGE,ADDRESS,SALARY) values (1, 'Paul', 32, 'California', 20000.00);
insert into company values(2, 'Allen', 25, 'Texas', 15000.00 );
insert into company values(3, 'Teddy', 23, 'Norway', 20000.00 );
insert into company values(4, 'Mark', 25, 'Rich-Mond ', 65000.00 );
insert into company values(5, 'David', 27, 'Texas', 85000.00 );
insert into company values(6, 'Kim', 22, 'South-Hall', 45000.00 );
insert into company values(7, 'James', 24, 'Houston', 10000.00 );

-- 查询company表中所有记录中的全部字段
select * from company;    

--查询company表中所有记录中的部分字段。
select id, name, salary from company;

--比较运算符
select * from company where salary > 50000;
select * from company where salary = 20000;
select * from company where salary != 20000;
select * from company where salary <> 50000; --同 !=
select * from company where salary >= 65000;
select * from company where salary == 65000;

--逻辑运算符
-- and / or
select * from company where age>=25 and salary >= 65000;
select * from company where age>=25 or salary >= 65000;

-- is / is not
select * from company where salary is 65000;
select * from company where salary is not 65000;

select * from company where age is NULL;
select * from company where age is not NULL;

-- like / glob
select * from company where name like "Ki%";
select * from company where name glob "P*";

-- in / not in
select * from company where age == 25 or age = 27;
select * from company where age is 25 or age is 27;

select * from company where age in (25,27);
select * from company where age not in (25,27);

-- between
select * from company where age between 23 and 27;    --查找年龄在25到27之间的所有记录

-- exists
select * from company where exists (
    select age from company where salary > 90000); -- 子查询语句结果为真，外查询返回全部结果
select * from company where not exists (
    select age from company where salary > 90000); -- 子查询语句结果为真，not exists(子查询)为假，则外查询不会返回结果
select * from company where age > (select age from company where salary > 65000) --子查询结果为salary>65000的年龄的记录，外查询返回所有年龄大于子查询字段值的记录。


--DROP TABLE DEPARTMENT