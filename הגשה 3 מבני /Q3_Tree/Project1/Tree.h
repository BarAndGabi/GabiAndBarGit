#pragma once

typedef int itemType;
typedef struct node
{
	itemType info;
	struct node *left;
	struct node *right;
} tree_node, *tree_ptr;

void RangeSearch(tree_ptr base, itemType u, itemType v);
int isEmpty(tree_ptr p);
void Print(tree_ptr root, int k1, int k2);
tree_ptr addNode(int info);

