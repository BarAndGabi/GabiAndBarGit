#ifndef __STUDENT__
#define __STUDENT__

struct Lunch;
#include "date.h"

typedef struct
{
	char name[20];
	Date birthday;
	float average;
	struct lunch_t*	pLunch;
} Student;

void initStudent(Student* s);
void printStudent(const Student* s);
void setLunch(Student* s, struct lunch_t* pLunch);

#endif