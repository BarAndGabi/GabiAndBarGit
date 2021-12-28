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
	if (runner->next == NULL)//if empty
	{
		L_insert(runner, d);
		return 1;
	}
	else
	{
		if (compare_dates(runner->next->key, d) == 1)//if smaller then the first
		{
			L_insert(runner, d);
			return 1;
		}
		while (runner->next != NULL)
		{
			runner = runner->next;
			if (compare_dates(runner->key, d) != 0)
			{
				if (isBetweenOrEqualToFirst(runner->key, runner->next->key, d) == 1)
				{
					L_insert(runner->next, d);
					return 1;
				}
			}
			else
			{
				printf("date is in list \n");
				return 1;
			}
		}
	}
	L_insert(runner, d);

	return 1;
}
void getDatesFrommArr(Airline * a)
{
	L_init(&a->Dates);
	for (size_t i = 0; i < a->flightCount; i++)
	{
		addDateToList(a,&a->flightArr[i]->date);
	}
}
int readAirlineFromFile(char *fileName, Airline *a)
{
	FILE *f = fopen(fileName, "rb");
	int len;
	if (fread(&len, sizeof(int), 1, f) != 1)
		return 0;
	a->name = (char*)malloc(len * sizeof(char));
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
	a->flightArr = (Flight **)malloc( (a->flightCount + 1) * sizeof(Flight *));
	if (!a->flightArr)
		return 0;
	if (a->flightCount > 0)
		for (size_t i = 0; i < a->flightCount; i++)
		{
			a->flightArr[i] = (Flight*)malloc(sizeof(Flight));
			readFlightFromFile(f, a->flightArr[i]);
		}
	getDatesFrommArr(a);

	fclose(f);
	return 1;
}

void printCompany(const Airline *pComp)
{
	printf("Airline %s\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	//generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight*), printFlight);
	printFlightArr(pComp->flightArr, pComp->flightCount);
	printf("airline DATES :\n");
	L_print(&pComp->Dates, printDate);
}

void printFlightArr(Flight **pFlight, int size)
{
	for (int i = 0; i < size; i++)
		printFlight(pFlight[i]);
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
int sortFlights(Airline *pComp)
{
	int choise = flightsComparatorMenu();
	switch (choise)
	{
	case 1:
		qsort(pComp->flightArr, (size_t)pComp->flightCount, (size_t)sizeof(Flight *), compareFlightBySourceName);
		break;
	case 2:
		qsort(&pComp->flightArr, (size_t)pComp->flightCount, (size_t)sizeof(Flight *), compareFlightByDestName);
		break;
	case 3:
		qsort(&pComp->flightArr, (size_t)pComp->flightCount, (size_t)sizeof(Flight *), compareFlightByDate);
		break;
	case 4:
		qsort(&pComp->flightArr, (size_t)pComp->flightCount, (size_t)sizeof(Flight *), compareFlightByPlainCode);
		break;
	default:
		printf("error");
		return 0;
	}
	printf("sorted\n");
	return 1;
}
int searchFlight(Airline *pComp)
{
	switch (pComp->sortType)
	{
	case notSorted:
		//bsearch(pF,pComp->flightArr, pComp->flightCount, sizeof(Flight), compareFlightBySourceName);

		break;
	case sourceName:
		//	bsearch(pF,pComp->flightArr, pComp->flightCount, sizeof(Flight), compareFlightByDestName);

		break;
	case DestanationName:
		//		bsearch(pF,pComp->flightArr, pComp->flightCount, sizeof(Flight), compareFlightByDate);
		break;
	case DateSort:
		//	bsearch(pF,pComp->flightArr, pComp->flightCount, sizeof(Flight), compareFlightByPlainCode);
		break;
	case PlainCode:
		//	bsearch(pF,pComp->flightArr, pComp->flightCount, sizeof(Flight), compareFlightByPlainCode);
		break;
	default:
		printf("error");
		break;
	}
	return 0;
}
int flightsComparatorMenu()
{
	int choise = 0;

	while (!(choise > 0 && choise < 5))
	{
		printf("choose on of the following to search/sory by :\n");
		printf("1) for sourceName\n2) for DestanationName\n3) for DateSort\n4) for PlainCode\n");
		scanf("%d", &choise);
	}
	return choise;
}
