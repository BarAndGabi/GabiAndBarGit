#ifndef Q2_C
#define Q2_C

typedef struct node
{
	int num;
	struct node *next;
} Node;

typedef struct
{
	Node head;
}LIST;
Node* del_fun(Node* head, int* vec);
int checkArray(int* vec);
int checkIfZero(int* vec);
int checkIfSorted(int* vec);
Node* L_insert(Node* pNode, int Value);

#endif // Q2_C

