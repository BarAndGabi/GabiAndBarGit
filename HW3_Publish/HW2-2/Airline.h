#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"
#include "list.h"

typedef enum
{
	notSorted,
	sourceName,
	DestanationName,
	DateSort,
	PlainCode
} SortedType;

typedef struct
{
	char *name;
	int flightCount;
	Flight **flightArr;
	LIST Dates;
	SortedType sortType;

} Airline;

void initAirline(Airline *pComp);
int addFlight(Airline *pComp, const AirportManager *pManager);
void printCompany(const Airline *pComp);
void doCountFlightsFromName(const Airline *pComp);
void doPrintFlightsWithPlaneCode(const Airline *pComp);
void doPrintFlightsWithPlaneType(const Airline *pComp);
void freeFlightArr(Flight **arr, int size);
void freeCompany(Airline *pComp);
void addDateToList(Airline *pComp, Date *d);
//int readAirlineFromFile(char *fileName, Airline *a);
int sortFlights(Airline *pComp);
int searchFlight(Airline *pComp);
//void writeAirlineToFile(const char *fileName, Airline *pComp);
int flightsComparatorMenu();
#endif
