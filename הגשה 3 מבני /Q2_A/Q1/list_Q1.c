#include <stdio.h>
#include <stdlib.h>
#include "list_Q1.h"

int biggerSumList(Node *head1, Node *head2)
{
	int sum1 = sumListAndFindTail(head1);
	int sum2 = sumListAndFindTail(head2);
	if (sum1 >= sum2)
		return 1;
	else
		return 2;
}
int sumListAndFindTail(Node *head)
{
	int sum = 0;
	Node* pN = head->next;
	while (pN != NULL)
	{
		
		sum = sum + pN->num;
		pN = pN->next;
		

	}
	return sum;
}
Node* findTail(Node *head)
{
	Node* pN = head->next;
	while (pN->next != NULL)
	{
		pN = pN->next;
	}
	return pN;
	
	
}
Node *combine_lists(Node *head1, Node *head2)
{
	Node* tail1=findTail(head1);
	Node* tail2=findTail(head2);
	switch (biggerSumList(head1, head2))
	{
	case 1:
		tail1->next = head2->next;
		tail2->next = head1;
		return head1;
		break;
	case 2:
		tail2->next = head1->next;
		tail1->next = head2;
		return head2;
		break;
	}
	return NULL;
}

int L_init(LIST* pList)
{
	if (pList == NULL)
		return 0;	// no list to initialize

	pList->head.next = NULL;
	return 1;
}
void createListFromArr(LIST* pLst, const int* arr, int size)
{
	Node* pN = &pLst->head;
	for (int i = 0; i < size; i++)
		pN = L_insert(pN, arr[i]);
}
Node* L_insert(Node* pNode, int Value)
{
	Node* tmp;

	if (!pNode)
		return NULL;

	tmp = (Node*)malloc(sizeof(Node));	// new node

	if (tmp != NULL) {
		tmp->num = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}
int L_print(LIST* pList)
{
	Node* tmp;
	int	counter = 0;

	if (!pList) return 0;

	printf("\n");
	for (tmp = pList->head.next; tmp; tmp = tmp->next, counter++)
		printf(" %d ", tmp->num);
	printf("\n");
	return counter;
}
int L_printCIRCLE(Node* head)
{
	Node* tmp;
	int	counter = 0;

	if (!head) 
		return 0;
	tmp = head->next;
	printf("\n");
	while (tmp !=head)
	{
		printf(" %d ", tmp->num);
		tmp = tmp->next;
	}
	printf("\n");
	return counter;
}
