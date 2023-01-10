```sql
Create table If Not Exists Person (id int, email varchar(255))
Truncate table Person
insert into Person (id, email) values ('1', 'a@b.com')
insert into Person (id, email) values ('2', 'c@d.com')
insert into Person (id, email) values ('3', 'a@b.com')

# where子句无法与聚合函数一起使用，因为where子句的运行顺序排在第二，运行到where时，表还没有被分组。
# 如果要对分组查询的结果进行筛选，可以使用having子句。

# Write your MySQL query statement below
select Email
from Person
group by Email
having count(Email) > 1;

# Write your MySQL query statement below
select Email from
(
    select Email, count(Email) as cnt
    from Person
    group by Email
) as t
where cnt > 1;
```
