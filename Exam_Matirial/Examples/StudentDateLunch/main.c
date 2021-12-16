#include <stdlib.h>
#include "student.h"
#include "lunch.h"

int main()
{
	Student s;
	initStudent(&s);
	printStudent(&s);

	Lunch l1;
	initLunch(&l1);
	setLunch(&s,&l1);
	printStudent(&s);
	system("pause");
}
