
#include <stdio.h>
#include "Address.h"

void	initAddress(Address* pAd)
{
	printf("please street name and house number\n");
	scanf("%s %d",pAd->street,&(pAd->num));
}


void printAddress(const Address* pAd)
{
	printf("%s number % d\n",pAd->street,pAd->num);
}

