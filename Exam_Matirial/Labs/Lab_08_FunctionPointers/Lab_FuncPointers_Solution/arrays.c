#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "arrays.h"
 


void	initArray(int* arr,int size)
{
	printf("Please enter %d numbers\n",size);
	for (int i=0; i<size; i++,arr++)
		scanf("%d",arr);
}


void	printArray(const int* arr,int size)
{
	for (int i=0; i<size; i++,arr++)
		printf("%5d",*arr);
	printf("\n");

}
