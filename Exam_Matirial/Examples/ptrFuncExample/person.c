#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

void printPerson(const void* person)
{
	const Person* p = (const Person*)person;
	printf("Id: %d\tName: %s\n", p->id, p->name);
}

int comparePersonById(const void* person1, const void* person2)
{
	const Person* p1 = (const Person*)person1;
	const Person* p2 = (const Person*)person2;
	return p1->id - p2->id;
}

int comparePersonByName(const void* person1, const void* person2)
{
	const Person* p1 = (const Person*)person1;
	const Person* p2 = (const Person*)person2;
	return strcmp(p1->name, p2->name);
}


void printPersonPtr(const void* person)
{
	const Person* p = *(const Person**)person;
	printPerson(p);
}

int comparePersonPtrById(const void* person1, const void* person2)
{
	const Person* p1 = *(const Person**)person1;
	const Person* p2 = *(const Person**)person2;
	return p1->id - p2->id;
}

int comparePersonPtrByName(const void* person1, const void* person2)
{
	const Person* p1 = *(const Person**)person1;
	const Person* p2 = *(const Person**)person2;
	return strcmp(p1->name, p2->name);
}