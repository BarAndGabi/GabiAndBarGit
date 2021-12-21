#include <stdio.h>
#include <stdlib.h>
#include "list_Q2.h"

Node *combine_lists(Node *head1, Node *head2)
{
	LIST *ResultList = (LIST *)malloc(sizeof(LIST));
	if (head2->next == NULL && head1->next == NULL)
		return &ResultList->head;
	if (head1->next == NULL)
		ResultList->head.next = head2->next;
	if (head2->next == NULL)
		ResultList->head.next = head1->next;
	Node *tail1 = head1;
	Node *tail2 = head2;
	int turn = 1;
	int flag1 = 0;
	int flag2 = 0;
	//int sum = flag1 + flag2;
	while (flag1 == 0 || flag2 == 0)
	{
		if (tail1->next == head1)
			flag1 = 1;
		if (tail2->next == head2)
			flag2 = 1;
		switch (turn)
		{
		case 1:
			if (tail1 = head1)
			{
				tail1 = tail1->next;
			}
			addNode(tail1, ResultList);
			tail1 = tail1->next;

			break;
		case -1: 
			if (tail2 = head2)
			{
				tail2 = tail2->next;
			}
			addNode(tail2, ResultList);
			tail1 = tail2->next;
			break;
		}
	}
	return &ResultList->head;
}
int addNode(Node *addThis, LIST *ResultList)
{//add node to list and change the new tail.
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