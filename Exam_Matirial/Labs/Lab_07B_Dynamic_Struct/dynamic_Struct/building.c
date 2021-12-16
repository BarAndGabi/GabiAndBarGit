#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "building.h"

void initBuilding(Building* pBuild)
{
	printf("What is the max number of families? ");
	scanf("%d", &(pBuild->maxFamilies));

	pBuild->numOfFamilies = 0;
	pBuild->allFamilies = NULL;
}

void initFamiliesFromUser(Building* pBuild)
{
	int ok = 1;
	char tav;

	while (ok) {
		if (pBuild->maxFamilies == pBuild->numOfFamilies) //building full
		{
			printf("Building is full\n");
			return;
		}

		printf("Do you want to enter a family? y/n\n");
		do {
			scanf("%c", &tav);
		} while (isspace(tav));

		if (tav == 'y' || tav == 'Y')
			ok = addFamilyToArr(pBuild);
		else
			ok = 0;
	}
}

int addFamilyToArr(Building* pBuild)
{
	if (pBuild->maxFamilies == pBuild->numOfFamilies) //building full
		return 0;	

	Family* pF =  (Family*) malloc(sizeof(Family));
	if (!pF)
		return 0;
	if (!initFamily(pF))
	{
		free(pF); //free what was allocated
		return 0;
	}

	pBuild->allFamilies = (Family**)realloc(pBuild->allFamilies,
		(pBuild->numOfFamilies + 1) * sizeof(Family*));
	if (!pBuild->allFamilies)
	{ //free al allocations made up to here before return
		freeFamily(pF);
		free(pF);
		return 0;
	}

	pBuild->allFamilies[pBuild->numOfFamilies] = pF;
	pBuild->numOfFamilies++;
	return 1;
}

void printBuilding(const Building* theBuilding)
{
	printf("Building has %d families out of %d:\n", theBuilding->numOfFamilies,
			theBuilding->maxFamilies);
	for (int i = 0; i < theBuilding->numOfFamilies; i++)
		printFamily(theBuilding->allFamilies[i]);
}

void freeBuilding(Building* theBuilding)
{
	for (int i = 0; i < theBuilding->numOfFamilies; i++) {
		freeFamily(theBuilding->allFamilies[i]);
		free(theBuilding->allFamilies[i]);
	}

	free(theBuilding->allFamilies);
}
