/* s, p, sp table 생성*/

show create table s;
select * from s;

/* Records into S */
insert into s values
("s1", "3", "busan"),
("s2", "4", "london"),
("s3", "6", "elcucuy"),
("s4", "8", "newyork")
;

/* Records into P */
insert into p values 
("p1", "tony", "blue"),
("p2", "rafael", "red"),
("p3", "header", "black"),
("p4", "diago", "green")
;

insert into sp values
("s1", "p1", 3),
("s2", "p2", 5),
("s3", "p3", 10),
("s4", "p4", 20)
;


alter table sp 
add constraint fk_snum 
foreign key (snum) references s(snum) 
on delete cascade on update restrict;

alter table sp 
add constraint fk_pnum 
foreign key (pnum) references p(pnum) 
on delete cascade on update restrict;


/* 이미 존재하는 테이블에 primary key 추가*/
alter table add primary key([col_name]);

/* s에 없는 snum으로 sp 테이블의 snum 열을 업데이트 해보기 
	-> 외래 키 제약조건으로 안 됨*/
update sp set snum='s99' where pnum = 'p1';

/* s의 s1을 삭제하면 sp의 s1도 자동으로 삭제 됨을 확인하기 
	-> on delete cascade 조건으로 자동 삭제 됨) */

	

