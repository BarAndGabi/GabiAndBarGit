#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "listGen.h"
#include "Person.h"



void Q1();


int main()
{
	Q1();
	system("pause");
}


void Q1()
{
	LIST	lst;
	int		count;
	NODE*	pNode;


//// Initialization
	L_init(&lst);

	printf("Please enter person count\n");
	scanf("%d", &count);

	Person* p;
	pNode = &lst.head;
	for (int i = 0; i < count; i++)
	{
		p = (Person*)malloc(sizeof(Person));
		if (!p)
			return;
		initPerson(p);
		pNode = L_insert(pNode, p);
	}

	printf("\nThe persons in list");
	L_print(&lst, showPerson);


	printf("Enter id to find\n");
	int id;
	scanf("%d", &id);
	//Add code here to search for person with id
	Person tempPerson = { id,"" };
	pNode = L_find(lst.head.next, &tempPerson, comparePersonById);
	if (pNode)
	{
		printf("Person found\n");
		showPerson(pNode->key);
	}
	else
		printf("Person not found\n");


	// Finish work
	L_free(&lst, freePerson);
}

