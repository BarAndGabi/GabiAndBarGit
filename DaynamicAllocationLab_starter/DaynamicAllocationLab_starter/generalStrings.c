#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generalStrings.h"


char* getStrExactLength()
{
	char* theStr = NULL;
	size_t len;
	char inpStr[MAX_LENGTH]; //variable to hold the string that the user gives

	//Ask for a string from the user
	printf("Enter a String:");
	myGets(inpStr, sizeof(inpStr));

	//find string size and add 1 for the '\0'
	len = strlen(inpStr) + 1;
	//allocate a place for the string in the right location in the array 
	theStr = (char*)malloc(len * sizeof(char));
	//Copy the string to the right location in the array 
	if (theStr != NULL)
		strcpy(theStr, inpStr);

	//can use the strdup function replace line 20 to 25
	//theStr = strdup(inpStr);
	return theStr;
}

char* myGets(char* buf, int size)
{
	if (buf != NULL && size > 0)
	{
		if (fgets(buf, size, stdin))
		{
			buf[strcspn(buf, "\n")] = '\0';
			return buf;
		}
		*buf = '\0';
	}
	return NULL;

}
