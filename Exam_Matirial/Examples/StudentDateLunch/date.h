#ifndef __MYDATE__
#define __MYDATE__

typedef struct
{
	int day, month, year;
} Date;

void initDate(Date*  d);
void printDate(const Date*  d, char delimiter);

#endif