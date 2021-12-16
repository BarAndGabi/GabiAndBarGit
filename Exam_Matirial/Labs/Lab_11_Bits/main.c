#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Student.h"


#define FILE_NAME_BIN "classInfo.bin"
#define N 5

void pauseFunc(void)
{
	system("pause");
}

int main()
{
	atexit(pauseFunc);

	Student baseArr[N];
	initStudentArr(baseArr, N);
	printf("\n\n------- Base student array --------------- \n");
	showStudentArr(baseArr, N);
	saveStudentArrToBinaryFile(FILE_NAME_BIN, baseArr,N);

	freeStudentArr(baseArr, N);

	int size;
	Student* arr = createStudentArrFromFile(FILE_NAME_BIN, &size);
	if (!arr)
	{
		printf("Error reading students\n");
		return 0;
	}

	printf("\n\n------- After loading form bianry file --------------- \n");
	showStudentArr(arr,size);
	freeStudentArr(arr, size);
	free(arr);
}
