#include <stdio.h>

#include "person.h"


const char* typeTilte[NofTypes] =  {"Man", "Woman", "Boy","Girl"};

void	initPerson(Person* pPer)
{
	printf("please enter person name\n");
	scanf("%s",pPer->name);
	pPer->theType = getTypeFromUser();
	initAddress(&pPer->my_address);
	getchar();
}

Type	getTypeFromUser()
{
	int i,t;
	printf("Enter person type\n");
	do {
		for(i=0; i < NofTypes; i++)
			printf("Enter %d for %s\n",i,typeTilte[i]);
		scanf("%d",&t);
	}while(t<0 || t>= NofTypes);
	return (Type)t;
}

void	printPerson(const Person* pPer)
{
	printf("%s name %s\n",typeTilte[pPer->theType],pPer->name);
	printf("Home address:");
	printAddress(&pPer->my_address);
}

void	initPersonArr(Person* pArr,int size)
{
	int i;
	for (i = 0; i < size; i++)
		initPerson(&pArr[i]);
}

void	printPersonArr(const Person* pArr,int size)
{
	int i;
	for (i = 0; i < size; i++)
		printPerson(&pArr[i]);
}
