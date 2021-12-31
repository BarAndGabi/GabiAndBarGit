#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Airline.h"
#include "Airport.h"
#include "General.h"
#include "Plane.h"

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
	pComp->sortType = 0;
	return 1;
}
void addDateToList(Airline *pComp, Date *d)
{
	NODE* node = &pComp->Dates.head;
	if (!node)
		return;
	int comparatorAnswer;
	while (node->next)
	{
		comparatorAnswer = compareDate(node->next->key, d);
		if (comparatorAnswer == 0)    
			return;
		else if (comparatorAnswer > 0)    
			break;
		else          
			node = node->next;
	}
	L_insert(node, d);
}

void printCompany(const Airline *pComp)
{
	printf("Airline %s\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight *), printFlight);
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
			printFlight(&pComp->flightArr[i]);
	}
	printf("\n");
}

void doPrintFlightsWithPlaneType(const Airline *pComp)
{
	ePlaneType type = getPlaneType();
	printf("All flights with the selected plane type:\n");
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isPlaneTypeInFlight(pComp->flightArr[i], type))
			printFlight(&pComp->flightArr[i]);
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
		qsort(pComp->flightArr, (size_t)pComp->flightCount, sizeof(Flight *), compareFlightBySourceName);
		pComp->sortType = 1;
		break;
	case 2:
		qsort(pComp->flightArr, pComp->flightCount, (size_t)sizeof(Flight *), compareFlightByDestName);
		pComp->sortType = 2;
		break;
	case 3:
		qsort(pComp->flightArr, (size_t)pComp->flightCount, (size_t)sizeof(Flight *), compareFlightByDate);
		pComp->sortType = 3;
		break;
	case 4:
		qsort(pComp->flightArr, (size_t)pComp->flightCount, (size_t)sizeof(Flight *), compareFlightByPlainCode);
		pComp->sortType = 4;

		break;
	default:
		printf("error");
		return 0;
	}
	printf("sorted\n");
	return 1;
}
int searchFlight(Airline *pComp /*AirportManager* m*/)
{
	Flight *temp = (Flight *)calloc(1, sizeof(Flight));
	if (!temp)
		return 0;
	switch (pComp->sortType)
	{
	case notSorted:
		printf("array not sotred\n");
		free(temp);
		return 0;
	case sourceName:
		temp->nameSource = getStrExactName("enter the airport source name you are searching :");
		printFlight(bsearch(&temp, pComp->flightArr, pComp->flightCount, sizeof(Flight *), compareFlightBySourceName));
		freeFlight(temp);
		return 1;
	case DestanationName:
		temp->nameDest = getStrExactName("enter the airport destenation name you are searching :");
		printFlight(bsearch(&temp, pComp->flightArr, pComp->flightCount, sizeof(Flight *), compareFlightByDestName));
		freeFlight(temp);
		return 1;
	case DateSort:
		getCorrectDate(&temp->date);
		printFlight(bsearch(&temp, pComp->flightArr, pComp->flightCount, sizeof(Flight *), compareFlightByDate));
		free(temp);
		return 1;
	case PlainCode:
		temp->thePlane = *(Plane *)malloc(sizeof(Plane));
		getPlaneCode(temp->thePlane.code);
		printFlight(bsearch(&temp, pComp->flightArr, pComp->flightCount, sizeof(Flight *), compareFlightByPlainCode));
		freeFlight(temp);
		return 1;
	default:
		printf("error");
		break;
	}
	printf("not found\n");

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
//void writeAirlineToFile(const char *fileName, Airline *pComp)
//{
//	FILE *pF = fopen(fileName, "wb");
//	if (!pF)
//		printf("There isnt a file to read from");
//	int len = (int)strlen(pComp->name) + 1;
//	if (fwrite(&len, sizeof(int), 1, pF) != 1)
//		return;
//	if (fwrite(pComp->name, sizeof(char), len, pF) != len)
//		return;
//	if (fwrite(&pComp->sortType, sizeof(int), 1, pF) != 1)
//		return;
//	if (fwrite(&pComp->flightCount, sizeof(int), 1, pF) != 1)
//		return;
//	for (size_t i = 0; i < pComp->flightCount; i++)
//	{
//		writeFlightToFile(pF, pComp->flightArr[i]);
//	}
//
//	fclose(pF);
//}
