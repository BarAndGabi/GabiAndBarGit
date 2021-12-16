#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Date.h"



int saveDateToFile(const char* fileName, Date* pDate)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (!fp)
		return 0;

	BYTE data[3];
	data[0] = pDate->year >> 7;
	data[1] = (pDate->month >> 3) | (pDate->year << 1);
	data[2] = pDate->day | (pDate->month << 5);


	if (fwrite(data, sizeof(BYTE), 3, fp) != 3)
	{
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}

int readDateFromFile(const char* fileName, Date* pDate)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
		return 0;

	BYTE data[3];
	if (fread(data, sizeof(char), 3, fp) != 3)
	{
		fclose(fp);
		return 0;
	}

	pDate->year = (data[1] >> 1) | ((data[0] & 0xF) << 7);
	pDate->month =  (data[2] >> 5) | ((data[1] & 0x1) << 3);
	pDate->day = data[2] & 0x1F;
	
	fclose(fp);

	return 1;
}