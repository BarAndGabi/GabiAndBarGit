#include <stdio.h>
#include <stdlib.h>
#include "list_Q1.h"

int biggerSumList(Node *head1, Node *head2, Node *tail1, Node *tail2)
{
	int sum1 = sumListAndFindTail(head1, tail1);
	int sum2 = sumListAndFindTail(head2, tail2);
	if (sum1 >= sum2)
		return 1;
	else
		return 2;
}
int sumListAndFindTail(Node *head, Node *tail)
{
	int sum = 0;
	while (head != NULL)
	{
		sum = sum + head->num;
		head = head->next;
		if (head->next == NULL)
			tail = head;
	}
	return sum;
}
Node *combine_lists(Node *head1, Node *head2)
{
	Node tail1;
	Node tail2;
	switch (biggerSumList(head1, head2, &tail1, &tail2))
	{
	case 1:
		tail1.next= head2->next;
		tail2.next = head1->next;
		return head1;
		break;
	case 2:
		tail2.next = head1->next;
		tail1.next = head2->next;
		return head2;
		break;
	}
	return NULL;
}