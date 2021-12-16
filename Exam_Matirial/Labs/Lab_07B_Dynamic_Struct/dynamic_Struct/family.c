#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "family.h"


int initFamily(Family* theFamily)
{
	theFamily->name = createDynStr("family name");
	if(!theFamily->name) //allocation did not work
		return 0;
	printf("Enter number of people: ");
	scanf("%d", &(theFamily->numOfPeople));
	return 1;
}

void printFamily(const Family* theFamily)
{
	printf("Family %s has %d peoples\n", 
			theFamily->name, theFamily->numOfPeople);
}

void freeFamily(Family* theFamily)
{
	free(theFamily->name);
}

char*	createDynStr(const char* msg)
{
	char* str;
	char temp[100];
	printf("Enter %s: ",msg);
	scanf("%s",temp);

	str = (char*)malloc((strlen(temp)+1)*sizeof(char));
	if (!str)
		return NULL;
	strcpy(str, temp);

	return str;
}






