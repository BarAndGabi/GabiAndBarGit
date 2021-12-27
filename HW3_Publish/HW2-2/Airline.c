#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Airline.h"
#include "Airport.h"
#include "General.h"

void initAirline(Airline *pComp)
{
	printf("-----------  Init Airline Airline\n");
	pComp->name = getStrExactName("Enter Airline name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	L_init(&pComp->Dates);
	pComp->sortType = notSorted;
}

int addFlight(Airline *pComp, const AirportManager *pManager)
{
	if (pManager->airportsCount < 2)
	{
		printf("There are not enough airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight **)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight *));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight *)calloc(1, sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount], pManager);

	addDateToList(pComp, &pComp->flightArr[pComp->flightCount]->date);
	pComp->flightCount++;
	return 1;
}
int addDateToList(Airline *pComp, Date *d)
{
	NODE *runner = &pComp->Dates.head;
	if (runner->next == NULL)
	{
		L_insert(runner, d);
		return 1;
	}
	else if (compare_dates(runner->next->key, d) == 1)
	{
		L_insert(runner, d);
		return 1;
	}
	runner = runner->next;
	while (runner->next != NULL)
	{

		if (isBetweenOrEqualToFirst(runner->key, runner->next->key, d))
		{
			L_insert(runner->next, d);
			return 1;
		}
		runner = runner->next;
	}
	L_insert(runner, d);

	return 1;
}
int readAirlineFromFile(char *fileName, Airline *a)
{
	FILE *airline = fopen(fileName, "rb");
	fclose(airline);
	return 0;
}
void printCompany(const Airline *pComp)
{
	printf("Airline %s\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight), printFlight);
	printf("airline DATES :\n");
	L_print(&pComp->Dates, printDate);
}

void doCountFlightsFromName(const Airline *pComp)
{
	if (pComp->flightCount == 0)
	{
		printf("No flight in company\n");
		return;
	}

	char *tempName = getStrExactName("Please enter origin airport name");

	int count = 0;
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isFlightFromSourceName(pComp->flightArr[i], tempName))
			count++;
	}

	free(tempName);

	if (count != 0)
		printf("There are %d ", count);
	else
		printf("There are No ");

	printf("flights from this airport\n");
}

void doPrintFlightsWithPlaneCode(const Airline *pComp)
{
	char code[MAX_STR_LEN];
	getPlaneCode(code);
	printf("All flights with plane code %s:\n", code);
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isPlaneCodeInFlight(pComp->flightArr[i], code))
			printFlight(pComp->flightArr[i]);
	}
	printf("\n");
}

void doPrintFlightsWithPlaneType(const Airline *pComp)
{
	ePlaneType type = getPlaneType();
	printf("All flights with plane type %s:\n", PlaneTypeStr[type]);
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isPlaneTypeInFlight(pComp->flightArr[i], type))
			printFlight(pComp->flightArr[i]);
	}
	printf("\n");
}

void freeFlightArr(Flight **arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		freeFlight(arr[i]);
	}
}

void freeCompany(Airline *pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->Dates, NULL);
}
