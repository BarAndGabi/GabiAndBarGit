
#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

int main()
{
	tree_ptr root = (tree_ptr)malloc(sizeof(tree_ptr));
	int a = 100;
	int b = 200;
	root = addNode(20);
	root->left = addNode(8);
	root->right = addNode(122);
	root->left->left = addNode(4);
	root->left->right = addNode(12);

	RangeSearch(root, a, b);

	getchar();
	system("pause");
	return 0;
}
