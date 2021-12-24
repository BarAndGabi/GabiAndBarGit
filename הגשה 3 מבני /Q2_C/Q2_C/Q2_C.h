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
void L_delete(Node* pNode);
int L_init(LIST* pList);
void createListFromArr(LIST* pLst, const int* arr, int size);
int L_print(LIST* pList);


#endif // Q2_C

