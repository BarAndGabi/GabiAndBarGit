#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"



void filter(int arr[], int size, int(*foo)(int))
{
	int i;
	for (i = 0; i < size; i++)
		if (foo(arr[i]) == 1)
			printf("%d ", arr[i]);
}

int isOdd(int x)
{
	//return x % 2 != 0; 
	if (x % 2 == 0)
		return 0;
	return 1;
}
int isPositive(int x) { return x > 0; }


void printArr(const void* arr, int size, int typeSize, void(*print)(const void*))
{
	int i;
	for (i = 0; i < size; i++)
		print((char*)arr + i*typeSize);
	printf("\n");
}


void swap(void* a, void* b, int typeSize)
{
	int i;
	char temp;
	char* first = (char*)a;
	char* second = (char*)b;

	for (i = 0; i < typeSize; i++)
	{
		temp = *(first + i);
		*(first + i) = *(second + i);
		*(second + i) = temp;
	}
}

void sort(void* arr, int size, int typeSize, int(*compare)(const void*,const void*))
{
	int i, j;

	for (i = size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (compare((char*)arr + j*typeSize, (char*)arr + (j + 1)*typeSize) > 0)
				swap((char*)arr + j*typeSize, (char*)arr + (j + 1)*typeSize, typeSize);
}


