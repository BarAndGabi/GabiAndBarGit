#include <stdio.h>
#include "student.h"

#include "lunch.h"

void initStudent(Student*  s)
{
	printf("Enter name of student and average:\n");
	scanf("%s %f", s->name, &s->average);
	initDate(&s->birthday);
	s->pLunch = NULL; //no lunch yet
}

void printStudent(const Student*  s)
{
	printf("Name: %s, Average: %.2f, DOB: ",
		s->name, s->average);
	printDate(&(s->birthday), '-');
	printf("\t");
	if (s->pLunch == NULL)
		printf("No lunch today\n");
	else
		printLunch(s->pLunch);
	printf("\n");
}

void setLunch(Student* s, Lunch* pLunch)
{
	s->pLunch = pLunch;
}

