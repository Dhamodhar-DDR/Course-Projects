create database courierdb;
use courierdb;

create table security(
    name varchar(30) NOT NULL,
    mobile_number varchar(10) NOT NULL,
    dob date,
    address varchar(30),
    sec_id varchar(5),
    constraint pk_security PRIMARY KEY (sec_id)
);

create table student(
    name varchar(30) NOT NULL,
    mobile_number varchar(10) NOT NULL,
    dob date ,
    address varchar(30) ,
    stu_id varchar(10),
    batch varchar(10) NOT NULL,
    constraint pk_student PRIMARY KEY (stu_id)
);

create table delivery_service(
    serv_id varchar(5),
    name varchar(30) NOT NULL,
    constraint pk_delivery_service PRIMARY KEY (serv_id)
);

create table courier(
    courier_id varchar(30),
    ord_stu_id varchar(10),
    ord_sec_id varchar(5),
    service_id varchar(5),
    updated_at date NOT NULL,
    student_received boolean NOT NULL,
    constraint pk_courier PRIMARY KEY (courier_id)
);
