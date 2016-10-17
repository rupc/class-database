create table S
(
snum varchar(4), 
sname varchar(10), 
status int, 
city varchar(10)
);

create table P
(pnum varchar(4), 
pname varchar(10), 
color varchar(10), 
weight float, 
city varchar(10)
);

create table SP
(snum varchar(4), 
pnum varchar(4), 
qty int
);

insert into S values
('s1', 'smith', 20, 'london'),
('s2', 'jones', 10, 'paris'),
('s3', 'blake', 30, 'paris'),
('s4', 'clark', 20, 'london'),
('s5', 'adams', 30, 'athens');

insert into P values
('p1', 'nut', 'red', 12.0, 'london'),
('p2', 'bolt', 'green', 17.0, 'paris'),
('p3', 'screw', 'blue', 17.0, 'rome'),
('p4', 'screw', 'red', 14.0, 'london'),
('p5', 'cam', 'blue', 12.0, 'paris'),
('p6', 'cog', 'red', 19.0, 'london');


insert into SP values 
('s1', 'p1', 300), 
('s1', 'p2', 200),
('s1', 'p3', 400),
('s1', 'p4', 200),
('s1', 'p5', 100),
('s1', 'p6', 100),
('s2', 'p1', 300),
('s3', 'p2', 400),
('s3', 'p2', 200),
('s4', 'p2', 200),
('s4', 'p4', 300),
('s4', 'p5', 400);

select sx.sname 
from s sx 
where exists(select * from sp spx 
where exists(select * from sp spy 
where sx.snum = spx.snum 
and spx.pnum = spy.pnum 
and spy.snum = 's2'));