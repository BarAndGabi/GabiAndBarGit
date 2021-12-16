#include <stdio.h>
#include "lunch.h"

void initLunch(Lunch* pLaunch)
{
	printf("Enter sendwich name\t");
	scanf("%s", pLaunch->sendwich);
	printf("Did you bring fruit? 1/0\t");
	scanf("%d", &pLaunch->fruit);
	printf("Did you bring drink? 1/0\t");
	scanf("%d", &pLaunch->drink);
}

void printLunch(const Lunch* pLaunch)
{
	printf("Lunch: sendwich %s Fruit? %d  Drink? %d\n", pLaunch->sendwich,
		pLaunch->fruit, pLaunch->drink);
}