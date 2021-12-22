#include <stdio.h>
#include <stdlib.h>
#include "list_Q2.h"

Node *combine_lists(Node *head1, Node *head2)
{
	LIST *ResultList = (LIST *)malloc(sizeof(LIST));
	ResultList->tail = &ResultList->head;
	if (head2->next == NULL && head1->next == NULL)
		return &ResultList->head;
	if (head1->next == NULL)
		ResultList->head.next = head2->next;
	if (head2->next == NULL)
		ResultList->head.next = head1->next;
	Node *tail1 = head1->next;
	Node *tail2 = head2->next;
	int turn = 1;
	int flag1 = 0;
	int flag2 = 0;
	//int sum = flag1 + flag2;
	while (flag1 == 0 || flag2 == 0)
	{
		
	
		switch (turn)
		{
		case 1:
			if (tail1 == head1)
			{
				tail1 = tail1->next;
			}
			L_insert(tail1,tail1->num,ResultList);
			tail1 = tail1->next;
			
			break;
		case -1: 
			if (tail2 == head2)
			{
				tail2 = tail2->next;
			}
			L_insert(tail2, tail2->num, ResultList);
			tail2 = tail2->next;
			break;
		}
		turn = turn * -1;
		if (tail1 == head1)
			flag1 = 1;
		if (tail2 == head2)
			flag2 = 1;

	}

	return &ResultList->head;
}
int addNode(Node *addThis, LIST *ResultList)
{
	Node* tmp;

	//add node to list and change the new tail.
	if (&ResultList->head == NULL) {
		//If list is empty, both head and tail would point to new node.  
		ResultList->head = *addThis;
		ResultList->tail = addThis;
		addThis->next = &(ResultList->head);
	}
	else 
	{
		//tail will point to new node.  
		ResultList->tail->next = addThis;
		//New node will become new tail.  
		ResultList->tail = addThis;
		//Since, it is circular linked list tail will point to head.  
		ResultList->tail->next = &(ResultList->head);
	}
	return 1;
}

int L_init(LIST* pList)
{
	if (pList == NULL)
		return 0;	// no list to initialize

	pList->head.next = NULL;
	pList->tail =&pList->head;
	return 1;
}


Node* L_insert(Node* pNode, int Value,LIST* pList)
{
	Node* tmp;

	if (!pNode)
		return NULL;

	tmp = (Node*)malloc(sizeof(Node));	// new node

	if (tmp != NULL) {
		if (&pList->head == NULL) {
			tmp->num = Value;
			tmp->next = &pList->head;
			pList->tail = tmp;
			pList->head.next = pList->tail;
		}
		else {
			tmp->num = Value;
			tmp->next = &pList->head;
			pList->tail->next = tmp;
			pList->tail = tmp;
		}

	}
	return tmp;

}

void createListFromArr(LIST* pLst, const int* arr, int size)
{
	Node* pN = &pLst->head;
	for (int i = 0; i < size; i++)
		pN = L_insert(pN, arr[i],pLst);
}

void L_print(LIST* pList) {
	if (!pList)
		printf("list is empty");

	for (Node* tmp = pList->head.next; tmp != &pList->head; tmp = tmp->next) {
		printf("%d ", tmp->num);
	}
	printf("\n");
}

