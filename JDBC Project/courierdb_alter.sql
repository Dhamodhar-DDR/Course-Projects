alter table courier
    add constraint fk_student_courier FOREIGN KEY (ord_stu_id) REFERENCES student(stu_id);

alter table courier
    add constraint fk_security_courier FOREIGN KEY (ord_sec_id) REFERENCES security(sec_id);

alter table courier
    add constraint fk_service_courier FOREIGN KEY (service_id) REFERENCES delivery_service(serv_id);