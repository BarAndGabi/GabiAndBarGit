#include <stdio.h>
#include <stdlib.h>
#include "Q2_C.h"

Node * del_fun(Node * head, int * vec)
{
	if(checkArray(vec)==0)
	return head;

	Node* pL = head;

	int i = 0; int x = 0;
	while (pL != NULL) 
	{
		if (vec[i] == x) 
		{
			L_delete(pL);
			x++, i++;
		}
		else {
			x++, pL = pL->next;
		}
	}
	if (head->next == NULL)
		return NULL;

	return head;
}

int checkArray(int * vec)
{
	if (!checkIfZero(vec) || !checkIfSorted(vec))
		return 0;

	return 1;
}

int checkIfZero(int * vec)
{
	if (*vec != 0)
		return 0;

	return 1;
}

int checkIfSorted(int* vec)
{
	int i = 1;
	int checker = *vec;
	while (vec[i] != -1)
	{
		if (vec[i] < checker) {
			return 0;
		}
		checker = vec[i];
		i++;
	}
	return 1;
}

int L_init(LIST* pList)
{
	if (pList == NULL)
		return 0;	// no list to initialize

	pList->head.next = NULL;
	return 1;
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

void L_delete(Node * pNode)
{

	Node* temp = pNode->next;
	if (temp != NULL) {
		pNode->next = temp->next;
		free(temp);
	}
}

void createListFromArr(LIST* pLst, const int* arr, int size)
{
	Node* pN = &pLst->head;
	for (int i = 0; i < size; i++)
		pN = L_insert(pN, arr[i]);
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

