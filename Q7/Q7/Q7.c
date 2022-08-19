#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int maxInt(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}
void maxStringPolindrom(char *array, int n)
{
	int start = 0, end = 1;
	int currentLength = 2;
	int *table = (int *)calloc(n * n, sizeof(int));
	for (size_t i = 0; i < n; i++)
	{
		table[i * n + i] = 1;
	}
	for (currentLength = 2; currentLength <= n; currentLength++)
	{
		for (start = 0; start < n - currentLength + 1; start++)
		{
			end = start + currentLength - 1;
			if (array[start] == array[end] && currentLength == 2)
				table[start * n + end] = 2;
			else if (array[start] == array[end])
				table[start * n + end] = table[(start + 1) * n + end - 1] + 2;
			else
				table[start * n + end] = maxInt(table[start * n + end - 1], table[(start + 1) * n + end]);
		}
	}
	// PRINT
	printf("\nEND->        ");
	for (start = 0; start < n; start++)
		printf("%d      ", start);
	printf("\nSTARTvv\n");
	printf("__________________________________________________________________________\n");
	for (start = 0; start < n; start++)
	{
		printf("[%d]\t", start);
		for (end = 0; end < n; end++)
			printf("%6d ", table[start * n + end]);
		printf("\n\n");
	}
	printf("\nnum of elements in the longest palindrom: %d\n", table[n - 1]);

	char *palind = (char *)malloc(sizeof(char *) * (table[n - 1] + 1));
	palind[table[n - 1]] = '\0';
	int palindIndex = 0;
	end = n - 1;
	start = 0;
	while (end >= 0 && start < n && table[start * n + end] != 0)
	{
		if (table[start * n + end] == table[start * n + end - 1]) // take
		{
			end--;
		}
		else if (table[start * n + end] == table[(start + 1) * n + end])
		{
			start++;
		}
		else
		{
			palind[palindIndex] = array[start];
			palind[table[n - 1] - 1 - palindIndex] = array[start];
			palindIndex++;
			end--;
			start++;
		}
	}

	printf("\nthe longest palindom in the string: %s\n-----------------------------------------------------\n", palind);
	free(palind);
	free(table);
}

int main()
{
	int length = 4;
	char *str = (char *)malloc(sizeof(char *) * length);
	;
	strcpy(str, "1421");
	maxStringPolindrom(str, length);

	length = 5;
	strcpy(str, "13221");
	maxStringPolindrom(str, length);

	free(str);
	system("pause");
	return 0;
}