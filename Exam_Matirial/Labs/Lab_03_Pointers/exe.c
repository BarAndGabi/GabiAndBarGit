#include <stdio.h>
#include <ctype.h>
#include "arrays.h"
#include "functions3.h"
#include "exe.h"

void q_DivMult()
{
	float m,d;
	float a,b;

	printf("Please enter 2 floats I will compute multiply and division \n");
	scanf("%f %f",&a,&b);

	if (!calc(a,b,&m,&d))	//We send the variable and two addresses for result
		printf("error occur\n");	//the function returned 0
	else
		printf("a*b=%f  a/b=%f\n",m,d);
}

void q_Char()
{
	char ch;

	printf("Please enter a character I will check its type\n");
	do{
		scanf("%c",&ch);
	} while(isspace(ch));
	
	changeChar(&ch);	//call the function with the address of ch.
	printf("I am now %c\n",ch);
}

void q_Reverse()
{
	int num;

	printf("please enter a number if positive will reverse its digits\n");
	scanf("%d",&num);

	if (reversePositive(&num) == 1)
		printf("The number was reverse %d\n",num);
	else
		printf("The number was  NOT reverse - negative %d\n",num);
}

void q_Arr_Sum_Evens()
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9,111,21};
	int sum = 0;
	int countEvens;

	int size = sizeof(arr)/sizeof(int);
	printArray(arr,size);
	sumAndCountEvensInArray(arr,size,&sum,&countEvens);

	printf("The sum of the elemnts in arrays is  %d \n",sum);
	printf("There are %d evens numbers in array \n",countEvens);
}

void q_Arr_Div_SumDig()
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9,111,21};
	int num = 3;
	int countDiv,countSumDig;

	int size = sizeof(arr)/sizeof(int);
	printArray(arr,size);
	countDivAndDigSumInArray(arr,size,num,&countDiv,&countSumDig);

	printf("Division by %d - There are %d numbers\n",num,countDiv);
	printf("sum digits %d - There are %d numbers\n",num,countSumDig);
}


