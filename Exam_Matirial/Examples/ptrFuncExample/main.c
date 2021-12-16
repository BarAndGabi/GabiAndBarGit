#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"
#include "ints.h"
#include "general.h"


#define SIZE 4

void Q1();
void Q2();
void Q3();
void Q4();
void Q5();

void main()
{
	printf("\n ---------   Q1 -----------------\n");
	Q1();
	printf("\n ---------   Q2 -----------------\n");
	Q2();
	printf("\n ---------   Q3 -----------------\n");
	Q3();
	printf("\n ---------   Q4 -----------------\n");
	Q4();
	printf("\n ---------   Q5 -----------------\n");
	Q5();
	system("pause");
}

void Q1()
{
	int arr[] = { -3, 6, -2, 8, 1, -4 };
	int size = sizeof(arr) / sizeof(arr[0]);

	printf("All odd numbers are: \n");
	filter(arr, size, isOdd);

	printf("\nAll positive numbers are : \n ");
	filter(arr, size, isPositive);
}

void Q2()
{
	int numbers[SIZE] = { 4,2,-3, 1 };
	Person persons[SIZE] = { { 333, "gogo" },{ 111, "yoyo" },
	{ 444, "momo" },{ 222, "koko" } };

	printf("The arrays are: ");
	printArr(numbers, SIZE, sizeof(int), printInt);
	printArr(persons, SIZE, sizeof(Person), printPerson);
}

void Q3()
{
	int numbers[SIZE] = { 4,2,-3, 1 };
	Person persons[SIZE] = { { 333, "gogo" },{ 111, "yoyo" },
				{ 444, "momo" },{ 222, "koko" } };

	printf("The sorted numbers are: ");
	sort(numbers, SIZE, sizeof(int), compareInt);
	printArr(numbers, SIZE, sizeof(int), printInt);

	printf("\nThe persons by ID are:\n");
	sort(persons, SIZE, sizeof(Person), comparePersonById);
	printArr(persons, SIZE, sizeof(Person), printPerson);

	printf("\nThe persons by names are:\n");
	sort(persons, SIZE, sizeof(Person), comparePersonByName);
	printArr(persons, SIZE, sizeof(Person), printPerson);
}

//Same as Q3 - using qsort and bsearch
void Q4()
{
	int numbers[SIZE] = { 4,2,-3, 1 };
	Person persons[SIZE] = { { 333, "gogo" },{ 111, "yoyo" },
				{ 444, "momo" },{ 222, "koko" } };


	printf("The sorted numbers are: ");
	qsort(numbers, SIZE, sizeof(int), compareInt);
	printArr(numbers, SIZE, sizeof(int), printInt);

	printf("enter number to check\t");
	int check;
	scanf("%d", &check);
	int* found = (int*)bsearch(&check, numbers, SIZE, sizeof(int), compareInt);
	if (!found)
		printf("%d was not found in array\n", check);
	else
		printf("%d was found in index %d\n", check, (int)(found - numbers));


	printf("\nThe persons by ID are:\n");
	qsort(persons, SIZE, sizeof(Person), comparePersonById);
	printArr(persons, SIZE, sizeof(Person), printPerson);

	Person temp;
	printf("enter person ID to check\t");
	scanf("%d", &temp.id);

	Person* foundPerson = (Person*)bsearch(&temp, persons, SIZE, sizeof(Person), comparePersonById);
	if (!foundPerson)
		printf("ID: %d was not found in array\n", temp.id);
	else {
		printf("ID: %d was found in index %d\n", temp.id, (int)(foundPerson - persons));
		printPerson(foundPerson);
	}

	printf("\nThe persons by names are:\n");
	sort(persons, SIZE, sizeof(Person), comparePersonByName);
	printArr(persons, SIZE, sizeof(Person), printPerson);

	printf("enter person name to check\t");
	scanf("%s", temp.name);
	foundPerson = (Person*)bsearch(&temp, persons, SIZE, sizeof(Person), comparePersonByName);
	if (!foundPerson)
		printf("ID: %s was not found in array\n", temp.name);
	else {
		printf("ID: %s was found in index %d\n", temp.name, (int)(foundPerson - persons));
		printPerson(foundPerson);
	}
}



//Same as Q4 - Peron**
void Q5()
{
	Person* persons[SIZE];
	
	for (int i = 0; i < SIZE; i++)
	{
		persons[i] = (Person*)malloc(sizeof(Person));
		printf("enter person name and id\n");
		scanf("%s %d", persons[i]->name, &persons[i]->id);
	}
	
	printf("\nThe persons by ID are:\n");
	qsort(persons, SIZE, sizeof(Person*), comparePersonPtrById);
	printArr(persons, SIZE, sizeof(Person*), printPersonPtr);

	Person temp;
	Person* pTemp = &temp;
	printf("enter person ID to check\t");
	scanf("%d", &temp.id);
	
	Person** foundPerson = (Person**)bsearch(&pTemp, persons, SIZE, sizeof(Person*), comparePersonPtrById);
	if (!foundPerson)
		printf("ID: %d was not found in array\n", temp.id);
	else{
		printf("ID: %d was found in index %d\n", temp.id, (int)(foundPerson - persons));
		printPerson(*foundPerson);
	}


	printf("\nThe persons by names are:\n");
	sort(persons, SIZE, sizeof(Person*), comparePersonPtrByName);
	printArr(persons, SIZE, sizeof(Person*), printPersonPtr);

	printf("enter person name to check\t");
	scanf("%s", temp.name);
	foundPerson = (Person**)bsearch(&pTemp, persons, SIZE, sizeof(Person*), comparePersonPtrByName);
	if (!foundPerson)
		printf("ID: %s was not found in array\n", temp.name);
	else {
		printf("ID: %s was found in index %d\n", temp.name, (int)(foundPerson - persons));
		printPerson(*foundPerson);
	}

	for (int i = 0; i < SIZE; i++)
		free(persons[i]);

}


