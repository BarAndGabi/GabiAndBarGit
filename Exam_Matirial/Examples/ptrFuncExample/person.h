#pragma once
typedef struct
{
	int id;
	char name[20];
}Person;


void printPerson(const void* person);
int comparePersonById(const void* person1, const void* person2);
int comparePersonByName(const void* person1, const void* person2);


void printPersonPtr(const void* person);
int comparePersonPtrById(const void* person1, const void* person2);
int comparePersonPtrByName(const void* person1, const void* person2);