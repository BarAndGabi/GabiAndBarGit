create schema college_2020_ver_21_a;
use college_2020_ver_21_a;

CREATE TABLE Departments
(DEPART			char(25) NOT NULL,
D_NAME			char(25),
HEAD			char(25),
PRIMARY KEY		(DEPART)

)ENGINE = InnoDB;

CREATE TABLE Courses
(COURSE_ID		char(25) NOT NULL,
COURSE_NAME		char(25),
TYPE			char(25),
POINTS			float,
DEPARTMENT_ID	char(25),
PRIMARY KEY		(COURSE_ID),
CONSTRAINT fk_dep
FOREIGN KEY (DEPARTMENT_ID) REFERENCES Departments(DEPART)
)ENGINE = InnoDB;

CREATE TABLE Students
(STUDENT_ID		float NOT NULL,
S_NAME			char(25),
CITY			char(25),
PRIMARY KEY (STUDENT_ID)
) ENGINE = InnoDB;

CREATE TABLE Grades
(STUDENT_ID		float NOT NULL,
COURSE_ID		char(25) NOT NULL,
SEMESTER 		char(25),
TERM			char(25),
GRADE			smallint,
GRADE_SEM		smallint,
PRIMARY KEY (STUDENT_ID, COURSE_ID),
CONSTRAINT fk_student
FOREIGN KEY (STUDENT_ID) REFERENCES Students(STUDENT_ID),
CONSTRAINT fk_course
FOREIGN KEY (COURSE_ID) REFERENCES Courses(COURSE_ID)
)ENGINE = InnoDB;

INSERT INTO Departments VALUES
('BS','Buisnes','Dr.Eyal'),
('CH','Chemistry','Prof.Doron'),
('CS','Computer Science','Dr.Israel'),
('MT','Mathematics','Prof.Levi');

INSERT INTO Courses VALUES
('B-10','Marketing','CLASS',5,'BS'),
('B-40','Operations Res.','SEMIN',3,'BS'),
('C-200','Programing','LAB',4,'CS'),
('C-300','Pascal','LAB',4,'CS'),
('C-55','Data Base','CLASS',3,'CS'),
('M-100','Linear Algebra','CLASS',3,'MT'),
('M-200','Numeric Analyses','CLASS',3,'MT');

INSERT INTO Students VALUES
(105,'Moshe','Haifa'),
(107,'Eyal','Tel Aviv'),
(110,'Ran','Haifa'),
(200,'David','Tel Aviv'),
(210,'Dan','Tel Aviv'),
(240,'Ayelet','Tel Aviv'),
(245,'Yoel','Haifa'),
(310,'Tova','Jerusalem');

INSERT INTO Grades VALUES
(105,'B-40','WIN1999','B',70,70),
(105,'C-200','AUT1999','A',90,85),
(105,'C-55','SUM1998','A',58,70),
(105,'M-100','SUM1998','B',75,50),
(200,'B-10','AUT1999','A',70,65),
(200,'C-200','AUT1999','B',78,50),
(200,'M-100','SUM1998','B',90,90),
(210,'B-10','WIN1999','A',78,50),
(210,'C-200','AUT1999','A',85,80),
(210,'M-100','AUT1999','A',90,90),
(245,'B-10','AUT1999','A',80,70),
(245,'B-40','WIN1998','A',85,95),
(245,'M-100','AUT1999','A',90,80),
(310,'M-100','SUM1998','A',65,100);