#include <stdio.h>
#include <stdlib.h>

#include "Date.h"


#define FILE_NAME "date.bin"

void main()
{
	Date origDate = { 7, 2, 2010 }, newDate;

	if(!saveDateToFile(FILE_NAME, &origDate))
		return;

	if (!readDateFromFile(FILE_NAME, &newDate))
		return;

	printf("\nThe read date is %d/%d/%d\n",
		newDate.day, newDate.month, newDate.year);
	
	system("pause");
}
