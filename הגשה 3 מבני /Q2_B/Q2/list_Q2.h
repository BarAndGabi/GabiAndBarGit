#ifndef __LIST__
#define __LIST__
typedef struct node
{
	int num;
	struct node *next;
} Node;

Node *combine_lists(Node *head1, Node *head2);

typedef struct
{
	Node head;
	Node *tail;
} LIST;

int L_init(LIST *pList);
Node *L_insert(Node *pNode, int Value, LIST *pList);
void createListFromArr(LIST *pLst, const int *arr, int size);
Node *combine_lists(Node *head1, Node *head2);
void L_print(LIST *pList);
#endif