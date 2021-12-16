#include <stdio.h>
#include "arrays.h"
 


void printArray(int* arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%5d",arr[i]);

	printf("\n");
}
