#include <stdio.h>
#include <ctype.h>
#include "functionsLab2.h" 


int checkArray(int arr[], int size)
{
	int i;

	for (i = 1; i < size; i++)
	{
		if (arr[i] <= arr[i - 1])
			return 0;
	}
	return 1;
}

 
int countCharInMat(char mat[][COLS], int rows, int cols, char tav)
{
	int i, j;
	int count = 0;
	if (cols > COLS)
		cols = COLS;

	char lowerTav = tolower(tav);
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (tolower(mat[i][j]) == lowerTav)
				count++;
		}
	}
	return count;
}
