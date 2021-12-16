#include <stdio.h>
#include "ints.h"

void printInt(const void* num)
{
	int n = *(int*)num;
	printf("%d ", n);
}



int compareInt(const void* num1, const void* num2)
{
	int n1 = *((int*)num1);
	int n2 = *((int*)num2);
	return n1 - n2;
}
