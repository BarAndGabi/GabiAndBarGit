#include "functions3.h"

int calc(float a,float b,float* mult,float* div)
{
	if(b==0)
		return 0;

	*mult=a*b;	// multiply
	*div=a/b;	//division
	return 1;
}

void changeChar(char* pTav)
{
	if ( (*pTav >= 'a') && (*pTav <= 'z'))
		*pTav = 'S';
	else if( (*pTav >= 'A') && (*pTav <= 'Z'))
		*pTav = 'C';
	else if( (*pTav >= '0') && (*pTav <= '9'))
		*pTav = 'D';
	else
		*pTav = 'O';
}

int	reversePositive(int* pNum)
{
	int temp,res=0;
	if(*pNum <= 0)//not positive
		return 0;

	//reverse the number
	temp = *pNum;

	while(temp != 0)
	{
		res = (res*10)+temp%10;
		temp /= 10;
	}
	*pNum = res;
	return 1;
}

void sumAndCountEvensInArray(int* arr, int size,int* pSum,int* pCountEvens)
{
	int i;
	*pSum = 0; //init
	*pCountEvens = 0;

	for (i = 0; i < size; i++)
	{
		if (arr[i] % 2 == 0)
			(*pCountEvens)++;
		(*pSum) += arr[i];
	}
}

void countDivAndDigSumInArray(int* arr, int size, int n,int* pCountDiv, int* pCountSumDig)
{
	int i;
	*pCountDiv = 0; //init
	*pCountSumDig = 0;

	for (i = 0; i < size; i++)
	{
		if (arr[i] % n == 0)
			(*pCountDiv)++;
		if(sumDig(arr[i]) == n)
			(*pCountSumDig)++;
	}
}

int	sumDig(int num)
{
	int sum = 0;
	while(num != 0)
	{
		sum +=num%10;
		num /= 10;
	}
	return sum;
}










