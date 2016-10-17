create database SPdb;
use SPdb

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
/* 
8.3.1 
get supplier numbers and status 
for suppliers 
in paris with status > 20
*/
select sx.snum, sx.status 
from s sx
where sx.city = 'paris' 
and sx.status > 20
;

/*
8.3.2 
Get all pairs of supplier numbers 
such that the two suppliers are located in the same city
*/
select sx.snum as first_num, sy.snum as second_num
from s sx, s sy 
where 	sx.city = sy.city 
	and sx.snum < sy.snum;

/*
8.3.3
Get supplier names for suppliers 
who supply part p2
*/
select sname 
from s sx
where exists (
select * from sp spx
where spx.snum = sx.snum
and	spx.pnum = 'p2'
);

/*
8.3.4
Get supplier names for suppliers 
who supply at least one red part
*/
select sx.sname 
from s sx
where exists(
	select * from sp spx
	where sx.snum = spx.snum 
	and exists (
			select * from p px 
			where px.pnum = spx.pnum 
			and px.color = 'red'
		)
);


/* 
8.3.5 
get supplier names for suppliers
who supply at least one part 
supplied by supplier s2
*/
select sx.sname 
from s sx 
where exists(select * from sp spx 
where exists(select * from sp spy 
where sx.snum = spx.snum 
and spx.pnum = spy.pnum 
and spy.snum = 's2'));