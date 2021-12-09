#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define SIZE 6


SimpleCheck(int A[], int start, int  end)
{
	if (A[end] - A[start] < end - start)
		return 1; 
	else 
		return 0;
}

SolveB(int A[], int start,int  end)
{
	if (start+1 == end)
		return A[start] + 1;
	int middle = (start + end) /2;
	if (SimpleCheck(A, start, middle) == 1)
		return SolveB(A, start, middle);
	else
		return SolveB(A, middle, end);
}




SolveC(int A[],int  start,int  end)
{
	if (end < start)
		return 0;
	int m = (end + start) / 2;
	if (A[m] = m)
		return 1;
	if (A[m] > m)
		return SolveC(A, start, m - 1);
	else
		return SolveC(A, m + 1, end);
}

void initArray(int *arr, int size)
{
	int i;
	printf("Please enter %d elements for array\n", size);
	for (i = 0; i < size; i++)
	{
		scanf("%d", arr);
		arr++;
	}
}
void printArray(const int *arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%5d", *arr);
		arr++;
	}

	printf("\n");
}
int main()
{
	int A[SIZE];
	initArray(A, SIZE);
	printArray(A, SIZE);
	int choise = 0;
	printf("enter 1 if you want a,b and 2 if you want c else program exit");
	scanf("%d", &choise); 
	
	switch (choise)
	{
	case 1://a,b
		if (SimpleCheck(A, 0, SIZE) == 1)
		{

		}
		else
		{

		}
			
		break;
	case 2://c
		if (SolveC(A, 0, SIZE - 1))
			printf("\nthere is a A[i]=i \n");
		else
			printf("\nthere is no  a A[i]=i \n");


		break;
	default:
		break;

	}
	system("pause");

}