﻿#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Airport.h"
#include "General.h"
#include "Address.h"

int isSameAirport(const Airport *pPort1, const Airport *pPort2)
{
	if (!pPort1 || !pPort2)
		return 0;
	if (strcmp(pPort1->name, pPort2->name) == 0)
		return 1;

	return 0;
}

int isAirportName(const Airport *pPort1, const char *name)
{
	if (!pPort1)
		return 0;
	if (strcmp(pPort1->name, name) == 0)
		return 1;

	return 0;
}

void initAirportNoName(Airport *pPort)
{
	//only address!!!
	pPort->address = getAddress();
}

void printAirport(const Airport *pPort)
{
	printf("Airport name:%-20s\t", pPort->name);
	printf("Airport address: %s\n", pPort->address);
}

void freeAirport(Airport *pPort)
{
	free(pPort->name);
	free(pPort->address);
}

void writeToFileAirport(FILE *pF, Airport *pPort)
{
	fprintf(pF, "%s\n%s\n", pPort->name, pPort->address);
}

int readFromFileAirport(FILE *pF, Airport *pPort)
{
	char line[255];
	char line2[255];
	if (fgets(line, sizeof(line), pF) == NULL)
		return 0;
	pPort->name = _strdup(line);
	removeChar(pPort->name, '\n');
	if (!pPort->name)
		free(pPort->name);
	if (fscanf(pF, "%s ", line2) != 1)
		return 0;
	pPort->address = _strdup(line2);
	if (!pPort->address)
		free(pPort->address);

	return 1;
}
