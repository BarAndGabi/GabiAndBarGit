#include <stdio.h>
#include <stdlib.h>

#include "list_Q1.h"

int main()
{
	int arr[] = { 2,4,3,5,6,7 };
	int arr2[] = { 7,8,9,6 };
	LIST lst1;
	L_init(&lst1);
	LIST lst2;
	L_init(&lst2);
	createListFromArr(&lst1, arr, sizeof(arr) / sizeof(arr[0]));
	L_print(&lst1);
	createListFromArr(&lst2, arr2, sizeof(arr2) / sizeof(arr2[0]));
	L_print(&lst2);
	L_printCIRCLE(combine_lists(&lst1.head, &lst2.head));
	system("pause");
}