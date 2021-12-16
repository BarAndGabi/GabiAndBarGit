#include <stdio.h>
#include "date.h"

void initDate(Date*  d)
{
	printf("Please enter DOB: ");
	scanf("%d %d %d", &d->day, &d->month, &d->year);
}

void printDate(const Date *  d, char delimiter)
{
	printf("%d%c%d%c%d", d->day,
		delimiter, d->month, delimiter, d->year);
}


