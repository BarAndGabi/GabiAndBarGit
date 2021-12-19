#ifndef __LIST__
#define __LIST__
typedef struct node
{
    int num;
    struct node *next;
} Node;
int sumListAndFindTail(Node *head, Node *tail);
int biggerSumList(Node *head1, Node *head2, Node *tail1, Node *tail2);
Node *combine_lists(Node *head1, Node *head2);
#endif