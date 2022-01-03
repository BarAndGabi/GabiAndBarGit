#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "exe.h"


int main()
{
	if(!Q1())
		printf("Error in Question1\n");

	getchar(); //clean the buffer

	if(!Q2())
			printf("Error in Question2\n");
	system("pause");
}
