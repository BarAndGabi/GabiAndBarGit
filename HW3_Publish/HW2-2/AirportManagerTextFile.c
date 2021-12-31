#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AirportManagerTextFile.h"

int readAirportsFromFile(const char *fileName, AirportManager *pManager)
{
	FILE *pF = fopen(fileName, "r");
	if (!pF)
		return 0;
	if (fscanf(pF, "%d ", &pManager->airportsCount) != 1)
	{
		fclose(pF);
		return 0;
	}

	pManager->airportsArr = (Airport *)malloc(sizeof(Airport) * (pManager->airportsCount));
	if (!pManager->airportsArr)
	{
		free(pManager->airportsArr);
		fclose(pF);
		return 0;
	}
	for (size_t i = 0; i < pManager->airportsCount; i++)
	{
		if (!readFromFileAirport(pF, &pManager->airportsArr[i]))
		{
			freeManager(pManager);
			fclose(pF);
			return 0;
		}
	}
	fclose(pF);
	return 1;
}

void writeAirportsToFile(const char *fileName, AirportManager *pManager)
{
	FILE *pF = fopen(fileName, "w");
	if (!pF)
		printf("There isnt a file to read from");

	fprintf(pF, "%d\n", pManager->airportsCount);

	for (size_t i = 0; i < pManager->airportsCount; i++)
		writeToFileAirport(pF, &pManager->airportsArr[i]);

	fclose(pF);
}
