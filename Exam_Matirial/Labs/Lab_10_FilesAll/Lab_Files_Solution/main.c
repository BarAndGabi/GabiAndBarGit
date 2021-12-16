#include <stdlib.h>
#include <stdio.h>
#include "studentBinary.h"
#include "studentText.h"

#define TEXT_FILE "StudentsT.txt"
#define BIN_FILE "StudentsB.bin"

#define TEXT_TO_BIN

void TextToBin();
void BinToText();

void main()
{
#ifdef TEXT_TO_BIN
	TextToBin();
#else
	BinToText();
#endif
	
	
	system("pause");
}

void TextToBin()
{
	Student* arr;
	int count;

	arr = readStudentArrFromTextFile(TEXT_FILE, &count);
	if (!arr)
	{
		printf("Error in array\n");
		return;
	}
	showStudentArr(arr, count);

	if (!writeStudentArrToBFile(BIN_FILE, arr, count))
	{
		printf("Error in write to bin file\n");
		freeStudentArr(arr, count);
		return;
	}
//	addStudentToEndOfBFile(BIN_FILE);

	freeStudentArr(arr, count);

}

void BinToText()
{
	Student* arr;
	int count;

	arr = readStudentArrFromBFile(BIN_FILE, &count);
	if (!arr)
	{
		printf("Error in array\n");
		return;
	}

	showStudentArr(arr, count);

	if (!writeStudentArrToTextFile(TEXT_FILE, arr, count))
	{
		printf("Error in write to txt file\n");
		freeStudentArr(arr, count);
		return;
	}
//	addStudentToEndOfTextFile(TEXT_FILE);

	freeStudentArr(arr, count);
}