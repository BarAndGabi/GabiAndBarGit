#pragma once
#ifndef __LIST__
#define __LIST__
typedef struct node
{
	int num;
	struct node *next;
} Node;
typedef struct 
{
	Node head;
}LIST;

int sumListAndFindTail(Node *head);
int biggerSumList(Node *head1, Node *head2);
Node *combine_lists(Node *head1, Node *head2);
Node* L_insert(Node* pNode, int Value);
void createListFromArr(LIST* pLst, const int* arr, int size);
int L_init(LIST* pList);
int L_print(LIST* pList);
int L_printCIRCLE(Node* pList);
Node* findTail(Node *head);


#endif