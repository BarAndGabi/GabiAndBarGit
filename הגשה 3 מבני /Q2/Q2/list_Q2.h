#ifndef __LIST__
#define __LIST__
typedef struct node
{
	int num;
	struct node *next;
} Node;

Node *combine_lists(Node *head1, Node *head2);

typedef struct {
	Node head;
	Node* tail;
}LIST;
int addNode(Node *addThis, LIST *ResultList);
Node *combine_lists(Node *head1, Node *head2);
#endif