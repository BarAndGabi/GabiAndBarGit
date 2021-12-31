#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AirlineBinFile.h"

void writeAirlineToFile(const char *fileName, Airline *pComp)
{
	FILE *pF = fopen(fileName, "wb");
	if (!pF)
		printf("There isnt a file to read from");
	int len = (int)strlen(pComp->name) + 1;
	if (fwrite(&len, sizeof(int), 1, pF) != 1)
		return;
	if (fwrite(pComp->name, sizeof(char), len, pF) != len)
		return;
	if (fwrite(&pComp->sortType, sizeof(int), 1, pF) != 1)
		return;
	if (fwrite(&pComp->flightCount, sizeof(int), 1, pF) != 1)
		return;
	for (size_t i = 0; i < pComp->flightCount; i++)
	{
		writeFlightToFile(pF, pComp->flightArr[i]);
	}

	fclose(pF);
}

void getDatesFrommArr(Airline *a)
{
	L_init(&a->Dates);
	for (size_t i = 0; i < a->flightCount; i++)
	{
		addDateToList(a, &a->flightArr[i]->date);
	}
}

int readAirlineFromFile(char *fileName, Airline *a)
{
	FILE *f = fopen(fileName, "rb");
	if (f == NULL)
		return 0;
	int len;
	if (fread(&len, sizeof(int), 1, f) != 1)
		return 0;
	a->name = (char *)malloc(len * sizeof(char));
	if (!a->name)
		return 0;
	if (fread(a->name, sizeof(char), len, f) != len)
	{
		free(a->name);
		return 0;
	}
	if (fread(&a->sortType, sizeof(int), 1, f) != 1)
	{
		free(a->name);
		return 0;
	}
	if (fread(&a->flightCount, sizeof(int), 1, f) != 1)
	{
		free(a->name);
		return 0;
	}
	a->flightArr = (Flight **)malloc((a->flightCount + 1) * sizeof(Flight *));
	if (!a->flightArr)
		return 0;
	if (a->flightCount > 0)
		for (size_t i = 0; i < a->flightCount; i++)
		{
			a->flightArr[i] = (Flight *)malloc(sizeof(Flight));
			readFlightFromFile(f, a->flightArr[i]);
		}
	getDatesFrommArr(a);
	a->sortType = 0;

	fclose(f);
	return 1;
}

