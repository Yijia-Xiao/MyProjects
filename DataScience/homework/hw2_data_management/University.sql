-- drop database university;
create database University;
use University;

-- then we import the data using wizard into table named 'raw'

create table if not exists department(select distinct dept_name, building, budget from raw where dept_name != 'null');
select * from department;
alter table department add primary key(dept_name);
select * from department;
-- we can find that after altering the primary key, the entities are arranged in dictionary order of dept_name

-- drop table instructor;
create table if not exists instructor(select distinct i_ID, i_name, salary from raw where i_ID != 'null');
alter table instructor add primary key(i_ID);
select * from instructor;

create table if not exists student(select distinct s_ID, s_name, tot_cred from raw where s_ID != 'null');
alter table student add primary key(s_ID);
select * from student;

create table if not exists stu_new(select * from student where tot_cred >= 100);
select * from stu_new;

create table if not exists ins_new(select * from instructor where salary <= 70000.00);
select * from ins_new;

create table if not exists dep_new(select * from department where budget >= 80000.00 order by budget desc);
select * from dep_new;

select * from instructor;

select avg(salary)
from instructor
where 50000.00 <= salary and salary <= 100000.00;

create table if not exists work(select distinct i_ID, dept_name from raw where i_ID != 'null'); 
select * from work;

create table if not exists belong(select distinct s_ID, dept_name from raw where s_ID != 'null');
select * from belong;

create table if not exists advise(select i_ID, s_ID from raw where i_ID != 'null' and s_ID != 'null');
select * from advise;

create table if not exists nat_join(select * from student natural join advise);
-- select * from nat_join;

-- drop table temp_stu_ins;
create table if not exists temp_stu_ins(select dept_name, count(s_ID), count(i_ID) from raw group by dept_name);
create table if not exists big_dept(select * from temp_stu_ins where `count(s_ID)` >= 2);
ALTER TABLE big_dept CHANGE `count(s_ID)` s_num int;
ALTER TABLE big_dept CHANGE `count(i_ID)` i_num int;
select * from big_dept;



create table if not exists natural_join(select * from student natural join advise);
select * from student inner join advise on student.s_ID = advise.s_ID;
-- create table if not exists inner_join(select * from student inner join advise on student.s_ID = advise.s_ID);
select * from student left outer join advise on student.s_ID = advise.s_ID;
select * from student right outer join advise on student.s_ID = advise.s_ID;
-- create table if not exists full_join(
ALTER TABLE advise CHANGE s_ID s_advise_ID varchar(255);

drop table full_join;
create table if not exists full_join(
select * from advise left outer join student on student.s_ID = advise.s_advise_ID
union
select * from advise left outer join student on student.s_ID = advise.s_advise_ID);
-- create table if not exists full_join(select * from student left outer join advise on student.s_ID = advise.s_advise_ID
-- union
-- select * from student right outer join advise on student.s_ID = advise.s_advise_ID);

create table if not exists instructor_stu_num(select i_ID, count(s_ID) from full_join group by i_ID);
alter table instructor_stu_num change `count(s_ID)` s_num int;
alter table instructor_stu_num change i_ID i_ID_stu_num int;
select * from instructor_stu_num;

-- update part
-- drop table test_salary;
-- create table test_salary(sal int, stu int);
-- insert into test_salary(sal, stu) values(1000, 2);
-- insert into test_salary(sal, stu) values(2000, 1);
-- select * from test_salary;
-- SET SQL_SAFE_UPDATES = 0;
-- update test_salary set sal=sal * 2 where stu > 1;
-- select * from test_salary;

create table if not exists copied_ins(select * from instructor);
create table if not exists salary_stu_num(
select * from instructor left join instructor_stu_num on instructor.i_ID = instructor_stu_num.i_ID_stu_num
union
select * from instructor right join instructor_stu_num on instructor.i_ID = instructor_stu_num.i_ID_stu_num);

-- update process
update salary_stu_num set salary = salary * 2 where s_num >= 2;
select * from salary_stu_num;

-- delete part
create table if not exists copied_dept(select * from department);
select * from copied_dept;
delete from copied_dept where budget <= 50000.00;
select * from copied_dept;

-- no use below
-- SELECT * FROM student INNER JOIN instructor ON student.=t_type.id;
-- Join table student with table advise conditioning on student ID under the following
-- join types.
-- i. natural join
-- ii. inner join
-- iii. left outer join
-- iv. right outer join
-- v. full outer join