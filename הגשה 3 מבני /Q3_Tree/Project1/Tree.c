
#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

void RangeSearch(tree_ptr base, itemType u, itemType v)
{
	if (isEmpty(base))
		return;
	itemType currenValue = base->info;
	if (u < currenValue)
		RangeSearch(base->left, u, v);

	if (u <= currenValue && v >= currenValue)
		printf("%d ", base->info);

	RangeSearch(base->right, u, v);
}

int isEmpty(tree_ptr p)
{
	if (p == NULL)
		return 1;
	return 0;
}

tree_ptr addNode(int info)
{
	tree_ptr temp = (tree_ptr) malloc(sizeof(tree_ptr));
	temp->info = info;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}