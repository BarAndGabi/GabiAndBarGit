#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "employee.h"
#include "arrays.h"

void Q1();
int Q2();
void Q3();

void main()
{
	Q1();
	Q2();
	Q3();
	system("pause");
}

void Q1()
{
	char str[] = "hello world";

	printf("The Ascii sum is %u \n", sum(str, getAsciiSum));

	printf("The str length us %u\n", sum(str, strlen));

}

int Q2()
{
	int newSize;
	int* newArr;

	int arr[] = { 2,3,4,-7,9,-6,5,1 };
	int size = sizeof(arr) / sizeof(int);

	printf("The array is:\t");
	printArray(arr, size);

	printf("Which array to you want to create?\n");
	printf("1 - Odd, 2 - Positive 3 - divide by 3\n");
	int option;
	scanf("%d", &option);
	char msg[20];

	int(*rule)(int) = NULL;
	switch (option)
	{
		case 1:
			rule = isOdd;
			strcpy(msg, "Odd");
			break;
		case 2:
			rule = isPositive;
			strcpy(msg, "Positive");
			break;
		case 3:
			strcpy(msg, "Devide By 3");
			rule = isDevideBy3;
			break;

		default:
			printf("Error\n");
			break;
	}
	
	if (rule == NULL)
		return 0;

	
	newArr = createArrayByRule(arr, size, &newSize, rule);
	if (newSize > 0)
	{
		if (!newArr)
			printf("Error\n");
		else {
			printf("The %d %s numbers are: ", newSize, msg);
			printArray(newArr, newSize);
			free(newArr);
		}
	}
	else
		printf("No %s in array\n",msg);
	
	return 1;

}


void Q3()
{
	Employee arr[] = {
		{ "aaa", 10000, 4.5F }, { "bbb", 9000, 5.1F }, { "ccc", 11000, 3.3F },
		{ "ddd", 15000, 7.0F }, { "eee", 7000, 3.2F } };

	int size = sizeof(arr) / sizeof(Employee);

	printf("\n\n");

	qsort(arr, size, sizeof(Employee), compareEmployeesBySalary);
	printf("\nSort by salary\n");
	printEmployeeArr(arr, size);
	printf("\n\n");

	qsort(arr, size, sizeof(Employee), compareEmployeesBySeniority);
	printf("\nSort by seniority\n");
	printEmployeeArr(arr, size);

	printf("\n\n");

	
	qsort(arr, size, sizeof(Employee), compareEmployeesByName);
	printf("\nSort by name\n");
	printEmployeeArr(arr, size);
	printf("\n\n");

	Employee* pFound;

	Employee temp;
	printf("Enter a name to search\n");
	scanf("%s",temp.name);
	pFound = (Employee*)bsearch(&temp, arr, size, sizeof(Employee), compareEmployeesByName);

	if (pFound)
	{
		printf("Employee with name %s exists at index %d\n", temp.name, pFound-arr);
		printEmployee(pFound);
	}
	else
		printf("Employee with name %s doesn't exists\n",temp.name);

	strcpy(temp.name, "ddd");
	pFound = (Employee*)bsearch(&temp, arr, size, sizeof(Employee), compareEmployeesByName);

	if (pFound)
	{
		printf("Employee with name %s exists at index %d\n", temp.name, pFound - arr);
		printEmployee(pFound);
	}
	else
		printf("Employee with name %s doesn't exists\n", temp.name);
}