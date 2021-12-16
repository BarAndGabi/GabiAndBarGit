#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "Q.h"

void Q1();
void Q2();
void Q3();
void Q4();
void Q5();


int main()
{
	printf("\n---------  Q1 -------------\n");
	Q1();
	printf("\n---------  Q2 -------------\n");
	Q2();
	printf("\n---------  Q3 -------------");
	Q3();
	printf("\n---------  Q4 -------------\n");
	Q4();
	printf("\n---------  Q5 -------------\n");
	Q5();
	system("pause");
}


void Q1()
{
	int arr[] = { 6,50,2,16,7,-9,11 };
	LIST lst;
	NODE* pNode;
	L_init(&lst);

	createListFromArr(&lst, arr, sizeof(arr)/sizeof(arr[0]));
	L_print(&lst);

	pNode = lst.head.next;
	int	 max = findMax(pNode);
	printf("Max of list :%d\n", max);

	L_free(&lst);
}

void Q2()
{
	int arr[] = { 6,6,50,50,50,2,16,7,-9,11,11,11 };
	LIST lst;
	NODE* pNode;

	L_init(&lst);

	createListFromArr(&lst, arr, sizeof(arr) / sizeof(arr[0]));
	L_print(&lst);

	pNode = lst.head.next;
	removeDuplicates(pNode);
	printf("After remove duplicates\n");
	L_print(&lst);

	L_free(&lst);

}

void Q3()
{
	LIST	lst;
	int arr[] = { 4,5,7,-6 };
	int size = sizeof(arr) / sizeof(int);
	int num = 20;

	L_init(&lst);
	createListFromArr(&lst, arr, size);
	// Print
	L_print(&lst);

	insertToNum(&lst, num);
	//4  -->  16  -->  5 --> 15 --> 7 --> 13 --> -6 --> 26
	printf("After indert to num %d\n", num);
	L_print(&lst);
	L_free(&lst);
}


void Q4()
{
	LIST	lst;
	int arr[] = { 4,5,7,4,1,4,7,-6,4 };
	int size = sizeof(arr) / sizeof(int);
	int num = 4;

	L_init(&lst);
	createListFromArr(&lst, arr, size);
	// Print
	L_print(&lst);

	removeValFromList(&lst, num);
	
	printf("After remove num %d\n", num);
	L_print(&lst);
	L_free(&lst);
}


void Q5()
{
	LIST	lst;
	int arr[] = { 14,5,7,4,1,4,-6,15 };
	int size = sizeof(arr) / sizeof(int);
	int num = 4;

	L_init(&lst);
	createListFromArr(&lst, arr, size);
	// Print
	L_print(&lst);

	removeNMaxFromList(&lst, num);

	printf("After remove %d maxs\n", num);
	L_print(&lst);
	L_free(&lst);



}

