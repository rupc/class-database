create table ssp (
snum varchar(6), 
city varchar(8), 
status int, 
pnum varchar(6), 
qty int
);

insert into ssp values 
('s9', 'busan', 100, 'p1', 10),
('s9', 'busan', 100, 'p2', 20);

delete from ssp where snum = 's8';

create table s (
	snum varchar(6) primary key,
	status int,
	city varchar(8)
);

insert into s values
('s1', 100, 'busan'),
('s2', 100, 'busan'),
('s3', 100, 'busan')
;

delete from s where snum = 's1';

create table sp(
	snum varchar(6),
	pnum varchar(6),
	qty int
);

create view sc as select snum, city from s;
create view cs as select city, snum from s;
create view ss as select snum, status from s;
insert into sc values 
('s1', 'busan')
;

insert into cs values
('busan', 100)
;

create table ss (
	snum varchar(6) primary key,
	sname varchar(10),
	status int,
	city varchar(10)
);

create table sjt (
	snum varchar(6) primary key,
	jname varchar(6),
	tname varchar(6)
);

insert into sjt values
('s1', 'db', 'hong'),
('s1', 'os', 'kim'),
('s2', 'db', 'park'),
('s2', 'os', 'lee'),
('dirty', 'db', 'choi')
;

// s2 제거시, os, lee 정보도 같이 사라짐 -> lossy information
// st, tj로 쪼갬.

create table st (
	snum varchar(6),
	tname varchar(6)
);
create table tj (
	tname varchar(6),
	jname varchar(6)
);

insert into st values 
('s1', 'hong'),
('s1', 'kim'),
('s2', 'park'),
('s2', 'lee'),
('s3', 'hong'),
('s95', 'choi')
;

insert into tj values
('hong', 'db'),
('kim', 'os'),
('park', 'db'),
('lee', 'os'),
('choi', 'db'),

