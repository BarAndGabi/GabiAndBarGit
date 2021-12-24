#include <stdio.h>
#include <stdlib.h>
#include "Q2_C.h"
int main()
{
	int vec[] = { 0,3,5,7,8,-1 };
	int arr[] = { 2,4,6,9,1,3,5,7 };
	LIST ls;
	L_init(&ls);
	int len = sizeof(arr)/sizeof(arr[0]);
	createListFromArr(&ls, arr, len);
	printf("List before func:\n");
	L_print(&ls);
	printf("List after:\n");
	if ((del_fun(&ls.head, vec)) == NULL)
		printf("all is deleted\n");
	L_print(&ls);
	system("pause");
	return 1;
}