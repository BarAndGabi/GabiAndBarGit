#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "generalStrings.h"

#define STOP_STR "Bye"

int* getEvenNumbers(const int* arr, int size, int* newSize)
{
	int* newArr = NULL;
	int i;
	int count = 0,index;

	//Pass 1 - find how many evens
	for (i=0; i < size ; i++)
	{
		if (arr[i]%2 == 0)
			count++;
	}
	*newSize = count;
	if (count == 0) //no evens!!!
		return NULL;

	//create the new array in the correct size
	newArr = (int*)malloc(count*sizeof(int));
	if (!newArr)			//if(newArr == NULL)
		return NULL;

	//Pass 2 - copy the evens
	index = 0;
	for (i=0; i < size ; i++)
	{
		if (arr[i]%2 == 0)
		{
			newArr[index] = arr[i];
			index++;
		}
	}

	return newArr;
}


int* getEvenNumbers_OnePass(const int* arr, int size, int* newSize)
{
	int* newArr = NULL;
	int i;
	int count = 0;

	for (i = 0; i < size; i++)
	{
		if (arr[i] % 2 == 0)
		{
			newArr = (int*)realloc(newArr, (count + 1) * sizeof(int));
			if (newArr == NULL)
				return NULL;
			newArr[count] = arr[i];
			count++;
		}
	}

	*newSize = count;
	return newArr;
}


char*	createCombineStrings()
{
	//Get strings and combine them into a dynamic string.
	char* longStr = NULL;
	char tempStr[MAX_LENGTH];

	size_t stringSize = 0, len;

	while (1)// infinite loop!!!!!!!! there must be a break command in the loop
	{
		printf("Please enter a string segment with at most %d characters. %s to exit\n", MAX_LENGTH - 1, STOP_STR);
		//We can input to temporary string
		myGets(tempStr, sizeof(tempStr));
		if (strcmp(tempStr, STOP_STR) == 0) // if tempStr is equal to Bye
			break;

		len = strlen(tempStr);

		if (longStr == NULL) //first time
		{
			longStr = (char*)malloc((len + 1) * sizeof(char));
			if (longStr == NULL) // error in allocation
				break;
			strcpy(longStr, tempStr);
		}
		else {
			stringSize = strlen(longStr) + len + 2; //1 for the $ , 1 for '\0'
			longStr = (char*)realloc(longStr, stringSize * sizeof(char));
			if (longStr == NULL) // error in allocation
				break;
			strcat(longStr, "$");
			strcat(longStr, tempStr);
		}
	}
	return longStr;
}





