#ifndef __BUILDING_H
#define __BUILDING_H

#include "family.h"

typedef struct
{
	Family** 	allFamilies;
	int 		maxFamilies;
	int 		numOfFamilies;
} Building;

void 	initBuilding(Building* pBuild);
int		addFamilyToArr(Building* pBuild);
void	initFamiliesFromUser(Building* pBuild);
void 	printBuilding(const Building* pBuild);
void 	freeBuilding(Building* pBuild);

#endif // __BUILDING_H
