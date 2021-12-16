#ifndef __MY_DATE__
#define __MY_DATE__



typedef unsigned char BYTE;

typedef struct
{
	unsigned int day;  //1->31
	unsigned int month;//1->12
	unsigned int year; //0 - 2047

}Date;

int saveDateToFile(const char* fileName, Date* pDate);
int readDateFromFile(const char* fileName, Date* pDate);



#endif