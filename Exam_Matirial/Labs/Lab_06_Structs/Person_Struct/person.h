#ifndef __PERSON__
#define __PERSON__

#include "Address.h"

typedef enum {Man, Woman, Boy, Girl, NofTypes } Type;
const char* typeTilte[NofTypes];
typedef struct
{
	char	name[LEN];
	Address	my_address;
	Type	theType;
} Person;


void	initPerson(Person* pPer);
Type	getTypeFromUser();
void	printPerson(const Person* pPer);

void	initPersonArr(Person* pArr,int size);
void	printPersonArr(const Person* pArr,int size);











#endif
