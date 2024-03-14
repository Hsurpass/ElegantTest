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

-- autoincrement 自增约束
drop table company;
CREATE TABLE COMPANY(
   ID INTEGER PRIMARY KEY     AUTOINCREMENT NOT NULL,
   NAME           TEXT    NOT NULL,
   AGE            INT     NOT NULL,
   ADDRESS        CHAR(50),
   SALARY         REAL
);
select * from sqlite_master where type='table';
select * from sqlite_sequence;

INSERT INto COMPANY (ID,NAME,AGE,ADDRESS,SALARY) values (1, 'Paul', 32, 'California', 20000.00);
insert into company values(2, 'Allen', 25, 'Texas', 15000.00 );
insert into company (NAME,AGE,ADDRESS,SALARY) values('Teddy', 23, 'Norway', 20000.00 );
insert into company (NAME,AGE,ADDRESS,SALARY) values('Mark', 25, 'Rich-Mond ', 65000.00 );
insert into company (NAME,AGE,ADDRESS,SALARY) values('David', 27, 'Texas', 85000.00 );
insert into company (NAME,AGE,ADDRESS,SALARY) values('Kim', 22, 'South-Hall', 45000.00 );
insert into company (NAME,AGE,ADDRESS,SALARY) values('James', 24, 'Houston', 10000.00 );

select * from sqlite_master where type='table';
select * from sqlite_sequence;
delete from company; --删除了company表中的所有数据，但是sqlite_sequence表中的自增序号还没清零。
-- 可以通过删除sqlite_sequence表中的seq字段将计数清零。
delete from sqlite_sequence where name='company';    --不管用？？ 内部表不能修改
-- 或者使用update命令将seq字段置0
update sqlite_sequence set seq=0 where name='company';    -- 不管用？？ 内部表不能修改 
DElete from sqlite_sequence;    --删了,让数据库重新创建

-- 查询company表中所有记录中的全部字段
select * from company;    

--查询company表中所有记录中的部分字段。
select id, name, salary from company;

-- 查询company表中有多少条记录
select COUNT(*) from company;
select COUNT(*) as company_count from company;    -- as的作用：命名

-- 查询当前系统的日期和时间  GMT时间
select current_timestamp;
-- 查询本地时间
select datetime('now', 'localtime');

-- select语句还能做运算
select (10 + 6) as sum;

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
select * from company where age > (select age from company where salary > 65000); --子查询结果为salary>65000的年龄的记录，外查询返回所有年龄大于子查询字段值的记录。
select exists(select *from company where age=40); --age=40的记录不存在
select exists(select *from company where age=25); --age=25的记录不存在，输出1
-- UPDATE
update company set address='Texas' where id = 6;
select * from company;
update company set address='Texas', salary=35000 where id = 6;

-- DELETE
delete from company where id = '1'; --删除一行
delete from company; --删除整个表

-- LIMIT 和 OFFSET
select * from company limit 4;    --从第一条记录开始只输出4条记录
select * from company limit 3 offset 2; --从第3条记录(偏移2条)开始输出3条记录
select * from company limit 2, 3; --从第3条记录(偏移2条)开始输出3条记录, 第一个数字是偏移量(offset)，第二个数字是限制输出条数。

-- ORDER BY
select * from company order by salary;    --基于salary字段的值进行升序排序
select * from company order by salary DESC; --基于salary字段的值进行降序排序
select * from company order by age;    --基于age字段的值进行升序排序
select * from company order by age, salary desc; --基于age字段的值进行升序排序, 然后基于salary进行降序排序

-- GROUP BY
select * from company;
select * from company group by name;    --根据名字进行分组
select NAME, SUM(SALARY) from company group by name; --根据名字进行分组
select NAME, SUM(SALARY) from company group by address; --根据地址进行分组, 然后对同组的salary进行求和
select COUNT(*) from group_count(
    select NAME, SUM(SALARY) from company group by address );
select NAME, SUM(SALARY) from company group by address order by SUM(salary); --根据地址进行分组, 然后对同组的salary进行求和， 然后按照SUM(salary)排序
select NAME, SUM(SALARY) AS sum_salary from company group by address order by sum_salary DESC, name; --根据地址进行分组, 然后对同组的salary进行求和， 然后按照SUM(salary)降序,name升序排序。

--having
insert into company values(8,Paul,24,Houston,20000.0);
insert into company values(9,James,44,Norway, 5000.0);
insert into company values(10,James,45,Texas,5000.0);

select * from company group by name having count(name) < 2; --先根据name进行分组，计算每组的数量，然后输出数量小于2的记录。
select * from company group by address having count(address) >= 2;--先根据address进行分组，计算每组的数量，然后输出数量大于2的记录。

select count(name) from company;      --查找name字段有多少条记录
select count(address) from company;   --查找address字段有多少条记录

--COUNT
select count(NAME) FROM COMPANY;
select count(*) FROM COMPANY;

--AVG
select AVG(salary) FROM COMPANY;

-- DISTINCT
select distinct address from company;
select distinct salary from company;

--union 并集
select * from company order by age;
select * from company order by salary;

select * from company where age>=25 
union
select * from company where salary>30000;-- 将年龄>=25的结果 或者salary>30000的结果合并到一个结果集中。
-- 等同于：
select * from company where age>=25 or salary>30000;

select * from company where age>=25 
union all
select * from company where salary>30000;

-- intersect 交集
select * from company where age>=25 
intersect
select * from company where salary>30000;--查找年龄>=25 并且salary>30000的结果
--等同于：
select *from company where age>=25 and salary>30000;

-- except 差集
select * from company where age>=25 
except
select * from company where salary>30000; --查找属于age>=25结果集，但不属于salary>30000结果集的记录。

select * from company where salary>30000
except
select * from company where age>=25; --查找属于salary>30000结果集，但不属于age>=25结果集的记录。

-- 子查询
select * from company;
select * from company where salary > (select AVG(salary) from company); --查找大于平均工资的记录
select ROUND(AVG(salary)) as avg_slary from company; -- ROUND函数的作用是四舍五入
--select * from company where salsry > avg_slary; -- error

--create table new_table select * from company where salary > 60000;
--insert into new_table select * from company where age between 25 and 40;

-- PRAGMA
PRAGMA test1.auto_vacuum;
pragma test1.cache_size;

pragma case_sensitive_like;
pragma count_changes;
pragma database_list;
pragma encoding;
pragma freelist_count;
pragma index_info;
pragma index_list;
pragma index_mode;
pragma journal_node;
pragma max_page_count;
pragma page_count;
pragma page_size;
pragma parser_trace;
pragma recursive_triggers;
pragma schema_version;
pragma secure_dalete;
pragma sql_trace;
pragma synchronous;
pragma temp_store;
pragma temp_store_directory;
pragma user_version;
pragma writable_schema;


-- join
select * from company;

INSERT INTO DEPARTMENT (ID, DEPT, EMP_ID)
VALUES (1, 'IT Billing', 1 );

INSERT INTO DEPARTMENT (ID, DEPT, EMP_ID)
VALUES (2, 'Engineering', 2 );

INSERT INTO DEPARTMENT (ID, DEPT, EMP_ID)
VALUES (3, 'Finance', 7 );

select * from department;

-- 交叉连接
SELECT EMP_ID, NAME, DEPT FROM COMPANY CROSS JOIN DEPARTMENT; --把第一个表的每一行和第二个表的每一行进行匹配。


--内连接，默认是内连接，INNER是可选的
select * from company;
select * from company inner join department on company.ID == department.EMP_ID;
select id, name, age, salary, dept from company inner join department on company.ID == department.EMP_ID;

 
--左外连接 返回左表中全部的数据和右表中匹配的数据， 右表中没有匹配的数据填NULL
select id, name, age, salary, dept from company left outer join department on company.ID == department.EMP_ID;
select * from company left outer join department on company.ID == department.EMP_ID;

--右外连接 返回右表中全部的数据和左表中匹配的数据， 左表中没有匹配的数据填NULL
select id, name, age, salary, dept from company right outer join department on company.ID == department.EMP_ID;
select * from company right outer join department on company.ID == department.EMP_ID;
select * from company,department where company.ID == department.EMP_ID;

--索引
select * from company;
create index salary_index on company (salary); --在salary这一列上创建索引
create unique index unique_name_index on company (name); --在name这一列上创建唯一索引，列中有相同的值不能创建唯一索引

select * from company INDEXED BY salary_index where salary > 50000; --指定使用salary_index索引来进行查询。

--.indices company; --查看所有索引
select * from sqlite_master where type='index'; --查看所有索引
drop index salary_index; --删除索引。

-- TRIGGER
select * from company;
create table company_log (
    EMP_ID INT NOT NULL,
    OPERATE_TIME TEXT NOT NULL
);
drop table company_log;

--创建一个触发器，当company表执行插入操作时，触发表company_log的插入操作
create trigger company_log after insert on company
begin
    insert into company_log VALUES (new.ID, datetime('now'));
end;

INSERT INTO COMPANY VALUES(8,'JJ',40,'LA',90000.00);

select * from company_log;
select tbl_name from sqlite_master where type='table';

select * from sqlite_master where type='trigger';    --查看所有触发器
select * from sqlite_master where type='trigger' and tbl_name='company'; --查看某个表上的触发器

-- 删除触发器
drop trigger company_log;


--alter
alter table company_log rename to new_company_log; -- 重名名表名

alter table new_company_log add column sex char(1); -- 修改表结构，新增一列
select sql from sqlite_master where type='table' and tbl_name='new_company_log';
select * from new_company_log; 


select *from sqlite_sequence where name="company";

-- view 视图 
create view company_view as select id, name, age from company; --创建一个视图。
select * from company_view; --查看一个视图。
update company set age=44 where id=7; -- 原表数据变化，视图也会跟着变化，因为视图保存的只是一条sql语句。
--alter view company_view as select id, name from company;
drop view company_view; --删除视图


-- 事务
select * from company;
begin;
delete from company where id=7;
rollback;

begin;
delete from company where id=7;
commit;



-- DROP
--DROP TABLE DEPARTMENT;