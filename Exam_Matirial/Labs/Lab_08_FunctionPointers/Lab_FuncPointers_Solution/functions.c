#include "functions.h"

size_t getAsciiSum(const char* str)
{
	int sum = 0;
	while (*str)
	{
		sum += *str;
		str++;
	}

	return sum;
}

size_t sum(const char* str, size_t(*getSum)(const char* str))
{
	return getSum(str);
}

int* createArrayByRule(const int* arr, int size, int* newSize,int (*rule)(int))
{
	int* newArr = NULL;
	int i;
	int count = 0, index;

	//Pass 1 - find how many evens
	for (i = 0; i < size; i++)
	{
		if (rule(arr[i]) == 1) //same as if (rule(arr[i]))
			count++;
	}
	*newSize = count;
	if (count == 0) //no evens!!!
		return NULL;

	//create the new array in the correct size
	newArr = (int*)malloc(count * sizeof(int));
	if (!newArr)			//if(newArr == NULL)
		return NULL;

	//Pass 2 - copy the evens
	index = 0;
	for (i = 0; i < size; i++)
	{
		if (rule(arr[i]))
		{
			newArr[index] = arr[i];
			index++;
		}
	}

	return newArr;
}

int isOdd(int val)
{
	return (val % 2);
}

int isPositive(int val)
{
	if (val > 0)
		return 1;
	return 0;
}

int isDevideBy3(int val)
{
	if (val % 3 == 0)
		return 1;
	return 0;
}



