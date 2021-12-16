#include <stdio.h>
#include <ctype.h>
#include "arrays.h"
 

void	printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%5d", arr[i]);

	printf("\n");
}

void	initArray(int arr[], int size)
{
	int i;
	printf("Please enter %d elemnts for array\n", size);
	for (i = 0; i < size; i++)
		scanf("%d", &arr[i]);
}
 

void	printMat(char mat[][COLS], int rows, int cols)
{
	int i, j;
	if (cols > COLS)
		cols = COLS;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			printf("%5c", mat[i][j]);
		printf("\n");
	}

}

void	initMat(char mat[][COLS], int rows, int cols)
{
	int i, j;
	char tav;

	if (cols > COLS)
		cols = COLS;
	
	printf("Please enter %d charecters to matrix\n", cols*rows);
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			do{
				scanf("%c", &tav);
			}while(isspace(tav));
			mat[i][j] = tav;
		}
	}
}

