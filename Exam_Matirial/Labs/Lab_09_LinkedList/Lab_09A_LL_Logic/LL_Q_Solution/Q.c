#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "Q.h"




int	 findMax(NODE* pNode)
{
	if (!pNode)
		return EMPTY;

	int max = pNode->key;
	pNode = pNode->next;
	while (pNode != NULL)
	{
		if (pNode->key > max)
			max = pNode->key;
		pNode = pNode->next;
	}
	return max;
}

void removeDuplicates(NODE* pNode)
{
	if (!pNode)
		return;
	while (pNode->next != NULL)
	{
		if (pNode->key == pNode->next->key)
			L_delete(pNode);
		else
			pNode = pNode->next;
	}
}

#ifndef NO_LIST_FUNC
void insertToNum(LIST* pList, int num)
{
	int value;
	NODE* pNode = pList->head.next;
	while (pNode != NULL)
	{
		value = num - pNode->key;
		pNode = L_insert(pNode, value);
		pNode = pNode->next;
	}
}
#else
void insertToNum(LIST* pList, int num)
{
	NODE* pNew;
	if (!pList)
		return;

	NODE* pNode = pList->head.next;
	while (pNode != NULL)
	{
		pNew = (NODE*)malloc(sizeof(NODE));
		if (!pNew)
			return;
		pNew->key = num - pNode->key;
		pNew->next = pNode->next;
		pNode->next = pNew;
		pNode = pNew->next;
	}
}
#endif


void removeValFromList(LIST* pList, int val)
{
	if (!pList)
		return;

	NODE* pNode = &pList->head;

	while (pNode->next != NULL)
	{
		if (pNode->next->key == val)
			L_delete(pNode);
		else
			pNode = pNode->next;
	}
}

void removeNMaxFromList(LIST* pList, int num)
{
	NODE* pNode;
	if (!pList)
		return;
	for (int i = 0; i < num; i++)
	{
		pNode = findBeforeMax(pList);
		if (pNode)
			L_delete(pNode);
	}
}

NODE* findBeforeMax(LIST* pList)
{
	if (!pList)
		return NULL;

	NODE* pPrevMax = &pList->head;
	NODE* pNode = pList->head.next;
	int max = pNode->key;

	NODE* pPrevNode = pNode;
	pNode = pNode->next;


	while (pNode != NULL)
	{
		if (pNode->key > max)
		{
			max = pNode->key;
			pPrevMax = pPrevNode;
		}
		pPrevNode = pNode;
		pNode = pNode->next;
	}

	return pPrevMax;
}

void createListFromArr(LIST* pLst, const int* arr, int size)
{
	NODE* pN = &pLst->head;
	for (int i = 0; i < size; i++)
		pN = L_insert(pN, arr[i]);
}