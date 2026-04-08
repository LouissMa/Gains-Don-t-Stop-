create database if not exists hr_system default character set utf8mb4;
use hr_system;

drop table if exists salary_history;
drop table if exists employee;
drop table if exists department;

create table department (
    dept_id int primary key auto_increment,
    dept_name varchar(50) not null,
    location varchar(100) null
);

create table employee (
    emp_id int primary key auto_increment,
    emp_name varchar(50) not null,
    gender char(1) not null,
    email varchar(100) unique,
    phone varchar(20) null,
    hire_date date not null,
    salary decimal(10,2) null,
    dept_id int null,
    constraint fk_employee_department
        foreign key (dept_id) references department(dept_id)
        on update cascade
        on delete set null
);

create table salary_history (
    id int primary key auto_increment,
    emp_id int not null,
    old_salary decimal(10,2) null,
    new_salary decimal(10,2) not null,
    adjust_date date not null,
    reason varchar(200) null,
    constraint fk_salary_history_employee
        foreign key (emp_id) references employee(emp_id)
        on update cascade
        on delete cascade
);

insert into department (dept_name, location) values
('研发部', '上海-9F'),
('市场部', '北京-12F'),
('人事部', '上海-6F');

insert into employee (emp_name, gender, email, phone, hire_date, salary, dept_id) values
('张伟', 'M', 'zhangwei@corp.com', '13800000001', '2022-03-01', 18000.00, 1),
('李娜', 'F', 'lina@corp.com', '13800000002', '2021-07-15', 15000.00, 1),
('王强', 'M', 'wangqiang@corp.com', '13800000003', '2020-11-20', 12000.00, 2),
('赵敏', 'F', 'zhaomin@corp.com', null, '2023-02-10', 9000.00, 3),
('陈晨', 'M', 'chenchen@corp.com', '13800000005', '2019-05-08', 20000.00, 1);

insert into salary_history (emp_id, old_salary, new_salary, adjust_date, reason) values
(1, 16000.00, 18000.00, '2024-01-01', '年度调薪'),
(2, 14000.00, 15000.00, '2023-06-01', '绩效调薪'),
(3, 10000.00, 11000.00, '2022-01-01', '年度调薪'),
(3, 11000.00, 12000.00, '2023-01-01', '年度调薪'),
(4, 8500.00, 9000.00, '2023-10-01', '试用期转正'),
(5, 18000.00, 20000.00, '2024-04-01', '关键岗位保留');
