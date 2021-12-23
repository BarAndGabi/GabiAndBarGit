#include <stdio.h>
#include "list.h"

void Q1();
void Q2();
void createListFromArr(const int* arr,int size,LIST* pLst);

int main()
{
	printf("----------  Q1 ----------\n\n");
	Q1();
	printf("----------  Q2 ----------\n\n");
	Q2();
}


void Q1()
{
	LIST	lst;
	NODE	*ptr1, *ptr2;


	// Initialization
	L_init(&lst);

	//Operations on list
	L_insert(&(lst.head), 0);
	L_insert(&(lst.head), 2);
	ptr1 = L_insert(&(lst.head), 10);
	ptr2 = L_insert(ptr1, -5);
	L_insert(ptr2, 100);
	// Print
	printf("----------  Before delete----------\n\n");
	L_print(&lst);
	L_delete(lst.head.next);
	L_delete(ptr1);

	// Print
	printf("----------  After delete----------\n\n");
	L_print(&lst);

	// Finish work
	L_free(&lst);
}

void Q2()
{
	int arr[] = {1,2,3,4,5,6,7};
	int size = sizeof(arr)/sizeof(arr[0]);
	LIST lst;

	createListFromArr(arr,size,&lst);

	L_print(&lst);

	// Finish work
	L_free(&lst);
}

void createListFromArr(const int* arr,int size,LIST* pLst)
{
	L_init(pLst);
	NODE* pNode = &(pLst->head);
	for(int i = 0; i < size; i++)
		pNode = L_insert(pNode,arr[i]);
}












