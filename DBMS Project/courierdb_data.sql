insert into security(name, mobile_number, dob, address, sec_id) VALUES ('John', '9999999999', '1965-01-09', '731 Fondren, Houston, TX', 'S0001');
insert into security(name, mobile_number, dob, address, sec_id) VALUES ('Franklin', '9999989999', '1955-12-08', '975 Fire Oak, Humble, TX', 'S0003');
insert into security(name, mobile_number, dob, address, sec_id) VALUES ('Ramesh', '9999997999', '1975-04-02', '980 Dallas, Houston, TX', 'S0002');
insert into security(name, mobile_number, dob, address, sec_id) VALUES ('James', '9999999699', '1969-05-01', '450 Stone, Houston, TX', 'S0004');

insert into student(name, mobile_number, dob, address, stu_id, batch) VALUES ('Manohar', '9919999999', '2001-01-09', '3321 Castle, Spring, TX', 'IMT2019025','IMTech');
insert into student(name, mobile_number, dob, address, stu_id, batch) VALUES ('Chandrahas', '9929999999', '2000-01-09', '731 Fondren, Houston, TX', 'IMT2019019','IMTech');
insert into student(name, mobile_number, dob, address, stu_id, batch) VALUES ('Anish', '9939999999', '2002-01-09', '291 Berry, Bellaire, TX', 'PH2019017','Phd');
insert into student(name, mobile_number, dob, address, stu_id, batch) VALUES ('Jayanth', '9949999999', '2001-01-09', '731 Fondren, Houston, TX', 'DT2018053','Dig Soc');
insert into student(name, mobile_number, dob, address, stu_id, batch) VALUES ('Jeet', '9959999999', '1999-01-09',  '5631 Rice, Houston, TX', 'MT2019052','MTech');
insert into student(name, mobile_number, dob, address, stu_id, batch) VALUES ('Sailesh', '9969999999', '2000-01-09', '1000 Fondren, Houston, TX', 'IMT2017512','IMTech');

insert into delivery_service(serv_id,name) VALUES ('SRV1', 'Flipkart');
insert into delivery_service(serv_id,name) VALUES ('SRV2', 'Amazon');
insert into delivery_service(serv_id,name) VALUES ('SRV3', 'Delhivery');
insert into delivery_service(serv_id,name) VALUES ('SRV4', 'Bluedart');


insert into courier(courier_id,ord_stu_id,ord_sec_id,service_id,updated_at,student_received) VALUES ('OD001', 'IMT2019019', 'S0002', 'SRV1', '2021-12-04',1);
insert into courier(courier_id,ord_stu_id,ord_sec_id,service_id,updated_at,student_received) VALUES ('OD002', 'IMT2019025', 'S0002', 'SRV4', '2021-12-05',0);
insert into courier(courier_id,ord_stu_id,ord_sec_id,service_id,updated_at,student_received) VALUES ('OD003', 'PH2019017', 'S0001', 'SRV1', '2021-12-06',0);
insert into courier(courier_id,ord_stu_id,ord_sec_id,service_id,updated_at,student_received) VALUES ('OD004', 'MT2019052', 'S0003', 'SRV2', '2021-12-06',1);

-- update employee set super_ssn = '333445555', dno = 5 where ssn = '123456789';
-- update employee set super_ssn = '987654321', dno = 4 where ssn = '987987987';
-- update employee set super_ssn = NULL, dno = 1 where ssn = '888665555';