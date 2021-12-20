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
	Node *list1Runner = head1;
	Node *list2Runner = head2;
	int turn =1;
	while (list1Runner->next != head1 && list2Runner->next != head2) 
	{
		switch (turn)
		{
		case 1 : 
			addNode(list1Runner->next, ResultList);
			break;
		case -1:
			addNode(list2Runner->next, ResultList);
			break;
		}
		turn = turn * (-1);
	}
	if (list1Runner->next == head1 && list2Runner->next == head2)
		return &ResultList->head;
	if (list1Runner->next == head1)
	{
		addNode(list2Runner->next, ResultList);
	}
	else
	{
		addNode(list1Runner->next, ResultList);
	}

	return &ResultList->head;
}
int addNode(Node *addThis,LIST *ResultList)
{//add node to list and change the new tail.
	ResultList->tail->next = addThis;
	ResultList->tail = addThis;
	return 1;
}