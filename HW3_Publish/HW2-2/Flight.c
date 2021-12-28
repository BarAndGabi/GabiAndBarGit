#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"


void	initFlight(Flight* pFlight, const AirportManager* pManager)
{
	Airport* pPortOr = setAiportToFlight(pManager, "Enter name of origin airport:");
	pFlight->nameSource = _strdup(pPortOr->name);
	int same;
	Airport* pPortDes;
	do {
		pPortDes = setAiportToFlight(pManager, "Enter name of destination airport:");
		same = isSameAirport(pPortOr, pPortDes);
		if (same)
			printf("Same origin and destination airport\n");
	} while (same);
	pFlight->nameDest = _strdup(pPortDes->name);
	initPlane(&pFlight->thePlane);
	getCorrectDate(&pFlight->date);
}




int		isFlightFromSourceName(const Flight* pFlight, const char* nameSource)
{
	if (strcmp(pFlight->nameSource, nameSource) == 0)
		return 1;

	return 0;
}


int		isFlightToDestName(const Flight* pFlight, const char* nameDest)
{
	if (strcmp(pFlight->nameDest, nameDest) == 0)
		return 1;

	return 0;


}

int		isPlaneCodeInFlight(const Flight* pFlight, const char*  code)
{
	if (strcmp(pFlight->thePlane.code, code) == 0)
		return 1;
	return 0;
}

int		isPlaneTypeInFlight(const Flight* pFlight, ePlaneType type)
{
	if (pFlight->thePlane.type == type)
		return 1;
	return 0;
}


void	printFlight(const void** pFlight)
{
	const Flight* pF = *(const Flight**)pFlight;
	printf("Flight From %s To %s\t",pF->nameSource,pF->nameDest);
	printDate(&pF->date);
	printPlane(&pF->thePlane);
}

Airport* setAiportToFlight(const AirportManager* pManager, const char* msg)
{
	char name[MAX_STR_LEN];
	Airport* port;
	do
	{
		printf("%s\t", msg);
		myGets(name, MAX_STR_LEN);
		port = findAirportByName(pManager, name);
		if (port == NULL)
			printf("No airport with this name - try again\n");
	} while (port == NULL);

	return port;
}

void	freeFlight(Flight* pFlight)
{
	free(pFlight->nameSource);
	free(pFlight->nameDest);
	free(pFlight);
}
readFlightFromFile(FILE *f, Flight * f1)
{
	int len;
	if (fread(&len, sizeof(int), 1, f) != 1)
		return 0;
	f1->nameSource= (char*)malloc(len * sizeof(char));
	if (!f1->nameSource)
		return 0;
	if (fread(f1->nameSource, sizeof(char), len, f) != len)
	{
		free(f1->nameSource);
		return 0;
	}
	if (fread(&len, sizeof(int), 1, f) != 1)
		return 0;
	f1->nameDest = (char*)malloc(len * sizeof(char));
	if (!f1->nameDest)
		return 0;
	if (fread(f1->nameDest, sizeof(char), len, f) != len)
	{
		free(f1->nameDest);
		return 0;
	}
	fread(&f1->thePlane, sizeof(Plane), 1, f);
	fread(&f1->date, sizeof(Date), 1, f);

return 1;
}
