#include <stdio.h>
#define SIZE 3
void main()
{
	int a1[SIZE][SIZE] = { {0,1,1},{1,1,1},{0,1,0} };
	int a2[SIZE][SIZE] = { {1,1,0},{1,1,1},{0,1,0} };
	if (!Init(SIZE, a1))
		printf("error");
	if(!(Flip(a1, 1, 1)))
		printf("error");

	int result = DNF(a2);
	printf("%d", result);

	system("pause");
}

int Init(int size, int A[SIZE][SIZE])
{
	for (int row = 0; row < size; row++)
		for (int col = 0; col < SIZE; col++)
			A[row][col] = 1;
	return 1;

}

int Flip(int a[SIZE][SIZE], int row, int col)
{
	if (a[row][col] == 0)
	{
		a[row][col] = 1;
		return 1;
	}
	else
	{
		a[row][col] = 0;
		return 1;
	}
	return 0;
}

int DNF(int a[SIZE][SIZE])
{
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = 0; col < SIZE; col++)
		{
			if (a[row][col] == 0)
				break;
			else if (col == SIZE - 1)
				return 1;
		}
	}
	return 0;
}