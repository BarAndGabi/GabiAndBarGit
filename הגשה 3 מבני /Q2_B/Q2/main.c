#include <stdio.h>
#include <stdlib.h>

#include "list_Q2.h"

int main()
{
	int temp1[] = { 1,2,3 };
	int temp2[] = { 4,5,6,7,8};

	LIST ls1,ls2;
	L_init(&ls1);
	createListFromArr(&ls1, temp1, 3);
	L_init(&ls2);
	L_print(&ls1);
	createListFromArr(&ls2, temp2, 5);
	L_print(&ls2);
	L_print(combine_lists(&ls1,&ls2));
	system("pause");
	return 1;
}