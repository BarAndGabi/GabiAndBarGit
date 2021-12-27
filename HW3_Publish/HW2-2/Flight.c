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


void	printFlight(const void* pFlight)
{
	const Flight* pF = (const Flight*)pFlight;
	printf("Flight From %s To %s\t", pF->nameSource, pF->nameDest);
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
int compareFlightBySourceName(const void * f1, const void* f2)
{
	const Flight* flight1 = (const Flight*)f1;
	const Flight* flight2 = (const Flight*)f2;
	if (flight1->nameSource < flight2->nameSource)
		return -1;
	else
		if (flight1->nameSource > flight2->nameSource)
			return 1;
		else
			return 0;

}
int compareFlightByDestName(const void * f1, const void* f2)
{
	
		const Flight* flight1 = (const Flight*)f1;
		const Flight* flight2 = (const Flight*)f2;
		if (flight1->nameDest < flight2->nameDest)
			return -1;
		else
			if (flight1->nameDest > flight2->nameDest)
				return 1;
			else
				return 0;

	
}

int compareFlightByPlainCode(const void * f1, const void* f2)
{
	const Flight* flight1 = (const Flight*)f1;
	const Flight* flight2 = (const Flight*)f2;
	if (flight1->thePlane.code < flight2->thePlane.code)
		return -1;
	else
		if (flight1->thePlane.code > flight2->thePlane.code)
			return 1;
		else
			return 0;
}
int compareFlightByDate(const void * f1, const void* f2)
{
	const Flight* flight1 = (const Flight*)f1;
	const Flight* flight2 = (const Flight*)f2;

	return compare_dates(&flight1->date, &flight2->date);
}
