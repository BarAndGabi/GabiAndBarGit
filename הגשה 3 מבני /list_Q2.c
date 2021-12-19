#include <stdio.h>
#include <stdlib.h>
#include "list_Q2.h"

Node *combine_lists(Node *head1, Node *head2)
{
    Node *ResultList = (Node *)malloc(sizeof(Node));
    if (head1->next == NULL && head2->next == NULL)//check if empty!!!!!!!
        return ResultList;
   
}