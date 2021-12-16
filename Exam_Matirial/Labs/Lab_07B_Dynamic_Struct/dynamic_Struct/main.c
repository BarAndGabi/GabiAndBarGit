#include <stdio.h>
#include <stdlib.h>
#include "building.h"


int main()
{
	Family f1;
	if (!initFamily(&f1))
		printf("Error\n");
	else {
		printFamily(&f1);
		freeFamily(&f1);
	}

	Building b;
	initBuilding(&b);

	//add families as the user wants
	initFamiliesFromUser(&b);

	printBuilding(&b);
	freeBuilding(&b);

	system("pause");
}
