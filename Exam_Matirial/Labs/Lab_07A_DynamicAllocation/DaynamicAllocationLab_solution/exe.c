#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exe.h"
#include "functions.h"
#include "arrays.h"


int Q1()
{
	int size,newSize;
	int* startArr;
	int* newArr;

	do{
		printf("Enter size of array: ");
		scanf("%d", &size);
	}while(size <=0);

	startArr = (int*)malloc(size*sizeof(int));
	if(!startArr)
		return 0;

	initArray(startArr,size);
	printf("The array is:\t");
	printArray(startArr,size);

	
	newArr = getEvenNumbers(startArr, size, &newSize);

	if(	newSize > 0)
	{
		if (!newArr)
			printf("Error\n");
		else {
			printf("The %d even numbers are: ", newSize);
			printArray(newArr, newSize);
			free(newArr);
		}
	} else
		printf("No evens in array\n");

	//Check second function
	newArr = getEvenNumbers_OnePass(startArr, size, &newSize);

	if (newSize > 0)
	{
		if (!newArr)
			printf("Error\n");
		else {
			printf("The %d even numbers are: ", newSize);
			printArray(newArr, newSize);
			free(newArr);
		}
	}
	else
		printf("No evens in array\n");

	free(startArr);

	return 1;
}

int	Q2()
{
	 char* longStr = createCombineStrings();

	if (longStr)
	{
		puts(longStr);
		free(longStr);
		return 1;
	}
	return 0;
}
