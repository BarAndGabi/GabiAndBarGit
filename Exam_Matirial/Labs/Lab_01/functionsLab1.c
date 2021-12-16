#include <stdio.h>

#include "functionsLab1.h"


void printTriangle(int basis)
{
	int row, i,j,space;
	for (row = 1; row <= basis; row++)
	{
		space = basis - row;  
		for (j = 0; j < space; j++)
			printf(" ");
		for (i = 0; i < row; i++)
			printf("*");
		printf("\n");
	}
	printf("\n");
}

void helloWorld()
{

	printf("Hello World\n");

}
