#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyMacros.h"
#include "Student.h"

static const char* DegreeStr[eNofTypes] = { "First", "Second" };



Student* createStudentArrFromFile(const char* fileName, int* pSize)
{
	FILE* fp;
	Student* arr;

	fp = fopen(fileName, "rb");

	CHECK_RETURN_0(fp);

	BYTE count;
	if (fread(&count, sizeof(BYTE), 1, fp) != 1)
	{
		fclose(fp);
		return 0;
	}
	*pSize = (int)count;


	arr = (Student*)malloc(*pSize * sizeof(Student));
	CHECK_NULL_CLOSE_FILE_0(arr, fp);

	for (int i = 0; i < *pSize; i++)
	{
		if (!readStudentFromBinaryFileCompressed(&arr[i], fp))
		{
			free(arr);
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	return arr;
}

int		saveStudentArrToBinaryFile(const char* fileName, const Student* arr, int size)
{
	FILE* fp;

	fp = fopen(fileName, "wb");
	CHECK_RETURN_0(fp);

	BYTE count = (BYTE)size;
	if (fwrite(&count, sizeof(BYTE), 1, fp) != 1)
	{
		fclose(fp);
		return 0;
	}


	for (int i = 0; i < size; i++)
	{
		if (!saveStudentToBinaryFileCompressed(&arr[i], fp))
		{
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	return 1;
}



int		saveStudentToBinaryFileCompressed(const Student* pSt, FILE* fp)
{
	BYTE data[2] = { 0 };
	
	int len = (int)strlen(pSt->name);
	data[0] = len << 3 | pSt->type << 2;
	data[0] = data[0] | pSt->year >> 1;


	data[1] = ((pSt->year) & 0x1) << 7;
	data[1] = data[1] | pSt->grade;
	
	
	if (fwrite(&data, sizeof(BYTE), 2, fp) != 2)
		return 0;

	if (fwrite(pSt->name, sizeof(char), len, fp) != len)
		return 0;

	return 1;
}

int		readStudentFromBinaryFileCompressed(Student* pSt, FILE* fp)
{
	BYTE data[2];
	if (fread(&data, sizeof(BYTE), 2, fp) != 2)
		return 0;

	int len = (data[0] >> 3) & 0x1F;
	pSt->type = (data[0] >> 2) & 0x1; 
	pSt->year = ((data[0] & 0x3) << 1) | ((data[1] >> 7) & 0x1);
	pSt->grade = data[1] & 0x7F;

	pSt->name = (char*)calloc(len + 1, sizeof(char));
	if (!pSt->name)
		return 0;

	if (fread(pSt->name, sizeof(char), len, fp) != len)
	{
		free(pSt->name);
		return 0;
	}

	return 1;
}

void	initStudentArr(Student* arr, int size)
{
	for (int i = 0; i < size; i++)
		initStudent(&arr[i]);
}

void	showStudentArr(const Student* arr, int size)
{
	for (int i = 0; i < size; i++)
		showStudent(&arr[i]);
}

void	freeStudentArr(Student* arr, int size)
{
	for (int i = 0; i < size; i++)
		free(arr[i].name);
}

void	showStudent(const Student* pSt)
{
	printf("Name: %s Type: %s Year: %d Grade: %d\n", 
		pSt->name, DegreeStr[pSt->type],pSt->year, pSt->grade);
}

void	initStudent(Student* pSt)
{
	pSt->name = createDynStr("Enter student name");
	pSt->type = getStudentTypeFromUser();
	printf("enter student year and grade\n");
	scanf("%d %d", &pSt->year, &pSt->grade);
	getchar();
}


eDegreeType getStudentTypeFromUser()
{
	int temp;
	do {
		for (int i = 0; i < eNofTypes; i++)
			printf("enter %d for type %s\n", i, DegreeStr[i]);
		scanf("%d", &temp);
	} while (temp < 0 || temp >= eNofTypes);
	return (eDegreeType)temp;
}

char*	createDynStr(const char* msg)
{
	char* str;
	char temp[100];
	printf("Enter %s: ", msg);
	fgets(temp,sizeof(temp),stdin);
	temp[strcspn(temp, "\n")] = '\0';
	str = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	if (!str)
		return NULL;
	strcpy(str, temp);

	return str;
}

