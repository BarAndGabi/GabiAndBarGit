#pragma once


#define SIZE 20


typedef  struct
{
	char name[SIZE];
	long id;
	float age;
} Person;


typedef  struct
{
	char* name;
	long id;
	float age;
} Person_p;



void example1();
void example2();
void example3();
void example4();


void initPerson(Person_p* pPer);