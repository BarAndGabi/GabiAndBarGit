
#include <stdio.h>
#include "person.h"

#define MAX_PERSONS 1

int main()
{
	Person arr[MAX_PERSONS];
	initPersonArr(arr,MAX_PERSONS);
	printf("The persons are:\n");
	printPersonArr(arr,MAX_PERSONS);
	return 0;
}

